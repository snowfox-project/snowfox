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

#include <spectre/hal/avr/ATMEGA328P/I2CMaster.h>

#include <avr/io.h>
#include <util/twi.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
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
 * PROTECTED MEMBER FUNCTIONS
 **************************************************************************************/

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

void I2CMaster::setTWIPrescaler(eTWIPrescaler const prescaler)
{
  TWSR &= ~(TWPS1_bm | TWPS0_bm);

  switch(prescaler)
  {
  case Prescaler_1  : TWSR |= 0;                    break;
  case Prescaler_4  : TWSR |= TWPS0_bm;             break;
  case Prescaler_16 : TWSR |= TWPS1_bm;             break;
  case Prescaler_64 : TWSR |= TWPS1_bm | TWPS0_bm;  break;
  default: break;
  }
}

void I2CMaster::setTWBR(uint32_t const i2c_speed_Hz, uint32_t const i2c_prescaler)
{
  uint32_t const twbr_val = (((static_cast<uint32_t>(F_CPU) / i2c_speed_Hz) / i2c_prescaler) - 16) / 2;

  TWBR = static_cast<uint8_t>(twbr_val);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* spectre */
