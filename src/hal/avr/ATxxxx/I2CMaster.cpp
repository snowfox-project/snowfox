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

#include <spectre/hal/avr/ATxxxx/I2CMaster.h>

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
 * DEFINES
 **************************************************************************************/

/* TWSR */
#define TWPS1_bm (1<<TWPS1)
#define TWPS0_bm (1<<TWPS0)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

I2CMaster::I2CMaster(interface::I2CMaster & i2c_master, interface::I2CMasterConfiguration & i2c_master_configuration)
: _i2c_master              (i2c_master              ),
  _i2c_master_configuration(i2c_master_configuration)
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
  return _i2c_master.start(convertI2CAddress(address, is_read_access));
}

bool I2CMaster::write(uint8_t const data)
{
  return _i2c_master.transmitByte(data);
}

void I2CMaster::end()
{
  _i2c_master.stop();
}

bool I2CMaster::requestFrom(uint8_t const address, uint8_t * data, uint16_t const num_bytes)
{
  if(num_bytes == 0        ) return false;

  if(!begin(address, true )) return false;

  for(uint16_t i = 0; i < (num_bytes - 1); i++)
  {
    _i2c_master.receiveByteAndSendACK(data+i);
  }

  _i2c_master.receiveByteAndSendNACK(data + num_bytes - 1);

  end();

  return true;
}

void I2CMaster::setI2CClock(eI2CClock const i2c_clock)
{
  uint32_t const TWI_PRESCALER = 1;

  _i2c_master_configuration.setTWIPrescaler(TWI_PRESCALER);

  switch(i2c_clock)
  {
  case F_100_kHz  : _i2c_master_configuration.setTWBR( 100000, TWI_PRESCALER); break;
  case F_400_kHz  : _i2c_master_configuration.setTWBR( 400000, TWI_PRESCALER); break;
  case F_1000_kHz : _i2c_master_configuration.setTWBR(1000000, TWI_PRESCALER); break;
  default: break;
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
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

} /* hal */

} /* spectre */
