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

#include <spectre/hal/avr/common/ATxxxx/I2cMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATxxxx
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

I2cMaster::I2cMaster(interface::I2cMasterLowLevel & i2c_master_low_level)
: _i2c_master_low_level(i2c_master_low_level)
{

}

I2cMaster::~I2cMaster()
{

}


/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool I2cMaster::begin(uint8_t const address, bool const is_read_access)
{
  return _i2c_master_low_level.start(convertI2cAddress(address, is_read_access));
}

bool I2cMaster::write(uint8_t const data)
{
  return _i2c_master_low_level.transmitByte(data);
}

void I2cMaster::end()
{
  _i2c_master_low_level.stop();
}

bool I2cMaster::requestFrom(uint8_t const address, uint8_t * data, uint16_t const num_bytes)
{
  if(num_bytes == 0) return false;

  if(!this->begin(address, true)) return false;

  for(uint16_t i = 0; i < (num_bytes - 1); i++)
  {
    _i2c_master_low_level.receiveByteAndSendACK(data+i);
  }

  _i2c_master_low_level.receiveByteAndSendNACK(data + num_bytes - 1);

  this->end();

  return true;
}

void I2cMaster::setI2cClock(hal::interface::I2cClock const i2c_clock)
{
  uint32_t const TWI_PRESCALER = 1;

  _i2c_master_low_level.setTwiPrescaler(TWI_PRESCALER);

  switch(i2c_clock)
  {
  case hal::interface::I2cClock::F_100_kHz : _i2c_master_low_level.setTwiBitRateRegister( 100000, TWI_PRESCALER); break;
  case hal::interface::I2cClock::F_400_kHz : _i2c_master_low_level.setTwiBitRateRegister( 400000, TWI_PRESCALER); break;
  case hal::interface::I2cClock::F_1000_kHz: _i2c_master_low_level.setTwiBitRateRegister(1000000, TWI_PRESCALER); break;
  default                                  :                                                                      break;
  }
}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

uint8_t convertI2cAddress(uint8_t const address, bool is_read_access)
{
  if(is_read_access)  return (address | 0x01);
  else                return address;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */
