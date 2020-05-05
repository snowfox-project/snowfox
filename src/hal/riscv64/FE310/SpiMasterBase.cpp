/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#include <snowfox/hal/riscv64/FE310/RegisterBits.h>

#include <snowfox/util/BitUtil.h>
#include <snowfox/util/EnumClassConv.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::FE310
{

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
  
  setSpiBitsPerFrame(8);
  setSpiProtocol    (SpiProtocol::Single);
  setChipSelectMode (ChipSelectMode::Off); /* Manual control of chip select line */
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
  util::clrBit(_spix_sckmode, util::bp(SPIx_SCKMODE::PHA));
  util::clrBit(_spix_sckmode, util::bp(SPIx_SCKMODE::POL));

  switch(spi_mode)
  {
  case interface::SpiMode::MODE_0: {                                                                                                                     } break;
  case interface::SpiMode::MODE_1: {                                                           util::setBit(_spix_sckmode, util::bp(SPIx_SCKMODE::PHA)); } break;
  case interface::SpiMode::MODE_2: { util::setBit(_spix_sckmode, util::bp(SPIx_SCKMODE::POL));                                                           } break;
  case interface::SpiMode::MODE_3: { util::setBit(_spix_sckmode, util::bp(SPIx_SCKMODE::POL)); util::setBit(_spix_sckmode, util::bp(SPIx_SCKMODE::PHA)); } break;
  }

  return true;
}

bool SpiMasterBase::setSpiBitOrder(interface::SpiBitOrder const spi_bit_order)
{ 
  switch(spi_bit_order)
  {
  case interface::SpiBitOrder::LSB_FIRST: util::setBit(_spix_fmt, util::bp(SPIx_FMT::ENDIAN)); break;
  case interface::SpiBitOrder::MSB_FIRST: util::clrBit(_spix_fmt, util::bp(SPIx_FMT::ENDIAN)); break;
  }

  return true;
}

bool SpiMasterBase::setSpiBitsPerFrame(uint8_t const spi_bits_per_frame)
{
  static constexpr uint32_t SPIx_FMT_LEN_MASK = util::bm(SPIx_FMT::LEN_3) | 
                                                util::bm(SPIx_FMT::LEN_2) |
                                                util::bm(SPIx_FMT::LEN_1) |
                                                util::bm(SPIx_FMT::LEN_0);
  *_spix_fmt &= ~SPIx_FMT_LEN_MASK;
  
  switch(spi_bits_per_frame)
  {
    case 8 : *_spix_fmt |= (8 << util::bp(SPIx_FMT::LEN_0)); return true;  break;
    default:                                                 return false; break;
  }
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
  util::clrBit(_spix_sckmode, util::bp(SPIx_FMT::PROTO_0));
  util::clrBit(_spix_sckmode, util::bp(SPIx_FMT::PROTO_1));

  switch(spi_protocol)
  {
  case SpiProtocol::Single:                                                           break;
  case SpiProtocol::Dual  : util::setBit(_spix_sckmode, util::bp(SPIx_FMT::PROTO_0)); break;
  case SpiProtocol::Quad  : util::setBit(_spix_sckmode, util::bp(SPIx_FMT::PROTO_1)); break;
  }
}

void SpiMasterBase::setChipSelectMode(ChipSelectMode const cs_mode)
{
  util::clrBit(_spix_csmode, util::bp(SPIx_CSMODE::MODE_1));
  util::clrBit(_spix_csmode, util::bp(SPIx_CSMODE::MODE_0));

  switch(cs_mode)
  {
    case ChipSelectMode::Auto: break;
    case ChipSelectMode::Hold: { util::setBit(_spix_csmode, util::bp(SPIx_CSMODE::MODE_1)); } break;
    case ChipSelectMode::Off : { util::setBit(_spix_csmode, util::bp(SPIx_CSMODE::MODE_1)); util::setBit(_spix_csmode, util::bp(SPIx_CSMODE::MODE_0)); } break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::FE310 */
