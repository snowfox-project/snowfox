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

#include <spectre/driver/memory/AT45DBx/AT45DBx_IoSpi.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace memory
{

namespace AT45DBx
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

AT45DBx_IoSpi::AT45DBx_IoSpi(hal::interface::SpiMasterControl & spi_master, hal::interface::DigitalOutPin & cs)
: _spi_master(spi_master),
  _cs        (cs        )
{
  _cs.set();
}

AT45DBx_IoSpi::~AT45DBx_IoSpi()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void AT45DBx_IoSpi::exchange(uint8_t const * buf_in, uint16_t const buf_in_size)
{
  _cs.clr();

  for(uint16_t b = 0; b < buf_in_size; b++)
  {
    _spi_master.exchange(buf_in[b]);
  }

  _cs.set();
}

void AT45DBx_IoSpi::exchange(uint8_t const * buf_in, uint8_t * buf_out, uint16_t const buf_size)
{
  _cs.clr();

  for(uint16_t b = 0; b < buf_size; b++)
  {
    buf_out[b] = _spi_master.exchange(buf_in[b]);
  }

  _cs.set();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT45DBx */

} /* memory */

} /* driver */

} /* spectre */
