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

#include <snowfox/driver/sensor/BMP388/BMP388_IoSpi.h>

#include <snowfox/util/EnumClassConv.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace BMP388
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

BMP388_IoSpi::BMP388_IoSpi(hal::interface::SpiMasterControl & spi_master, hal::interface::DigitalOutPin & cs)
: _spi_master{spi_master}
, _cs{cs}
{
  _cs.set();
}

BMP388_IoSpi::~BMP388_IoSpi()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void BMP388_IoSpi::readRegister(interface::Register const reg, uint8_t * data, uint16_t const num_bytes)
{
  uint8_t const reg_addr = 0x80 | util::to_integer(reg);

  _cs.clr();
  _spi_master.exchange(reg_addr);
  for(uint8_t b = 0; b < num_bytes; b++) {
    data[b] = _spi_master.exchange(0);
  }
  _cs.set();
}

void BMP388_IoSpi::writeRegister(interface::Register const reg, uint8_t const * data, uint16_t const num_bytes)
{
  uint8_t const reg_addr = util::to_integer(reg);

  _cs.clr();
  _spi_master.exchange(reg_addr);
  for(uint8_t b = 0; b < num_bytes; b++) {
    _spi_master.exchange(data[b]);
  }
  _cs.set();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* BMP388 */

} /* sensor */

} /* driver */

} /* snowfox */
