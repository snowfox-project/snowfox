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

#include <spectre/mcu/avr/ATMEGA328P/I2CMaster.h>

#include <avr/io.h>
#include <util/twi.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace mcu
{

namespace ATMEGA328P
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* TWSR */
#define TWPS1_bm     (1<<TWPS1)
#define TWPS0_bm     (1<<TWPS0)

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

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

uint8_t I2CMaster::convertI2CAddress(uint8_t const address, bool is_read_access)
{
  if(is_read_access)  return (address | 0x01);
  else                return address;
}

bool I2CMaster::start(uint8_t const address)
{
  /* Transmit START condition */
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

  /* Wait for end of transmission */
  while( !(TWCR & (1<<TWINT)) );

  /* Check if the start condition was successfully transmitted */
  uint8_t twst = TW_STATUS & 0xF8;
  if((twst != TW_START) && (twst != TW_REP_START)) return false;

  /* Load slave address into data register */
  TWDR = address;

  /* Start transmission of address */
  TWCR = (1<<TWINT) | (1<<TWEN);

  /* Wait for end of transmission */
  while( !(TWCR & (1<<TWINT)) );

  /* Check if the device has acknowledged the READ / WRITE mode */
  twst = TW_STATUS & 0xF8;
  if  ((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return false;
  else                                                      return true;
}

bool I2CMaster::transmitByte(uint8_t const data)
{
  /* Load data into data register */
  TWDR = data;

  /* Start transmission of data */
  TWCR = (1<<TWINT) | (1<<TWEN);

  /* Wait for end of transmission */
  while( !(TWCR & (1<<TWINT)) );

  if  ((TWSR & 0xF8) != TW_MT_DATA_ACK ) return false;
  else                                   return true;
}

void I2CMaster::receiveByteAndSendACK(uint8_t * data)
{
  /* Start TWI module and acknowledge data after reception */
  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);

  /* Wait for end of transmission */
  while( !(TWCR & (1<<TWINT)) );

  /* Read received data from TWDR */
  *data = TWDR;
}

void I2CMaster::receiveByteAndSendNACK(uint8_t * data)
{
  /* Start receiving without acknowledging reception */
  TWCR = (1<<TWINT) | (1<<TWEN);

  /* Wait for end of transmission */
  while( !(TWCR & (1<<TWINT)) );

  /* Read received data from TWDR */
  *data = TWDR;
}

void I2CMaster::stop()
{
  /* Transmit STOP condition */
  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* mcu */

} /* spectre */
