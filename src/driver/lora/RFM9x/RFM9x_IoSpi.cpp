/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#include <spectre/driver/lora/RFM9x/RFM9x_IoSpi.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace lora
{

namespace RFM9x
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RFM9x_IoSpi::RFM9x_IoSpi(hal::interface::SpiMaster & spi_master, hal::interface::DigitalOutPin & cs)
: _spi_master(spi_master),
  _cs        (cs        )
{
  _cs.set();
}

RFM9x_IoSpi::~RFM9x_IoSpi()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_IoSpi::readRegister(interface::Register const reg, uint8_t * data)
{
  uint8_t const reg_addr = static_cast<uint8_t>(reg);

  _cs.clr();
          _spi_master.exchange(reg_addr);
  *data = _spi_master.exchange(0       );
  _cs.set();
}

void RFM9x_IoSpi::readRegister(interface::Register const reg, uint8_t * data, uint16_t const bytes)
{
  uint8_t const reg_addr = static_cast<uint8_t>(reg);

  _cs.clr();
  _spi_master.exchange(reg_addr);
  for(uint16_t b = 0; b < bytes; b++) data[b] = _spi_master.exchange(0);
  _cs.set();
}

void RFM9x_IoSpi::writeRegister(interface::Register const reg, uint8_t const data)
{
  uint8_t const reg_addr = static_cast<uint8_t>(reg);

  _cs.clr();
  _spi_master.exchange(0x80 | reg_addr);
  _spi_master.exchange(data           );
  _cs.set();
}

void RFM9x_IoSpi::writeRegister(interface::Register const reg, uint8_t const * data, uint16_t const bytes)
{
  uint8_t const reg_addr = static_cast<uint8_t>(reg);

  _cs.clr();
  _spi_master.exchange(0x80 | reg_addr);
  for(uint16_t b = 0; b < bytes; b++) _spi_master.exchange(data[b]);
  _cs.set();
}


/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
