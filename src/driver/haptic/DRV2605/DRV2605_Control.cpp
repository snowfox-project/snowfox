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
  if(!_io.writeSingleRegister(interface::Register::MODE, DRV2605_REG_MODE_DEV_RESET_bm)) return false;

  _delay.delay_ms(DEVICE_RESET_DURATION_ms);

  uint8_t reg_mode_content = 0;
  if(!_io.readSingleRegister(interface::Register::MODE, &reg_mode_content)) return false;

  return ((reg_mode_content & DRV2605_REG_MODE_DEV_RESET_bm) == 0);
}

bool DRV2605_Control::setStandby()
{
  uint8_t reg_mode_content = 0;

  if(!_io.readSingleRegister(interface::Register::MODE, &reg_mode_content)) return false;

  reg_mode_content |= DRV2605_REG_MODE_STANDBY_bm;

  if(!_io.writeSingleRegister(interface::Register::MODE, reg_mode_content)) return false;

  return true;
}

bool DRV2605_Control::clrStandby()
{
  uint8_t reg_mode_content = 0;

  if(!_io.readSingleRegister(interface::Register::MODE, &reg_mode_content)) return false;

  reg_mode_content &= ~(DRV2605_REG_MODE_STANDBY_bm);

  if(!_io.writeSingleRegister(interface::Register::MODE, reg_mode_content)) return false;

  return true;
}

bool DRV2605_Control::setMode(interface::ModeSelect const mode)
{
  uint8_t reg_mode_content = 0;

  if(!_io.readSingleRegister(interface::Register::MODE, &reg_mode_content)) return false;

  reg_mode_content &= ~(DRV2605_REG_MODE_2_bm | DRV2605_REG_MODE_1_bm | DRV2605_REG_MODE_0_bm);
  reg_mode_content |= static_cast<uint8_t>(mode);

  if(!_io.writeSingleRegister(interface::Register::MODE, reg_mode_content)) return false;

  return true;
}

bool DRV2605_Control::setWaveformLibrary(interface::WaveformLibrarySelect const library)
{
  uint8_t reg_lib_content = 0;

  if(!_io.readSingleRegister(interface::Register::LIB, &reg_lib_content)) return false;

  reg_lib_content &= ~(DRV2605_REG_LIB_LIBRARY_SEL_2_bm | DRV2605_REG_LIB_LIBRARY_SEL_1_bm | DRV2605_REG_LIB_LIBRARY_SEL_0_bm);
  reg_lib_content |= static_cast<uint8_t>(library);

  if(!_io.writeSingleRegister(interface::Register::LIB, reg_lib_content)) return false;

  return true;
}

bool DRV2605_Control::setWaveform(interface::WaveformSequencerSelect const sequencer, uint8_t const waveform)
{
  switch(sequencer)
  {
  case interface::WAVEFORM_SEQUENCER_1: return _io.writeSingleRegister(interface::Register::WAVESEQ1, (waveform & 0x7F)); break;
  case interface::WAVEFORM_SEQUENCER_2: return _io.writeSingleRegister(interface::Register::WAVESEQ2, (waveform & 0x7F)); break;
  case interface::WAVEFORM_SEQUENCER_3: return _io.writeSingleRegister(interface::Register::WAVESEQ3, (waveform & 0x7F)); break;
  case interface::WAVEFORM_SEQUENCER_4: return _io.writeSingleRegister(interface::Register::WAVESEQ4, (waveform & 0x7F)); break;
  case interface::WAVEFORM_SEQUENCER_5: return _io.writeSingleRegister(interface::Register::WAVESEQ5, (waveform & 0x7F)); break;
  case interface::WAVEFORM_SEQUENCER_6: return _io.writeSingleRegister(interface::Register::WAVESEQ6, (waveform & 0x7F)); break;
  case interface::WAVEFORM_SEQUENCER_7: return _io.writeSingleRegister(interface::Register::WAVESEQ7, (waveform & 0x7F)); break;
  case interface::WAVEFORM_SEQUENCER_8: return _io.writeSingleRegister(interface::Register::WAVESEQ8, (waveform & 0x7F)); break;
  default                             : return false;                                                               break;
  }
}

bool DRV2605_Control::setActuator(interface::ActuatorSelect const actuator)
{
  uint8_t reg_feedback_content = 0;

  if(!_io.readSingleRegister(interface::Register::FEEDBACK, &reg_feedback_content)) return false;

  reg_feedback_content &= ~(DRV2605_REG_FEEDBACK_N_ERM_LRA_bm);
  reg_feedback_content |= static_cast<uint8_t>(actuator);

  if(!_io.writeSingleRegister(interface::Register::FEEDBACK, reg_feedback_content)) return false;

  return true;
}

bool DRV2605_Control::setGo()
{
  return _io.writeSingleRegister(interface::Register::GO, DRV2605_REG_GO_GO_bm);
}

bool DRV2605_Control::clrGo()
{
  return _io.writeSingleRegister(interface::Register::GO, 0);
}

void DRV2605_Control::debug_dumpAllRegs(debug::interface::Debug & debug_interface)
{
  debug_dumpSingleReg(debug_interface, "REG_STATUS            = ", interface::Register::STATUS          );
  debug_dumpSingleReg(debug_interface, "REG_MODE              = ", interface::Register::MODE            );
  debug_dumpSingleReg(debug_interface, "REG_RTP               = ", interface::Register::RTP             );
  debug_dumpSingleReg(debug_interface, "REG_LIB               = ", interface::Register::LIB             );
  debug_dumpSingleReg(debug_interface, "REG_WAVESEQ1          = ", interface::Register::WAVESEQ1        );
  debug_dumpSingleReg(debug_interface, "REG_WAVESEQ2          = ", interface::Register::WAVESEQ2        );
  debug_dumpSingleReg(debug_interface, "REG_WAVESEQ3          = ", interface::Register::WAVESEQ3        );
  debug_dumpSingleReg(debug_interface, "REG_WAVESEQ4          = ", interface::Register::WAVESEQ4        );
  debug_dumpSingleReg(debug_interface, "REG_WAVESEQ5          = ", interface::Register::WAVESEQ5        );
  debug_dumpSingleReg(debug_interface, "REG_WAVESEQ6          = ", interface::Register::WAVESEQ6        );
  debug_dumpSingleReg(debug_interface, "REG_WAVESEQ7          = ", interface::Register::WAVESEQ7        );
  debug_dumpSingleReg(debug_interface, "REG_WAVESEQ8          = ", interface::Register::WAVESEQ8        );
  debug_dumpSingleReg(debug_interface, "REG_GO                = ", interface::Register::GO              );
  debug_dumpSingleReg(debug_interface, "REG_OVERDRIVE         = ", interface::Register::OVERDRIVE       );
  debug_dumpSingleReg(debug_interface, "REG_SUSTAINOFFSETPOS  = ", interface::Register::SUSTAINOFFSETPOS);
  debug_dumpSingleReg(debug_interface, "REG_SUSTAINOFFSETNEG  = ", interface::Register::SUSTAINOFFSETNEG);
  debug_dumpSingleReg(debug_interface, "REG_BREAKTIME         = ", interface::Register::BREAKTIME       );
  debug_dumpSingleReg(debug_interface, "REG_AUDIOCTRL         = ", interface::Register::AUDIOCTRL       );
  debug_dumpSingleReg(debug_interface, "REG_AUDMINLVL         = ", interface::Register::AUDMINLVL       );
  debug_dumpSingleReg(debug_interface, "REG_AUDMAXLVL         = ", interface::Register::AUDMAXLVL       );
  debug_dumpSingleReg(debug_interface, "REG_AUDMINDRIVE       = ", interface::Register::AUDMINDRIVE     );
  debug_dumpSingleReg(debug_interface, "REG_AUDMAXDRIVE       = ", interface::Register::AUDMAXDRIVE     );
  debug_dumpSingleReg(debug_interface, "REG_RATEDVOLT         = ", interface::Register::RATEDVOLT       );
  debug_dumpSingleReg(debug_interface, "REG_OVERDRIVECLAMP    = ", interface::Register::OVERDRIVECLAMP  );
  debug_dumpSingleReg(debug_interface, "REG_COMPRESULT        = ", interface::Register::COMPRESULT      );
  debug_dumpSingleReg(debug_interface, "REG_BACKEMF           = ", interface::Register::BACKEMF         );
  debug_dumpSingleReg(debug_interface, "REG_FEEDBACK          = ", interface::Register::FEEDBACK        );
  debug_dumpSingleReg(debug_interface, "REG_CONTROL1          = ", interface::Register::CONTROL1        );
  debug_dumpSingleReg(debug_interface, "REG_CONTROL2          = ", interface::Register::CONTROL2        );
  debug_dumpSingleReg(debug_interface, "REG_CONTROL3          = ", interface::Register::CONTROL3        );
  debug_dumpSingleReg(debug_interface, "REG_CONTROL4          = ", interface::Register::CONTROL4        );
  debug_dumpSingleReg(debug_interface, "REG_CONTROL5          = ", interface::Register::CONTROL5        );
  debug_dumpSingleReg(debug_interface, "REG_OLP               = ", interface::Register::OLP             );
  debug_dumpSingleReg(debug_interface, "REG_VBATMONITOR       = ", interface::Register::VBATMONITOR     );
  debug_dumpSingleReg(debug_interface, "REG_LRARESPERIOD      = ", interface::Register::LRARESPERIOD    );
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void DRV2605_Control::debug_dumpSingleReg(debug::interface::Debug & debug_interface, char const * msg, interface::Register const reg)
{
  uint8_t reg_content = 0;

  _io.readSingleRegister(reg, &reg_content);

  debug_interface.print("%s%X\n", msg, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* DRV2605 */

} /* haptic */

} /* driver */

} /* spectre */
