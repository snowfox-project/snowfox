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

#include <snowfox/hal/riscv64/FE310/SpiMasterBase.h>

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
#define SCKMODE_POL_bp    (1)
#define SCKMODE_PHA_bp    (0)

/* FMT */
#define FMT_ENDIAN_bp     (2)
#define FMT_PROTO_1_bp    (1)
#define FMT_PROTO_0_bp    (0)

/* CSMODE */
#define CSMODE_MODE_1_bp  (1)
#define CSMODE_MODE_0_bp  (0)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

SpiMasterBase::SpiMasterBase(volatile uint32_t * spix_sckmode,
                             volatile uint32_t * spix_fmt,
                             volatile uint32_t * spix_csmode)
: _spix_sckmode(spix_sckmode),
  _spix_fmt    (spix_fmt    ),
  _spix_csmode (spix_csmode )
{
  setSpiProtocol   (SpiProtocol::Single);
  setChipSelectMode(ChipSelectMode::Off); /* Manual control of chip select line */
}

SpiMasterBase::~SpiMasterBase()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

uint8_t SpiMasterBase::exchange(uint8_t const /* data */)
{
  /* TODO */ return 0;
}

bool SpiMasterBase::setSpiMode(interface::SpiMode const spi_mode)
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

bool SpiMasterBase::setSpiBitOrder(interface::SpiBitOrder const spi_bit_order)
{ 
  switch(spi_bit_order)
  {
  case interface::SpiBitOrder::LSB_FIRST: util::setBit(_spix_fmt, FMT_ENDIAN_bp); break;
  case interface::SpiBitOrder::MSB_FIRST: util::clrBit(_spix_fmt, FMT_ENDIAN_bp); break;
  }

  return true;
}

bool SpiMasterBase::setSpiPrescaler(uint32_t const /* spi_prescaler */)
{
  /* TODO */ return false;
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void SpiMasterBase::setSpiProtocol(SpiProtocol const spi_protocol)
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

void SpiMasterBase::setChipSelectMode(ChipSelectMode const cs_mode)
{
  util::clrBit(_spix_csmode, CSMODE_MODE_1_bp);
  util::clrBit(_spix_csmode, CSMODE_MODE_0_bp);

  switch(cs_mode)
  {
    case ChipSelectMode::Auto: break;
    case ChipSelectMode::Hold: util::setBit(_spix_csmode, CSMODE_MODE_1_bp); break;
    case ChipSelectMode::Off : util::setBit(_spix_csmode, CSMODE_MODE_1_bp); util::setBit(_spix_csmode, CSMODE_MODE_0_bp); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* FE310 */

} /* hal */

} /* snowfox */
