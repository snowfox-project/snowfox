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

#include <spectre/mcu/avr/ATxxxx/I2CMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace mcu
{

namespace ATxxxx
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* TWSR */
#define TWPS1_bm (1<<TWPS1)
#define TWPS0_bm (1<<TWPS0)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

I2CMaster::I2CMaster()
{

}

I2CMaster::~I2CMaster()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool I2CMaster::begin(uint8_t const address, bool const is_read_access)
{
  return this->start(convertI2CAddress(address, is_read_access));
}

bool I2CMaster::write(uint8_t const data)
{
  return this->transmitByte(data);
}

void I2CMaster::end()
{
  this->stop();
}

bool I2CMaster::requestFrom(uint8_t const address, uint8_t * data, uint16_t const num_bytes)
{
  if(num_bytes == 0        ) return false;

  if(!begin(address, true )) return false;

  for(uint16_t i = 0; i < (num_bytes - 1); i++)
  {
    this->receiveByteAndSendACK(data+i);
  }

  this->receiveByteAndSendNACK(data + num_bytes - 1);

  this->end();

  return true;
}

void I2CMaster::setI2CClock(eI2CClock const i2c_clock)
{
  setTWIPrescaler(Prescaler_1);

  switch(i2c_clock)
  {
  case F_100_kHz  : setTWBR( 100000, static_cast<uint32_t>(Prescaler_1)); break;
  case F_400_kHz  : setTWBR( 400000, static_cast<uint32_t>(Prescaler_1)); break;
  case F_1000_kHz : setTWBR(1000000, static_cast<uint32_t>(Prescaler_1)); break;
  default: break;
  }
}

/**************************************************************************************
 * PROTECTED MEMBER FUNCTIONS
 **************************************************************************************/

uint8_t I2CMaster::convertI2CAddress(uint8_t const address, bool is_read_access)
{
  if(is_read_access)  return (address | 0x01);
  else                return address;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* mcu */

} /* spectre */
