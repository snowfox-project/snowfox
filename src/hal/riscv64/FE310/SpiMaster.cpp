/**
 * Snowfox is a modular RTOS with extensive IO support.
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

#include <snowfox/hal/riscv64/FE310/SpiMaster.h>

#include <snowfox/util/BitUtil.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace FE310
{

/**************************************************************************************
 * DEFINE
 **************************************************************************************/

/* SCKMODE */
#define SCKMODE_PHA_bp  (0)
#define SCKMODE_PHA_bm  (1<<SCKMODE_PHA_bp)
#define SCKMODE_POL_bp  (1)
#define SCKMODE_POL_bm  (1<<SCKMODE_POL_bp)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

SpiMaster::SpiMaster(volatile uint32_t * spix_sckmode)
: _spix_sckmode(spix_sckmode)
{

}

SpiMaster::~SpiMaster()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

uint8_t SpiMaster::exchange(uint8_t const data)
{

}

void SpiMaster::setSpiMode(interface::SpiMode const spi_mode)
{
  *_spix_sckmode &= ~(SCKMODE_PHA_bm | SCKMODE_POL_bm);

  switch(spi_mode)
  {
  case interface::SpiMode::MODE_0:                                                                                           break;
  case interface::SpiMode::MODE_1:                                              util::setBit(_spix_sckmode, SCKMODE_PHA_bp); break;
  case interface::SpiMode::MODE_2: util::setBit(_spix_sckmode, SCKMODE_POL_bp);                                              break;
  case interface::SpiMode::MODE_3: util::setBit(_spix_sckmode, SCKMODE_POL_bp); util::setBit(_spix_sckmode, SCKMODE_PHA_bp); break;
  }
}

void SpiMaster::setSpiBitOrder(interface::SpiBitOrder const spi_bit_order)
{

}

void SpiMaster::setSpiPrescaler(uint32_t const spi_prescaler)
{

}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* FE310 */

} /* hal */

} /* snowfox */
