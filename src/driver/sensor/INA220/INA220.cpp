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

#include <spectre/driver/sensor/INA220/INA220.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace INA220
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

INA220::INA220(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master)
: _i2c_address(i2c_address),
  _i2c_master (i2c_master )
{

}

INA220::~INA220()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool INA220::setBusVoltageRange(BusVoltageRangeSelect const sel)
{
  uint16_t config_reg_content = 0;

  if(!readRegister(REG_CONFIG, &config_reg_content)) return false;

  config_reg_content &= ~INA220_CONFIG_REG_BRNG_bm;
  config_reg_content |= static_cast<uint16_t>(sel);

  if(!writeRegister(REG_CONFIG, config_reg_content)) return false;

  return true;
}

bool INA220::setShuntPGAGain(ShuntPGAGainSelect const sel)
{
  uint16_t config_reg_content = 0;

  if(!readRegister(REG_CONFIG, &config_reg_content)) return false;

  config_reg_content &= ~(INA220_CONFIG_REG_PG1_bm | INA220_CONFIG_REG_PG0_bm);
  config_reg_content |= static_cast<uint16_t>(sel);

  if(!writeRegister(REG_CONFIG, config_reg_content)) return false;

  return true;
}

bool INA220::setBusADCResolution(BusADCResolutionSelect const sel)
{
  uint16_t config_reg_content = 0;

  if(!readRegister(REG_CONFIG, &config_reg_content)) return false;

  config_reg_content &= ~(INA220_CONFIG_REG_BADC4_bm | INA220_CONFIG_REG_BADC3_bm | INA220_CONFIG_REG_BADC2_bm | INA220_CONFIG_REG_BADC1_bm);
  config_reg_content |= static_cast<uint16_t>(sel);

  if(!writeRegister(REG_CONFIG, config_reg_content)) return false;

  return true;
}

bool INA220::setShuntADCResolution(ShuntADCResolutionSelect const sel)
{
  uint16_t config_reg_content = 0;

  if(!readRegister(REG_CONFIG, &config_reg_content)) return false;

  config_reg_content &= ~(INA220_CONFIG_REG_SADC4_bm | INA220_CONFIG_REG_SADC3_bm | INA220_CONFIG_REG_SADC2_bm | INA220_CONFIG_REG_SADC1_bm);
  config_reg_content |= static_cast<uint16_t>(sel);

  if(!writeRegister(REG_CONFIG, config_reg_content)) return false;

  return true;

}

bool INA220::setOperatingMode(OperatingModeSelect const sel)
{
  uint16_t config_reg_content = 0;

  if(!readRegister(REG_CONFIG, &config_reg_content)) return false;

  config_reg_content &= ~(INA220_CONFIG_REG_MODE3_bm | INA220_CONFIG_REG_MODE2_bm | INA220_CONFIG_REG_MODE1_bm);
  config_reg_content |= static_cast<uint16_t>(sel);

  if(!writeRegister(REG_CONFIG, config_reg_content)) return false;

  return true;
}

bool INA220::readShuntVoltage(int16_t * shunt_voltage)
{
  uint16_t v_shunt_reg_content = 0;

  if(!readRegister(REG_V_SHUNT, &v_shunt_reg_content)) return false;

  *shunt_voltage = static_cast<int16_t>(v_shunt_reg_content);

  return true;

}

bool INA220::readBusVoltage(int16_t * bus_voltage)
{
  uint16_t v_bus_reg_content = 0;

  if(!readRegister(REG_V_BUS, &v_bus_reg_content)) return false;

  *bus_voltage = static_cast<int16_t>(v_bus_reg_content) >> 3;

  return true;
}

void INA220::debug_dumpAllRegs(driver::interface::Debug & debug_interface)
{
  debug_dumpSingleReg(debug_interface, "REG_CONFIG      = ", REG_CONFIG     );
  debug_dumpSingleReg(debug_interface, "REG_V_SHUNT     = ", REG_V_SHUNT    );
  debug_dumpSingleReg(debug_interface, "REG_V_BUS       = ", REG_V_BUS      );
  debug_dumpSingleReg(debug_interface, "REG_POWER       = ", REG_POWER      );
  debug_dumpSingleReg(debug_interface, "REG_CURRENT     = ", REG_CURRENT    );
  debug_dumpSingleReg(debug_interface, "REG_CALIBRATION = ", REG_CALIBRATION);
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/


bool INA220::readRegister(uint8_t const reg_addr, uint16_t * data)
{
  uint8_t data_buf[2] = {0};

  if(!_i2c_master.begin      (_i2c_address, false      )) return false;
  if(!_i2c_master.write      (reg_addr                 )) return false;
  if(!_i2c_master.requestFrom(_i2c_address, data_buf, 2)) return false;

  *data  = (static_cast<uint16_t>(data[0]) << 8);
  *data += (static_cast<uint16_t>(data[1]) << 0);

  return true;
}

bool INA220::writeRegister(uint8_t const reg_addr, uint16_t const data)
{
  uint8_t const data_msb = static_cast<uint8_t>((data & 0xFF00) >> 8);
  uint8_t const data_lsb = static_cast<uint8_t>((data & 0x00FF) >> 0);

  if(!_i2c_master.begin(_i2c_address, false)) return false;
  if(!_i2c_master.write(reg_addr           )) return false;
  if(!_i2c_master.write(data_msb           )) return false;
  if(!_i2c_master.write(data_lsb           )) return false;
      _i2c_master.end  (                   );

  return true;
}

void INA220::debug_dumpSingleReg(driver::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel)
{
  uint16_t reg_content = 0;

  readRegister(reg_sel, &reg_content);

  debug_interface.print("%s%X\n", msg, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* INA220 */

} /* sensor */

} /* driver */

} /* spectre */
