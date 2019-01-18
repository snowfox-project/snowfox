/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2019 Alexander Entinger / LXRobotics GmbH
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

#include <snowfox/driver/sensor/INA220/INA220_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
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

INA220_Control::INA220_Control(interface::INA220_Io & io)
: _io(io)
{

}

INA220_Control::~INA220_Control()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool INA220_Control::setBusVoltageRange(interface::BusVoltageRange const bus_voltage_range)
{
  uint16_t config_reg_content = 0;

  if(!_io.readRegister(interface::Register::CONFIG, &config_reg_content)) return false;

  config_reg_content &= ~INA220_CONFIG_REG_BRNG_bm;
  config_reg_content |= static_cast<uint16_t>(bus_voltage_range);

  if(!_io.writeRegister(interface::Register::CONFIG, config_reg_content)) return false;

  return true;
}

bool INA220_Control::setShuntPgaGain(interface::ShuntPgaGain const shunt_pga_gain)
{
  uint16_t config_reg_content = 0;

  if(!_io.readRegister(interface::Register::CONFIG, &config_reg_content)) return false;

  config_reg_content &= ~(INA220_CONFIG_REG_PG1_bm | INA220_CONFIG_REG_PG0_bm);
  config_reg_content |= static_cast<uint16_t>(shunt_pga_gain);

  if(!_io.writeRegister(interface::Register::CONFIG, config_reg_content)) return false;

  return true;
}

bool INA220_Control::setBusAdcResolution(interface::BusAdcResolution const bus_adc_resolution)
{
  uint16_t config_reg_content = 0;

  if(!_io.readRegister(interface::Register::CONFIG, &config_reg_content)) return false;

  config_reg_content &= ~(INA220_CONFIG_REG_BADC4_bm | INA220_CONFIG_REG_BADC3_bm | INA220_CONFIG_REG_BADC2_bm | INA220_CONFIG_REG_BADC1_bm);
  config_reg_content |= static_cast<uint16_t>(bus_adc_resolution);

  if(!_io.writeRegister(interface::Register::CONFIG, config_reg_content)) return false;

  return true;
}

bool INA220_Control::setShuntAdcResolution(interface::ShuntAdcResolution const shunt_adc_resolution)
{
  uint16_t config_reg_content = 0;

  if(!_io.readRegister(interface::Register::CONFIG, &config_reg_content)) return false;

  config_reg_content &= ~(INA220_CONFIG_REG_SADC4_bm | INA220_CONFIG_REG_SADC3_bm | INA220_CONFIG_REG_SADC2_bm | INA220_CONFIG_REG_SADC1_bm);
  config_reg_content |= static_cast<uint16_t>(shunt_adc_resolution);

  if(!_io.writeRegister(interface::Register::CONFIG, config_reg_content)) return false;

  return true;

}

bool INA220_Control::setOperatingMode(interface::OperatingMode const operating_mode)
{
  uint16_t config_reg_content = 0;

  if(!_io.readRegister(interface::Register::CONFIG, &config_reg_content)) return false;

  config_reg_content &= ~(INA220_CONFIG_REG_MODE3_bm | INA220_CONFIG_REG_MODE2_bm | INA220_CONFIG_REG_MODE1_bm);
  config_reg_content |= static_cast<uint16_t>(operating_mode);

  if(!_io.writeRegister(interface::Register::CONFIG, config_reg_content)) return false;

  return true;
}

bool INA220_Control::readShuntVoltage(int16_t * shunt_voltage)
{
  uint16_t v_shunt_reg_content = 0;

  if(!_io.readRegister(interface::Register::V_SHUNT, &v_shunt_reg_content)) return false;

  *shunt_voltage = static_cast<int16_t>(v_shunt_reg_content);

  return true;

}

bool INA220_Control::readBusVoltage(int16_t * bus_voltage)
{
  uint16_t v_bus_reg_content = 0;

  if(!_io.readRegister(interface::Register::V_BUS, &v_bus_reg_content)) return false;

  *bus_voltage = static_cast<int16_t>(v_bus_reg_content) >> 3;

  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* INA220 */

} /* sensor */

} /* driver */

} /* snowfox */
