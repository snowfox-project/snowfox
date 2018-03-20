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

#include <spectre/driver/sensor/AS5600/AS5600_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace AS5600
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

AS5600_Control::AS5600_Control(interface::AS5600_Io & io)
: _io(io)
{

}

AS5600_Control::~AS5600_Control()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool AS5600_Control::setPowerMode(interface::PowerModeSelect const sel)
{
  uint8_t conf_low_byte_content = 0;

  if(!_io.readRegister(interface::Register::CONF_LOW_BYTE, &conf_low_byte_content)) return false;

  conf_low_byte_content &= ~(AS5600_CONF_LOW_BYTE_REG_PM1_bm | AS5600_CONF_LOW_BYTE_REG_PM0_bm);
  conf_low_byte_content |= static_cast<uint8_t>(sel);

  if(!_io.writeRegister(interface::Register::CONF_LOW_BYTE, conf_low_byte_content)) return false;

  return true;
}

bool AS5600_Control::setHysteresis(interface::HysteresisSelect const sel)
{
  uint8_t conf_low_byte_content = 0;

  if(!_io.readRegister(interface::Register::CONF_LOW_BYTE, &conf_low_byte_content)) return false;

  conf_low_byte_content &= ~(AS5600_CONF_LOW_BYTE_REG_HYST1_bm | AS5600_CONF_LOW_BYTE_REG_HYST0_bm);
  conf_low_byte_content |= static_cast<uint8_t>(sel);

  if(!_io.writeRegister(interface::Register::CONF_LOW_BYTE, conf_low_byte_content)) return false;

  return true;
}

bool AS5600_Control::setOutputStage(interface::OutputStageSelect const sel)
{
  uint8_t conf_low_byte_content = 0;

  if(!_io.readRegister(interface::Register::CONF_LOW_BYTE, &conf_low_byte_content)) return false;

  conf_low_byte_content &= ~(AS5600_CONF_LOW_BYTE_REG_OUTS1_bm | AS5600_CONF_LOW_BYTE_REG_OUTS0_bm);
  conf_low_byte_content |= static_cast<uint8_t>(sel);

  if(!_io.writeRegister(interface::Register::CONF_LOW_BYTE, conf_low_byte_content)) return false;

  return true;
}

bool AS5600_Control::setPWMFrequency(interface::PWMFrequencySelect const sel)
{
  uint8_t conf_low_byte_content = 0;

  if(!_io.readRegister(interface::Register::CONF_LOW_BYTE, &conf_low_byte_content)) return false;

  conf_low_byte_content &= ~(AS5600_CONF_LOW_BYTE_REG_PWMF1_bm | AS5600_CONF_LOW_BYTE_REG_PWMF0_bm);
  conf_low_byte_content |= static_cast<uint8_t>(sel);

  if(!_io.writeRegister(interface::Register::CONF_LOW_BYTE, conf_low_byte_content)) return false;

  return true;
}

bool AS5600_Control::setSlowFilter(interface::SlowFilterSelect const sel)
{
  uint8_t conf_high_byte_content = 0;

  if(!_io.readRegister(interface::Register::CONF_HIGH_BYTE, &conf_high_byte_content)) return false;

  conf_high_byte_content &= ~(AS5600_CONF_HIGH_BYTE_REG_SF1_bm | AS5600_CONF_HIGH_BYTE_REG_SF0_bm);
  conf_high_byte_content |= static_cast<uint8_t>(sel);

  if(!_io.writeRegister(interface::Register::CONF_HIGH_BYTE, conf_high_byte_content)) return false;

  return true;
}

bool AS5600_Control::setFastFilterThreshold(interface::FastFilterThreshold const sel)
{
  uint8_t conf_high_byte_content = 0;

  if(!_io.readRegister(interface::Register::CONF_HIGH_BYTE, &conf_high_byte_content)) return false;

  conf_high_byte_content &= ~(AS5600_CONF_HIGH_BYTE_REG_FTH2_bm | AS5600_CONF_HIGH_BYTE_REG_FTH1_bm | AS5600_CONF_HIGH_BYTE_REG_FTH0_bm);
  conf_high_byte_content |= static_cast<uint8_t>(sel);

  if(!_io.writeRegister(interface::Register::CONF_HIGH_BYTE, conf_high_byte_content)) return false;

  return true;
}

bool AS5600_Control::enableWatchog()
{
  uint8_t conf_high_byte_content = 0;

  if(!_io.readRegister(interface::Register::CONF_HIGH_BYTE, &conf_high_byte_content)) return false;

  conf_high_byte_content |= AS5600_CONF_HIGH_BYTE_REG_WD_bm;

  if(!_io.writeRegister(interface::Register::CONF_HIGH_BYTE, conf_high_byte_content)) return false;

  return true;
}

bool AS5600_Control::disableWatchog()
{
  uint8_t conf_high_byte_content = 0;

  if(!_io.readRegister(interface::Register::CONF_HIGH_BYTE, &conf_high_byte_content)) return false;

  conf_high_byte_content &= ~AS5600_CONF_HIGH_BYTE_REG_WD_bm;

  if(!_io.writeRegister(interface::Register::CONF_HIGH_BYTE, conf_high_byte_content)) return false;

  return true;
}

bool AS5600_Control::setAngularStartPosition(uint16_t const angle_start)
{
  uint8_t const angle_start_buf[2] =
  {
      (uint8_t)((angle_start & 0xFF00) >> 8),
      (uint8_t)((angle_start & 0x00FF) >> 0)
  };

  return _io.writeRegister(interface::Register::ZPOS_HIGH_BYTE, angle_start_buf, 2);
}

bool AS5600_Control::setAngularStopPosition(uint16_t const angle_stop)
{
  uint8_t const angle_stop_buf[2] =
  {
      (uint8_t)((angle_stop & 0xFF00) >> 8),
      (uint8_t)((angle_stop & 0x00FF) >> 0)
  };

  return _io.writeRegister(interface::Register::MPOS_HIGH_BYTE, angle_stop_buf, 2);
}

bool AS5600_Control::setMaximumAngle(uint16_t const angle_max)
{
  uint8_t const angle_max_buf[2] =
  {
      (uint8_t)((angle_max & 0xFF00) >> 8),
      (uint8_t)((angle_max & 0x00FF) >> 0)
  };

  return _io.writeRegister(interface::Register::MANG_HIGH_BYTE, angle_max_buf, 2);
}

bool AS5600_Control::readAngle(uint16_t * angle)
{
  uint8_t angle_buf[2] = {0};

  if(!_io.readRegister(interface::Register::ANGLE_HIGH_BYTE, angle_buf, 2)) return false;

  *angle  = (static_cast<uint16_t>(angle_buf[0]) << 8);
  *angle += (static_cast<uint16_t>(angle_buf[1]) << 0);

  return true;
}

bool AS5600_Control::readAngleRaw(uint16_t * angle_raw)
{
  uint8_t angle_raw_buf[2] = {0};

  if(!_io.readRegister(interface::Register::RAW_ANGLE_HIGH_BYTE, angle_raw_buf, 2)) return false;

  *angle_raw  = (static_cast<uint16_t>(angle_raw_buf[0]) << 8);
  *angle_raw += (static_cast<uint16_t>(angle_raw_buf[1]) << 0);

  return true;
}

bool AS5600_Control::readStatus(uint8_t * status)
{
  return _io.readRegister(interface::Register::STATUS, status);
}

bool AS5600_Control::readAGC(uint8_t * agc)
{
  return _io.readRegister(interface::Register::AGC, agc);
}

bool AS5600_Control::readMagnitude(uint16_t * mag)
{
  uint8_t mag_buf[2] = {0};

  if(!_io.readRegister(interface::Register::MAGNITUDE_HIGH_BYTE, mag_buf, 2)) return false;

  *mag  = (static_cast<uint16_t>(mag_buf[0]) << 8);
  *mag += (static_cast<uint16_t>(mag_buf[1]) << 0);

  return true;
}

bool AS5600_Control::isMagnetTooStrong(uint8_t const status)
{
  return (status & AS5600_STATUS_REG_MH_bm) != 0;
}

bool AS5600_Control::isMagnetTooWeak(uint8_t const status)
{
  return (status & AS5600_STATUS_REG_ML_bm) != 0;
}

bool AS5600_Control::isMagnetDetected(uint8_t const status)
{
  return (status & AS5600_STATUS_REG_MD_bm) != 0;
}

void AS5600_Control::debug_dumpAllRegs(debug::interface::Debug & debug_interface)
{
  debug_dumpSingleReg(debug_interface, "ZMCO                = ", interface::Register::ZMCO               );
  debug_dumpSingleReg(debug_interface, "ZPOS_HIGH_BYTE      = ", interface::Register::ZPOS_HIGH_BYTE     );
  debug_dumpSingleReg(debug_interface, "ZPOS_LOW_BYTE       = ", interface::Register::ZPOS_LOW_BYTE      );
  debug_dumpSingleReg(debug_interface, "MPOS_HIGH_BYTE      = ", interface::Register::MPOS_HIGH_BYTE     );
  debug_dumpSingleReg(debug_interface, "MPOS_LOW_BYTE       = ", interface::Register::MPOS_LOW_BYTE      );
  debug_dumpSingleReg(debug_interface, "MANG_HIGH_BYTE      = ", interface::Register::MANG_HIGH_BYTE     );
  debug_dumpSingleReg(debug_interface, "MANG_LOW_BYTE       = ", interface::Register::MANG_LOW_BYTE      );
  debug_dumpSingleReg(debug_interface, "CONF_HIGH_BYTE      = ", interface::Register::CONF_HIGH_BYTE     );
  debug_dumpSingleReg(debug_interface, "CONF_LOW_BYTE       = ", interface::Register::CONF_LOW_BYTE      );
  debug_dumpSingleReg(debug_interface, "RAW_ANGLE_HIGH_BYTE = ", interface::Register::RAW_ANGLE_HIGH_BYTE);
  debug_dumpSingleReg(debug_interface, "RAW_ANGLE_LOW_BYTE  = ", interface::Register::RAW_ANGLE_LOW_BYTE );
  debug_dumpSingleReg(debug_interface, "ANGLE_HIGH_BYTE     = ", interface::Register::ANGLE_HIGH_BYTE    );
  debug_dumpSingleReg(debug_interface, "ANGLE_LOW_BYTE      = ", interface::Register::ANGLE_LOW_BYTE     );
  debug_dumpSingleReg(debug_interface, "AGC                 = ", interface::Register::AGC                );
  debug_dumpSingleReg(debug_interface, "MAGNITUDE_HIGH_BYTE = ", interface::Register::MAGNITUDE_HIGH_BYTE);
  debug_dumpSingleReg(debug_interface, "MAGNITUDE_LOW_BYTE  = ", interface::Register::MAGNITUDE_LOW_BYTE );
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void AS5600_Control::debug_dumpSingleReg(debug::interface::Debug & debug_interface, char const * msg, interface::Register const reg)
{
  uint8_t reg_content = 0;

  _io.readRegister(reg, &reg_content);

  debug_interface.print("%s%X\n", msg, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AS5600 */

} /* sensor */

} /* driver */

} /* spectre */
