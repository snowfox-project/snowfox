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
 * INCLUDE
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

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* DRV2605 */

} /* haptic */

} /* driver */

} /* spectre */
