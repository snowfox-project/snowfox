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
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/ATxxxx/i2c/I2CMasterBase.h>

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

I2CMasterBase::I2CMasterBase(interface::I2CMasterMCU & i2c_master_mcu)
: _i2c_master_mcu(i2c_master_mcu)
{

}

I2CMasterBase::~I2CMasterBase()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool I2CMasterBase::begin(uint8_t const address, bool const is_read_access)
{
  return _i2c_master_mcu.start(convertI2CAddress(address, is_read_access));
}

bool I2CMasterBase::write(uint8_t const data)
{
  return _i2c_master_mcu.transmitByte(data);
}

void I2CMasterBase::end()
{
  _i2c_master_mcu.stop();
}

bool I2CMasterBase::requestFrom(uint8_t const address, uint8_t * data, uint16_t const num_bytes)
{
  if(num_bytes == 0        ) return false;

  if(!begin(address, true )) return false;

  for(uint16_t i = 0; i < (num_bytes - 1); i++)
  {
    _i2c_master_mcu.receiveByteAndSendACK(data+i);
  }

  _i2c_master_mcu.receiveByteAndSendNACK(data + num_bytes - 1);

  end();

  return true;
}

void I2CMasterBase::setI2CClock(eI2CClock const i2c_clock)
{
  uint32_t const TWI_PRESCALER = 1;

  _i2c_master_mcu.setTWIPrescaler(TWI_PRESCALER);

  switch(i2c_clock)
  {
  case F_100_kHz  : _i2c_master_mcu.setTWBR( 100000, TWI_PRESCALER); break;
  case F_400_kHz  : _i2c_master_mcu.setTWBR( 400000, TWI_PRESCALER); break;
  case F_1000_kHz : _i2c_master_mcu.setTWBR(1000000, TWI_PRESCALER); break;
  default: break;
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

uint8_t I2CMasterBase::convertI2CAddress(uint8_t const address, bool is_read_access)
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
