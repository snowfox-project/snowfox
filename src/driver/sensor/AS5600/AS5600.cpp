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

#include <spectre/driver/sensor/AS5600/AS5600.h>

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

AS5600::AS5600(AS5600_IO_Interface & io)
: _io(io)
{

}

AS5600::~AS5600()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool AS5600::setPowerMode(PowerModeSelect const sel)
{
  uint8_t conf_low_byte_content = 0;

  if(!readSingleRegister(REG_CONF_LOW_BYTE, &conf_low_byte_content)) return false;

  conf_low_byte_content &= ~(AS5600_CONF_LOW_BYTE_REG_PM1_bm | AS5600_CONF_LOW_BYTE_REG_PM0_bm);
  conf_low_byte_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CONF_LOW_BYTE, conf_low_byte_content)) return false;

  return true;
}

bool AS5600::setHysteresis(HysteresisSelect const sel)
{
  uint8_t conf_low_byte_content = 0;

  if(!readSingleRegister(REG_CONF_LOW_BYTE, &conf_low_byte_content)) return false;

  conf_low_byte_content &= ~(AS5600_CONF_LOW_BYTE_REG_HYST1_bm | AS5600_CONF_LOW_BYTE_REG_HYST0_bm);
  conf_low_byte_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CONF_LOW_BYTE, conf_low_byte_content)) return false;

  return true;
}

bool AS5600::setOutputStage(OutputStageSelect const sel)
{
  uint8_t conf_low_byte_content = 0;

  if(!readSingleRegister(REG_CONF_LOW_BYTE, &conf_low_byte_content)) return false;

  conf_low_byte_content &= ~(AS5600_CONF_LOW_BYTE_REG_OUTS1_bm | AS5600_CONF_LOW_BYTE_REG_OUTS0_bm);
  conf_low_byte_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CONF_LOW_BYTE, conf_low_byte_content)) return false;

  return true;
}

bool AS5600::setPWMFrequency(PWMFrequencySelect const sel)
{
  uint8_t conf_low_byte_content = 0;

  if(!readSingleRegister(REG_CONF_LOW_BYTE, &conf_low_byte_content)) return false;

  conf_low_byte_content &= ~(AS5600_CONF_LOW_BYTE_REG_PWMF1_bm | AS5600_CONF_LOW_BYTE_REG_PWMF0_bm);
  conf_low_byte_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CONF_LOW_BYTE, conf_low_byte_content)) return false;

  return true;
}

bool AS5600::setSlowFilter(SlowFilterSelect const sel)
{
  uint8_t conf_high_byte_content = 0;

  if(!readSingleRegister(REG_CONF_HIGH_BYTE, &conf_high_byte_content)) return false;

  conf_high_byte_content &= ~(AS5600_CONF_HIGH_BYTE_REG_SF1_bm | AS5600_CONF_HIGH_BYTE_REG_SF0_bm);
  conf_high_byte_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CONF_HIGH_BYTE, conf_high_byte_content)) return false;

  return true;
}

bool AS5600::setFastFilterThreshold(FastFilterThreshold const sel)
{
  uint8_t conf_high_byte_content = 0;

  if(!readSingleRegister(REG_CONF_HIGH_BYTE, &conf_high_byte_content)) return false;

  conf_high_byte_content &= ~(AS5600_CONF_HIGH_BYTE_REG_FTH2_bm | AS5600_CONF_HIGH_BYTE_REG_FTH1_bm | AS5600_CONF_HIGH_BYTE_REG_FTH0_bm);
  conf_high_byte_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CONF_HIGH_BYTE, conf_high_byte_content)) return false;

  return true;
}

bool AS5600::enableWatchog()
{
  uint8_t conf_high_byte_content = 0;

  if(!readSingleRegister(REG_CONF_HIGH_BYTE, &conf_high_byte_content)) return false;

  conf_high_byte_content |= AS5600_CONF_HIGH_BYTE_REG_WD_bm;

  if(!writeSingleRegister(REG_CONF_HIGH_BYTE, conf_high_byte_content)) return false;

  return true;
}

bool AS5600::disableWatchog()
{
  uint8_t conf_high_byte_content = 0;

  if(!readSingleRegister(REG_CONF_HIGH_BYTE, &conf_high_byte_content)) return false;

  conf_high_byte_content &= ~AS5600_CONF_HIGH_BYTE_REG_WD_bm;

  if(!writeSingleRegister(REG_CONF_HIGH_BYTE, conf_high_byte_content)) return false;

  return true;
}

bool AS5600::setAngularStartPosition(uint16_t const angle_start)
{
  uint8_t const angle_start_buf[2] =
  {
      (uint8_t)((angle_start & 0xFF00) >> 8),
      (uint8_t)((angle_start & 0x00FF) >> 0)
  };

  return _io.writeMultipleRegister(REG_ZPOS_HIGH_BYTE, angle_start_buf, 2);
}

bool AS5600::setAngularStopPosition(uint16_t const angle_stop)
{
  uint8_t const angle_stop_buf[2] =
  {
      (uint8_t)((angle_stop & 0xFF00) >> 8),
      (uint8_t)((angle_stop & 0x00FF) >> 0)
  };

  return _io.writeMultipleRegister(REG_MPOS_HIGH_BYTE, angle_stop_buf, 2);
}

bool AS5600::setMaximumAngle(uint16_t const angle_max)
{
  uint8_t const angle_max_buf[2] =
  {
      (uint8_t)((angle_max & 0xFF00) >> 8),
      (uint8_t)((angle_max & 0x00FF) >> 0)
  };

  return _io.writeMultipleRegister(REG_MANG_HIGH_BYTE, angle_max_buf, 2);
}

bool AS5600::readAngle(uint16_t * angle)
{
  uint8_t angle_buf[2] = {0};

  if(!_io.readMultipleRegister(REG_ANGLE_HIGH_BYTE, angle_buf, 2)) return false;

  *angle  = (static_cast<uint16_t>(angle_buf[0]) << 8);
  *angle += (static_cast<uint16_t>(angle_buf[1]) << 0);

  return true;
}

bool AS5600::readAngleRaw(uint16_t * angle_raw)
{
  uint8_t angle_raw_buf[2] = {0};

  if(!_io.readMultipleRegister(REG_RAW_ANGLE_HIGH_BYTE, angle_raw_buf, 2)) return false;

  *angle_raw  = (static_cast<uint16_t>(angle_raw_buf[0]) << 8);
  *angle_raw += (static_cast<uint16_t>(angle_raw_buf[1]) << 0);

  return true;
}

bool AS5600::readStatus(uint8_t * status)
{
  return readSingleRegister(REG_STATUS, status);
}

bool AS5600::readAGC(uint8_t * agc)
{
  return readSingleRegister(REG_AGC, agc);
}

bool AS5600::readMagnitude(uint16_t * mag)
{
  uint8_t mag_buf[2] = {0};

  if(!_io.readMultipleRegister(REG_MAGNITUDE_HIGH_BYTE, mag_buf, 2)) return false;

  *mag  = (static_cast<uint16_t>(mag_buf[0]) << 8);
  *mag += (static_cast<uint16_t>(mag_buf[1]) << 0);

  return true;
}

bool AS5600::isMagnetTooStrong(uint8_t const status)
{
  return (status & AS5600_STATUS_REG_MH_bm) != 0;
}

bool AS5600::isMagnetTooWeak(uint8_t const status)
{
  return (status & AS5600_STATUS_REG_ML_bm) != 0;
}

bool AS5600::isMagnetDetected(uint8_t const status)
{
  return (status & AS5600_STATUS_REG_MD_bm) != 0;
}

void AS5600::debug_dumpAllRegs(driver::interface::Debug & debug_interface)
{
  debug_dumpSingleReg(debug_interface, "REG_ZMCO                = ", REG_ZMCO               );
  debug_dumpSingleReg(debug_interface, "REG_ZPOS_HIGH_BYTE      = ", REG_ZPOS_HIGH_BYTE     );
  debug_dumpSingleReg(debug_interface, "REG_ZPOS_LOW_BYTE       = ", REG_ZPOS_LOW_BYTE      );
  debug_dumpSingleReg(debug_interface, "REG_MPOS_HIGH_BYTE      = ", REG_MPOS_HIGH_BYTE     );
  debug_dumpSingleReg(debug_interface, "REG_MPOS_LOW_BYTE       = ", REG_MPOS_LOW_BYTE      );
  debug_dumpSingleReg(debug_interface, "REG_MANG_HIGH_BYTE      = ", REG_MANG_HIGH_BYTE     );
  debug_dumpSingleReg(debug_interface, "REG_MANG_LOW_BYTE       = ", REG_MANG_LOW_BYTE      );
  debug_dumpSingleReg(debug_interface, "REG_CONF_HIGH_BYTE      = ", REG_CONF_HIGH_BYTE     );
  debug_dumpSingleReg(debug_interface, "REG_CONF_LOW_BYTE       = ", REG_CONF_LOW_BYTE      );
  debug_dumpSingleReg(debug_interface, "REG_RAW_ANGLE_HIGH_BYTE = ", REG_RAW_ANGLE_HIGH_BYTE);
  debug_dumpSingleReg(debug_interface, "REG_RAW_ANGLE_LOW_BYTE  = ", REG_RAW_ANGLE_LOW_BYTE );
  debug_dumpSingleReg(debug_interface, "REG_ANGLE_HIGH_BYTE     = ", REG_ANGLE_HIGH_BYTE    );
  debug_dumpSingleReg(debug_interface, "REG_ANGLE_LOW_BYTE      = ", REG_ANGLE_LOW_BYTE     );
  debug_dumpSingleReg(debug_interface, "REG_AGC                 = ", REG_AGC                );
  debug_dumpSingleReg(debug_interface, "REG_MAGNITUDE_HIGH_BYTE = ", REG_MAGNITUDE_HIGH_BYTE);
  debug_dumpSingleReg(debug_interface, "REG_MAGNITUDE_LOW_BYTE  = ", REG_MAGNITUDE_LOW_BYTE );
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

bool AS5600::readSingleRegister(RegisterSelect const reg_sel, uint8_t * data)
{
  return _io.readMultipleRegister(reg_sel, data, 1);
}

bool AS5600::writeSingleRegister(RegisterSelect const reg_sel, uint8_t const data)
{
  return _io.writeMultipleRegister(reg_sel, &data, 1);
}

void AS5600::debug_dumpSingleReg(driver::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel)
{
  uint8_t reg_content = 0;

  readSingleRegister(reg_sel, &reg_content);

  debug_interface.print("%s%X\n", msg, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AS5600 */

} /* sensor */

} /* driver */

} /* spectre */
