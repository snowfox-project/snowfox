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

#include <snowfox/driver/sensor/BMG160/BMG160_IoI2c.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensor::BMG160
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

BMG160_IoI2c::BMG160_IoI2c(uint8_t const i2c_address, hal::interface::I2cMaster & i2c_master)
: _i2c_address(i2c_address),
  _i2c_master (i2c_master )
{

}

BMG160_IoI2c::~BMG160_IoI2c()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool BMG160_IoI2c::readRegister(interface::Register const reg, uint8_t * data, uint16_t const num_bytes)
{
  uint8_t const reg_addr = (0x80 | static_cast<uint8_t>(reg));

  if(!_i2c_master.begin      (_i2c_address, false          )) return false;
  if(!_i2c_master.write      (reg_addr                     )) return false;
  if(!_i2c_master.requestFrom(_i2c_address, data, num_bytes)) return false;

  return true;
}

bool BMG160_IoI2c::readRegister(interface::Register const reg, uint8_t * data)
{
  uint8_t const reg_addr = static_cast<uint8_t>(reg);

  if(!_i2c_master.begin      (_i2c_address, false  )) return false;
  if(!_i2c_master.write      (reg_addr             )) return false;
  if(!_i2c_master.requestFrom(_i2c_address, data, 1)) return false;

  return true;
}

bool BMG160_IoI2c::writeRegister(interface::Register const reg, uint8_t const  * data, uint16_t const num_bytes)
{
  uint8_t const reg_addr = (0x80 | static_cast<uint8_t>(reg));

  if(!_i2c_master.begin(_i2c_address, false)) return false;
  if(!_i2c_master.write(reg_addr           )) return false;

  for(uint16_t i = 0; i < num_bytes; i++)
  {
    if(!_i2c_master.write(data[i]          )) return false;
  }
      _i2c_master.end  (                   );

  return true;
}

bool BMG160_IoI2c::writeRegister(interface::Register const reg, uint8_t const data)
{
  uint8_t const reg_addr = static_cast<uint8_t>(reg);

  if(!_i2c_master.begin(_i2c_address, false)) return false;
  if(!_i2c_master.write(reg_addr           )) return false;
  if(!_i2c_master.write(data               )) return false;
      _i2c_master.end  (                   );

  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensor::BMG160 */
