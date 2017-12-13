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

#include <spectre/driver/haptic/DRV2605/DRV2605.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
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

DRV2605::DRV2605(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master, hal::interface::Delay & delay)
: _i2c_address(i2c_address),
  _i2c_master (i2c_master ),
  _delay      (delay      )
{

}

DRV2605::~DRV2605()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool DRV2605::setGo()
{
  return writeSingleRegister(REG_GO, DRV2605_REG_GO_GO_bm);
}

bool DRV2605::clrGo()
{
  return writeSingleRegister(REG_GO, 0);
}

bool DRV2605::reset()
{
  if(!writeSingleRegister(REG_MODE, DRV2605_REG_MODE_DEV_RESET_bm)) return false;

  _delay.delay_ms(DEVICE_RESET_DURATION_ms);

  uint8_t reg_mode_content = 0;
  if(!readSingleRegister(REG_MODE, &reg_mode_content)) return false;

  return ((reg_mode_content & DRV2605_REG_MODE_DEV_RESET_bm) == 0);
}

bool DRV2605::setStandby()
{
  uint8_t reg_mode_content = 0;

  if(!readSingleRegister(REG_MODE, &reg_mode_content)) return false;

  reg_mode_content |= DRV2605_REG_MODE_STANDBY_bm;

  if(!writeSingleRegister(REG_MODE, reg_mode_content)) return false;

  return true;
}

bool DRV2605::clrStandby()
{
  uint8_t reg_mode_content = 0;

  if(!readSingleRegister(REG_MODE, &reg_mode_content)) return false;

  reg_mode_content &= ~(DRV2605_REG_MODE_STANDBY_bm);

  if(!writeSingleRegister(REG_MODE, reg_mode_content)) return false;

  return true;
}

bool DRV2605::setMode(eDRV2605ModeSelect const mode)
{
  uint8_t reg_mode_content = 0;

  if(!readSingleRegister(REG_MODE, &reg_mode_content)) return false;

  reg_mode_content &= ~(DRV2605_REG_MODE_2_bm | DRV2605_REG_MODE_1_bm | DRV2605_REG_MODE_0_bm);
  reg_mode_content |= static_cast<uint8_t>(mode);

  if(!writeSingleRegister(REG_MODE, reg_mode_content)) return false;

  return true;
}

bool DRV2605::setWaveformLibrary(eDRV2605WaveformLibrarySelect const library)
{
  uint8_t reg_lib_content = 0;

  if(!readSingleRegister(REG_LIB, &reg_lib_content)) return false;

  reg_lib_content &= ~(DRV2605_REG_LIB_LIBRARY_SEL_2_bm | DRV2605_REG_LIB_LIBRARY_SEL_1_bm | DRV2605_REG_LIB_LIBRARY_SEL_0_bm);
  reg_lib_content |= static_cast<uint8_t>(library);

  if(!writeSingleRegister(REG_LIB, reg_lib_content)) return false;

  return true;
}

bool DRV2605::setWaveform(eDRV2605WaveformSequencerSelect const sequencer, uint8_t const waveform)
{
  return writeSingleRegister(REG_WAVESEQ1 + sequencer, (waveform & 0x7F));
}

bool DRV2605::setActuator(eDRV2605ActuatorSelect const actuator)
{
  uint8_t reg_feedback_content = 0;

  if(!readSingleRegister(REG_FEEDBACK, &reg_feedback_content)) return false;

  reg_feedback_content &= ~(DRV2605_REG_FEEDBACK_N_ERM_LRA_bm);
  reg_feedback_content |= static_cast<uint8_t>(actuator);

  if(!writeSingleRegister(REG_FEEDBACK, reg_feedback_content)) return false;

  return true;
}

void DRV2605::debug_dumpAllRegs(debug::interface::Debug & debug_interface)
{
  debug_dumpSingleReg(debug_interface, "REG_STATUS            = ", REG_STATUS          );
  debug_dumpSingleReg(debug_interface, "REG_MODE              = ", REG_MODE            );
  debug_dumpSingleReg(debug_interface, "REG_RTP               = ", REG_RTP             );
  debug_dumpSingleReg(debug_interface, "REG_LIB               = ", REG_LIB             );
  debug_dumpSingleReg(debug_interface, "REG_WAVESEQ1          = ", REG_WAVESEQ1        );
  debug_dumpSingleReg(debug_interface, "REG_WAVESEQ2          = ", REG_WAVESEQ2        );
  debug_dumpSingleReg(debug_interface, "REG_WAVESEQ3          = ", REG_WAVESEQ3        );
  debug_dumpSingleReg(debug_interface, "REG_WAVESEQ4          = ", REG_WAVESEQ4        );
  debug_dumpSingleReg(debug_interface, "REG_WAVESEQ5          = ", REG_WAVESEQ5        );
  debug_dumpSingleReg(debug_interface, "REG_WAVESEQ6          = ", REG_WAVESEQ6        );
  debug_dumpSingleReg(debug_interface, "REG_WAVESEQ7          = ", REG_WAVESEQ7        );
  debug_dumpSingleReg(debug_interface, "REG_WAVESEQ8          = ", REG_WAVESEQ8        );
  debug_dumpSingleReg(debug_interface, "REG_GO                = ", REG_GO              );
  debug_dumpSingleReg(debug_interface, "REG_OVERDRIVE         = ", REG_OVERDRIVE       );
  debug_dumpSingleReg(debug_interface, "REG_SUSTAINOFFSETPOS  = ", REG_SUSTAINOFFSETPOS);
  debug_dumpSingleReg(debug_interface, "REG_SUSTAINOFFSETNEG  = ", REG_SUSTAINOFFSETNEG);
  debug_dumpSingleReg(debug_interface, "REG_BREAKTIME         = ", REG_BREAKTIME       );
  debug_dumpSingleReg(debug_interface, "REG_AUDIOCTRL         = ", REG_AUDIOCTRL       );
  debug_dumpSingleReg(debug_interface, "REG_AUDMINLVL         = ", REG_AUDMINLVL       );
  debug_dumpSingleReg(debug_interface, "REG_AUDMAXLVL         = ", REG_AUDMAXLVL       );
  debug_dumpSingleReg(debug_interface, "REG_AUDMINDRIVE       = ", REG_AUDMINDRIVE     );
  debug_dumpSingleReg(debug_interface, "REG_AUDMAXDRIVE       = ", REG_AUDMAXDRIVE     );
  debug_dumpSingleReg(debug_interface, "REG_RATEDVOLT         = ", REG_RATEDVOLT       );
  debug_dumpSingleReg(debug_interface, "REG_OVERDRIVECLAMP    = ", REG_OVERDRIVECLAMP  );
  debug_dumpSingleReg(debug_interface, "REG_COMPRESULT        = ", REG_COMPRESULT      );
  debug_dumpSingleReg(debug_interface, "REG_BACKEMF           = ", REG_BACKEMF         );
  debug_dumpSingleReg(debug_interface, "REG_FEEDBACK          = ", REG_FEEDBACK        );
  debug_dumpSingleReg(debug_interface, "REG_CONTROL1          = ", REG_CONTROL1        );
  debug_dumpSingleReg(debug_interface, "REG_CONTROL2          = ", REG_CONTROL2        );
  debug_dumpSingleReg(debug_interface, "REG_CONTROL3          = ", REG_CONTROL3        );
  debug_dumpSingleReg(debug_interface, "REG_CONTROL4          = ", REG_CONTROL4        );
  debug_dumpSingleReg(debug_interface, "REG_CONTROL5          = ", REG_CONTROL5        );
  debug_dumpSingleReg(debug_interface, "REG_OLP               = ", REG_OLP             );
  debug_dumpSingleReg(debug_interface, "REG_VBATMONITOR       = ", REG_VBATMONITOR     );
  debug_dumpSingleReg(debug_interface, "REG_LRARESPERIOD      = ", REG_LRARESPERIOD    );
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

bool DRV2605::readSingleRegister(uint8_t const reg_addr, uint8_t * data)
{
  if(!_i2c_master.begin      (_i2c_address, false  )) return false;
  if(!_i2c_master.write      (reg_addr             )) return false;
  if(!_i2c_master.requestFrom(_i2c_address, data, 1)) return false;

  return true;
}

bool DRV2605::writeSingleRegister(uint8_t const reg_addr, uint8_t const data)
{
  if(!_i2c_master.begin(_i2c_address, false)) return false;
  if(!_i2c_master.write(reg_addr           )) return false;
  if(!_i2c_master.write(data               )) return false;
      _i2c_master.end  (                   );

  return true;
}

void DRV2605::debug_dumpSingleReg(debug::interface::Debug & debug_interface, char const * msg, eDRV2605RegisterSelect const reg_sel)
{
  uint8_t reg_content = 0;

  readSingleRegister(reg_sel, &reg_content);

  debug_interface.print("%s%X\n", msg, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* DRV2605 */

} /* driver */

} /* spectre */
