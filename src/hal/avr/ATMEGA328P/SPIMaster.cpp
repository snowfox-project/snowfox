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

#include <spectre/hal/avr/ATMEGA328P/SPIMaster.h>

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

/* SPCR */
#define SPR0_bm   (1<<0)
#define SPR1_bm   (1<<1)
#define CPHA_bm   (1<<2)
#define CPOL_bm   (1<<3)
#define MSTR_bm   (1<<4)
#define DORD_bm   (1<<5)
#define SPE_bm    (1<<6)
#define SPIE_bm   (1<<7)

/* SPSR */
#define SPI2X_bm  (1<<0)
#define WCOL_bm   (1<<6)
#define SPIF_bm   (1<<7)

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  Prescaler_4   = 0,
  Prescaler_16  =           SPR0_bm,
  Prescaler_64  = SPR1_bm,
  Prescaler_128 = SPR1_bm | SPR0_bm
} SPIPrescalerSelect;

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

SPIMaster::SPIMaster(volatile uint8_t * spcr,
                     volatile uint8_t * spsr,
                     volatile uint8_t * spdr)
: _SPCR(spcr),
  _SPSR(spsr),
  _SPDR(spdr)
{
  enableSpiMaster();
}

SPIMaster::~SPIMaster()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

uint8_t SPIMaster::exchange(uint8_t const data)
{
  *_SPDR = data;

  while (!(*_SPSR & SPIF_bm)) { }

  return *_SPDR;
}

void SPIMaster::setSpiMode(interface::SpiMode const spi_mode)
{
  *_SPCR &= ~(CPOL_bm | CPHA_bm);

  switch(spi_mode)
  {
  case interface::SpiMode::MODE_0:                                break;
  case interface::SpiMode::MODE_1: *_SPCR |= CPHA_bm;             break;
  case interface::SpiMode::MODE_2: *_SPCR |= CPOL_bm;             break;
  case interface::SpiMode::MODE_3: *_SPCR |= (CPOL_bm | CPHA_bm); break;
  }
}

void SPIMaster::setSpiBitOrder(interface::SpiBitOrder const spi_bit_order)
{
  switch(spi_bit_order)
  {
  case interface::SpiBitOrder::LSB_FIRST: *_SPCR |=  (DORD_bm); break;
  case interface::SpiBitOrder::MSB_FIRST: *_SPCR &= ~(DORD_bm); break;
  }
}

void SPIMaster::setSpiPrescaler(uint32_t const spi_prescaler)
{
  *_SPCR &= ~(SPR1_bm | SPR0_bm);

  switch(spi_prescaler)
  {
  case 2  : { *_SPCR |= static_cast<uint8_t>(Prescaler_4  ); *_SPSR |=  SPI2X_bm; } break;
  case 4  : { *_SPCR |= static_cast<uint8_t>(Prescaler_4  ); *_SPSR &= ~SPI2X_bm; } break;
  case 8  : { *_SPCR |= static_cast<uint8_t>(Prescaler_16 ); *_SPSR |=  SPI2X_bm; } break;
  case 16 : { *_SPCR |= static_cast<uint8_t>(Prescaler_16 ); *_SPSR &= ~SPI2X_bm; } break;
  case 32 : { *_SPCR |= static_cast<uint8_t>(Prescaler_64 ); *_SPSR |=  SPI2X_bm; } break;
  case 64 : { *_SPCR |= static_cast<uint8_t>(Prescaler_64 ); *_SPSR &= ~SPI2X_bm; } break;
  case 128: { *_SPCR |= static_cast<uint8_t>(Prescaler_128); *_SPSR &= ~SPI2X_bm; } break;
  default : {                                                *_SPSR &= ~SPI2X_bm; } break;
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void SPIMaster::enableSpiMaster()
{
  *_SPCR |= (SPE_bm | MSTR_bm);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* spectre */
