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

#include <spectre/driver/sensor/INA220/INA220_IoI2c.h>

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

INA220_IoI2c::INA220_IoI2c(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master)
: _i2c_address(i2c_address),
  _i2c_master (i2c_master )
{

}

INA220_IoI2c::~INA220_IoI2c()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool INA220_IoI2c::readRegister(interface::RegisterSelect const reg_sel, uint16_t * data)
{
  uint8_t data_buf[2] = {0};

  if(!_i2c_master.begin      (_i2c_address, false      )) return false;
  if(!_i2c_master.write      (reg_sel                  )) return false;
  if(!_i2c_master.requestFrom(_i2c_address, data_buf, 2)) return false;

  *data  = (static_cast<uint16_t>(data[0]) << 8);
  *data += (static_cast<uint16_t>(data[1]) << 0);

  return true;
}

bool INA220_IoI2c::writeRegister(interface::RegisterSelect const reg_sel, uint16_t const data)
{
  uint8_t const data_msb = static_cast<uint8_t>((data & 0xFF00) >> 8);
  uint8_t const data_lsb = static_cast<uint8_t>((data & 0x00FF) >> 0);

  if(!_i2c_master.begin(_i2c_address, false)) return false;
  if(!_i2c_master.write(reg_sel            )) return false;
  if(!_i2c_master.write(data_msb           )) return false;
  if(!_i2c_master.write(data_lsb           )) return false;
      _i2c_master.end  (                   );

  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* INA220 */

} /* sensor */

} /* driver */

} /* spectre */
