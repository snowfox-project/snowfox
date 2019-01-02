/**
 * Spectre is a modular RTOS with extensive IO support.
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

#include <spectre/driver/memory/PCF8570/PCF8570_IoI2c.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace memory
{

namespace PCF8570
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

PCF8570_IoI2c::PCF8570_IoI2c(uint8_t const i2c_address, hal::interface::I2cMaster & i2c_master)
: _i2c_address(i2c_address),
  _i2c_master (i2c_master )
{

}

PCF8570_IoI2c::~PCF8570_IoI2c()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool PCF8570_IoI2c::writeByte(uint8_t const address, uint8_t const data)
{
  if(!_i2c_master.begin(_i2c_address, false)) return false;
  if(!_i2c_master.write(address            )) return false;
  if(!_i2c_master.write(data               )) return false;
      _i2c_master.end  (                   );

  return true;
}

bool PCF8570_IoI2c::readByte(uint8_t const address, uint8_t * data)
{
  if(!_i2c_master.begin      (_i2c_address, false  )) return false;
  if(!_i2c_master.write      (address              )) return false;
  if(!_i2c_master.requestFrom(_i2c_address, data, 1)) return false;

  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* PCF8570 */

} /* memory */

} /* driver */

} /* spectre */
