/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#include <snowfox/driver/sensor/LSM6DSM/LSM6DSM_Configuration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensor::LSM6DSM
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

LSM6DSM_Configuration::LSM6DSM_Configuration(interface::LSM6DSM_Io & io)
: _io(io)
{

}

LSM6DSM_Configuration::~LSM6DSM_Configuration()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool LSM6DSM_Configuration::enableRegAddrAutoIncrement()
{
  uint8_t ctrl3_c_reg_content = 0;

  if(!_io.readRegister(interface::Register::CTRL3_C, &ctrl3_c_reg_content)) return false;

  ctrl3_c_reg_content |= LSM6DSM_CTRL3_C_REG_IF_INC_bm;

  return _io.writeRegister(interface::Register::CTRL3_C, ctrl3_c_reg_content);
}

bool LSM6DSM_Configuration::enableBlockDataUpdate()
{
  uint8_t ctrl3_c_reg_content = 0;

  if(!_io.readRegister(interface::Register::CTRL3_C, &ctrl3_c_reg_content)) return false;

  ctrl3_c_reg_content |= LSM6DSM_CTRL3_C_REG_BDU_bm;

  return _io.writeRegister(interface::Register::CTRL3_C, ctrl3_c_reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensor::LSM6DSM */
