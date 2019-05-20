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
#define SCKMODE_POL_bp  (1)
#define SCKMODE_PHA_bp  (0)

/* FMT */
#define FMT_ENDIAN_bp   (2)
#define FMT_PROTO_1_bp  (1)
#define FMT_PROTO_0_bp  (0)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

SpiMaster::SpiMaster(volatile uint32_t * spix_sckmode,
                     volatile uint32_t * spix_fmt)
: _spix_sckmode(spix_sckmode),
  _spix_fmt    (spix_fmt    )
{
  setSpiProtocol(SpiProtocol::Single);
}

SpiMaster::~SpiMaster()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

uint8_t SpiMaster::exchange(uint8_t const /* data */)
{
  /* TODO */ return 0;
}

bool SpiMaster::setSpiMode(interface::SpiMode const spi_mode)
{
  util::clrBit(_spix_sckmode, SCKMODE_PHA_bp);
  util::clrBit(_spix_sckmode, SCKMODE_POL_bp);

  switch(spi_mode)
  {
  case interface::SpiMode::MODE_0:                                                                                           break;
  case interface::SpiMode::MODE_1:                                              util::setBit(_spix_sckmode, SCKMODE_PHA_bp); break;
  case interface::SpiMode::MODE_2: util::setBit(_spix_sckmode, SCKMODE_POL_bp);                                              break;
  case interface::SpiMode::MODE_3: util::setBit(_spix_sckmode, SCKMODE_POL_bp); util::setBit(_spix_sckmode, SCKMODE_PHA_bp); break;
  }

  return true;
}

bool SpiMaster::setSpiBitOrder(interface::SpiBitOrder const spi_bit_order)
{ 
  switch(spi_bit_order)
  {
  case interface::SpiBitOrder::LSB_FIRST: util::setBit(_spix_fmt, FMT_ENDIAN_bp); break;
  case interface::SpiBitOrder::MSB_FIRST: util::clrBit(_spix_fmt, FMT_ENDIAN_bp); break;
  }

  return true;
}

bool SpiMaster::setSpiPrescaler(uint32_t const /* spi_prescaler */)
{
  /* TODO */ return false;
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void SpiMaster::setSpiProtocol(SpiProtocol const spi_protocol)
{
  util::clrBit(_spix_sckmode, FMT_PROTO_0_bp);
  util::clrBit(_spix_sckmode, FMT_PROTO_1_bp);

  switch(spi_protocol)
  {
  case SpiProtocol::Single:                                              break;
  case SpiProtocol::Dual  : util::setBit(_spix_sckmode, FMT_PROTO_0_bp); break;
  case SpiProtocol::Quad  : util::setBit(_spix_sckmode, FMT_PROTO_1_bp); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* FE310 */

} /* hal */

} /* snowfox */
