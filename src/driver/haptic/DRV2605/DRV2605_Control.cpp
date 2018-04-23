/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 Alexander Entinger / LXRobotics GmbH
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/haptic/DRV2605/DRV2605_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace haptic
{

namespace DRV2605
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t const DEVICE_RESET_DURATION_ms = 10;

FLASH_DECLARE(static char const STATUS          [] = "STATUS            = ");
FLASH_DECLARE(static char const MODE            [] = "MODE              = ");
FLASH_DECLARE(static char const RTP             [] = "RTP               = ");
FLASH_DECLARE(static char const LIB             [] = "LIB               = ");
FLASH_DECLARE(static char const WAVESEQ1        [] = "WAVESEQ1          = ");
FLASH_DECLARE(static char const WAVESEQ2        [] = "WAVESEQ2          = ");
FLASH_DECLARE(static char const WAVESEQ3        [] = "WAVESEQ3          = ");
FLASH_DECLARE(static char const WAVESEQ4        [] = "WAVESEQ4          = ");
FLASH_DECLARE(static char const WAVESEQ5        [] = "WAVESEQ5          = ");
FLASH_DECLARE(static char const WAVESEQ6        [] = "WAVESEQ6          = ");
FLASH_DECLARE(static char const WAVESEQ7        [] = "WAVESEQ7          = ");
FLASH_DECLARE(static char const WAVESEQ8        [] = "WAVESEQ8          = ");
FLASH_DECLARE(static char const GO              [] = "GO                = ");
FLASH_DECLARE(static char const OVERDRIVE       [] = "OVERDRIVE         = ");
FLASH_DECLARE(static char const SUSTAINOFFSETPOS[] = "SUSTAINOFFSETPOS  = ");
FLASH_DECLARE(static char const SUSTAINOFFSETNEG[] = "SUSTAINOFFSETNEG  = ");
FLASH_DECLARE(static char const BREAKTIME       [] = "BREAKTIME         = ");
FLASH_DECLARE(static char const AUDIOCTRL       [] = "AUDIOCTRL         = ");
FLASH_DECLARE(static char const AUDMINLVL       [] = "AUDMINLVL         = ");
FLASH_DECLARE(static char const AUDMAXLVL       [] = "AUDMAXLVL         = ");
FLASH_DECLARE(static char const AUDMINDRIVE     [] = "AUDMINDRIVE       = ");
FLASH_DECLARE(static char const AUDMAXDRIVE     [] = "AUDMAXDRIVE       = ");
FLASH_DECLARE(static char const RATEDVOLT       [] = "RATEDVOLT         = ");
FLASH_DECLARE(static char const OVERDRIVECLAMP  [] = "OVERDRIVECLAMP    = ");
FLASH_DECLARE(static char const COMPRESULT      [] = "COMPRESULT        = ");
FLASH_DECLARE(static char const BACKEMF         [] = "BACKEMF           = ");
FLASH_DECLARE(static char const FEEDBACK        [] = "FEEDBACK          = ");
FLASH_DECLARE(static char const CONTROL1        [] = "CONTROL1          = ");
FLASH_DECLARE(static char const CONTROL2        [] = "CONTROL2          = ");
FLASH_DECLARE(static char const CONTROL3        [] = "CONTROL3          = ");
FLASH_DECLARE(static char const CONTROL4        [] = "CONTROL4          = ");
FLASH_DECLARE(static char const CONTROL5        [] = "CONTROL5          = ");
FLASH_DECLARE(static char const OLP             [] = "OLP               = ");
FLASH_DECLARE(static char const VBATMONITOR     [] = "VBATMONITOR       = ");
FLASH_DECLARE(static char const LRARESPERIOD    [] = "LRARESPERIOD      = ");

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

DRV2605_Control::DRV2605_Control(interface::DRV2605_Io & io, hal::interface::Delay & delay)
: _io   (io   ),
  _delay(delay)
{

}

DRV2605_Control::~DRV2605_Control()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool DRV2605_Control::reset()
{
  if(!_io.writeRegister(interface::Register::MODE, DRV2605_REG_MODE_DEV_RESET_bm)) return false;

  _delay.delay_ms(DEVICE_RESET_DURATION_ms);

  uint8_t reg_mode_content = 0;
  if(!_io.readRegister(interface::Register::MODE, &reg_mode_content)) return false;

  return ((reg_mode_content & DRV2605_REG_MODE_DEV_RESET_bm) == 0);
}

bool DRV2605_Control::setStandby()
{
  uint8_t reg_mode_content = 0;

  if(!_io.readRegister(interface::Register::MODE, &reg_mode_content)) return false;

  reg_mode_content |= DRV2605_REG_MODE_STANDBY_bm;

  if(!_io.writeRegister(interface::Register::MODE, reg_mode_content)) return false;

  return true;
}

bool DRV2605_Control::clrStandby()
{
  uint8_t reg_mode_content = 0;

  if(!_io.readRegister(interface::Register::MODE, &reg_mode_content)) return false;

  reg_mode_content &= ~(DRV2605_REG_MODE_STANDBY_bm);

  if(!_io.writeRegister(interface::Register::MODE, reg_mode_content)) return false;

  return true;
}

bool DRV2605_Control::setMode(interface::Mode const mode)
{
  uint8_t reg_mode_content = 0;

  if(!_io.readRegister(interface::Register::MODE, &reg_mode_content)) return false;

  reg_mode_content &= ~(DRV2605_REG_MODE_2_bm | DRV2605_REG_MODE_1_bm | DRV2605_REG_MODE_0_bm);
  reg_mode_content |= static_cast<uint8_t>(mode);

  if(!_io.writeRegister(interface::Register::MODE, reg_mode_content)) return false;

  return true;
}

bool DRV2605_Control::setWaveformLibrary(interface::WaveformLibrary const library)
{
  uint8_t reg_lib_content = 0;

  if(!_io.readRegister(interface::Register::LIB, &reg_lib_content)) return false;

  reg_lib_content &= ~(DRV2605_REG_LIB_LIBRARY_SEL_2_bm | DRV2605_REG_LIB_LIBRARY_SEL_1_bm | DRV2605_REG_LIB_LIBRARY_SEL_0_bm);
  reg_lib_content |= static_cast<uint8_t>(library);

  if(!_io.writeRegister(interface::Register::LIB, reg_lib_content)) return false;

  return true;
}

bool DRV2605_Control::setWaveform(interface::WaveformSequencer const sequencer, uint8_t const waveform)
{
  switch(sequencer)
  {
  case interface::WaveformSequencer::SEQ_1: return _io.writeRegister(interface::Register::WAVESEQ1, (waveform & 0x7F)); break;
  case interface::WaveformSequencer::SEQ_2: return _io.writeRegister(interface::Register::WAVESEQ2, (waveform & 0x7F)); break;
  case interface::WaveformSequencer::SEQ_3: return _io.writeRegister(interface::Register::WAVESEQ3, (waveform & 0x7F)); break;
  case interface::WaveformSequencer::SEQ_4: return _io.writeRegister(interface::Register::WAVESEQ4, (waveform & 0x7F)); break;
  case interface::WaveformSequencer::SEQ_5: return _io.writeRegister(interface::Register::WAVESEQ5, (waveform & 0x7F)); break;
  case interface::WaveformSequencer::SEQ_6: return _io.writeRegister(interface::Register::WAVESEQ6, (waveform & 0x7F)); break;
  case interface::WaveformSequencer::SEQ_7: return _io.writeRegister(interface::Register::WAVESEQ7, (waveform & 0x7F)); break;
  case interface::WaveformSequencer::SEQ_8: return _io.writeRegister(interface::Register::WAVESEQ8, (waveform & 0x7F)); break;
  default                                 : return false;                                                               break;
  }
}

bool DRV2605_Control::setActuator(interface::Actuator const actuator)
{
  uint8_t reg_feedback_content = 0;

  if(!_io.readRegister(interface::Register::FEEDBACK, &reg_feedback_content)) return false;

  reg_feedback_content &= ~(DRV2605_REG_FEEDBACK_N_ERM_LRA_bm);
  reg_feedback_content |= static_cast<uint8_t>(actuator);

  if(!_io.writeRegister(interface::Register::FEEDBACK, reg_feedback_content)) return false;

  return true;
}

bool DRV2605_Control::setGo()
{
  return _io.writeRegister(interface::Register::GO, DRV2605_REG_GO_GO_bm);
}

bool DRV2605_Control::clrGo()
{
  return _io.writeRegister(interface::Register::GO, 0);
}

void DRV2605_Control::debug_dumpAllRegs(debug::interface::Debug & debug_interface, hal::interface::Flash & flash)
{
  debug_dumpSingleReg(debug_interface, flash, STATUS          , interface::Register::STATUS          );
  debug_dumpSingleReg(debug_interface, flash, MODE            , interface::Register::MODE            );
  debug_dumpSingleReg(debug_interface, flash, RTP             , interface::Register::RTP             );
  debug_dumpSingleReg(debug_interface, flash, LIB             , interface::Register::LIB             );
  debug_dumpSingleReg(debug_interface, flash, WAVESEQ1        , interface::Register::WAVESEQ1        );
  debug_dumpSingleReg(debug_interface, flash, WAVESEQ2        , interface::Register::WAVESEQ2        );
  debug_dumpSingleReg(debug_interface, flash, WAVESEQ3        , interface::Register::WAVESEQ3        );
  debug_dumpSingleReg(debug_interface, flash, WAVESEQ4        , interface::Register::WAVESEQ4        );
  debug_dumpSingleReg(debug_interface, flash, WAVESEQ5        , interface::Register::WAVESEQ5        );
  debug_dumpSingleReg(debug_interface, flash, WAVESEQ6        , interface::Register::WAVESEQ6        );
  debug_dumpSingleReg(debug_interface, flash, WAVESEQ7        , interface::Register::WAVESEQ7        );
  debug_dumpSingleReg(debug_interface, flash, WAVESEQ8        , interface::Register::WAVESEQ8        );
  debug_dumpSingleReg(debug_interface, flash, GO              , interface::Register::GO              );
  debug_dumpSingleReg(debug_interface, flash, OVERDRIVE       , interface::Register::OVERDRIVE       );
  debug_dumpSingleReg(debug_interface, flash, SUSTAINOFFSETPOS, interface::Register::SUSTAINOFFSETPOS);
  debug_dumpSingleReg(debug_interface, flash, SUSTAINOFFSETNEG, interface::Register::SUSTAINOFFSETNEG);
  debug_dumpSingleReg(debug_interface, flash, BREAKTIME       , interface::Register::BREAKTIME       );
  debug_dumpSingleReg(debug_interface, flash, AUDIOCTRL       , interface::Register::AUDIOCTRL       );
  debug_dumpSingleReg(debug_interface, flash, AUDMINLVL       , interface::Register::AUDMINLVL       );
  debug_dumpSingleReg(debug_interface, flash, AUDMAXLVL       , interface::Register::AUDMAXLVL       );
  debug_dumpSingleReg(debug_interface, flash, AUDMINDRIVE     , interface::Register::AUDMINDRIVE     );
  debug_dumpSingleReg(debug_interface, flash, AUDMAXDRIVE     , interface::Register::AUDMAXDRIVE     );
  debug_dumpSingleReg(debug_interface, flash, RATEDVOLT       , interface::Register::RATEDVOLT       );
  debug_dumpSingleReg(debug_interface, flash, OVERDRIVECLAMP  , interface::Register::OVERDRIVECLAMP  );
  debug_dumpSingleReg(debug_interface, flash, COMPRESULT      , interface::Register::COMPRESULT      );
  debug_dumpSingleReg(debug_interface, flash, BACKEMF         , interface::Register::BACKEMF         );
  debug_dumpSingleReg(debug_interface, flash, FEEDBACK        , interface::Register::FEEDBACK        );
  debug_dumpSingleReg(debug_interface, flash, CONTROL1        , interface::Register::CONTROL1        );
  debug_dumpSingleReg(debug_interface, flash, CONTROL2        , interface::Register::CONTROL2        );
  debug_dumpSingleReg(debug_interface, flash, CONTROL3        , interface::Register::CONTROL3        );
  debug_dumpSingleReg(debug_interface, flash, CONTROL4        , interface::Register::CONTROL4        );
  debug_dumpSingleReg(debug_interface, flash, CONTROL5        , interface::Register::CONTROL5        );
  debug_dumpSingleReg(debug_interface, flash, OLP             , interface::Register::OLP             );
  debug_dumpSingleReg(debug_interface, flash, VBATMONITOR     , interface::Register::VBATMONITOR     );
  debug_dumpSingleReg(debug_interface, flash, LRARESPERIOD    , interface::Register::LRARESPERIOD    );
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void DRV2605_Control::debug_dumpSingleReg(debug::interface::Debug & debug_interface, hal::interface::Flash & flash, char const * msg, interface::Register const reg)
{
  char    msg_ram[32];
  uint8_t reg_content = 0;

  flash.readStringFromFlash(msg_ram, msg);
  _io.readRegister(reg, &reg_content);

  debug_interface.print("%s%02X\n\r", msg_ram, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* DRV2605 */

} /* haptic */

} /* driver */

} /* spectre */
