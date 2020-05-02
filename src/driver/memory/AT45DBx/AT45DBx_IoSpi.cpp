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

#include <snowfox/driver/memory/AT45DBx/AT45DBx_IoSpi.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::memory::AT45DBx
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

void AT45DBx_IoSpi::exchange(uint8_t const * buf_cmd_in)
{
  _cs.clr();

  for(uint16_t b = 0; b < interface::AT45DBx_Io::COMMAND_BUFFER_SIZE; b++)
  {
    _spi_master.exchange(buf_cmd_in[b]);
  }

  _cs.set();
}

void AT45DBx_IoSpi::exchange(uint8_t const * buf_cmd_in, uint8_t * buf_cmd_out)
{
  _cs.clr();

  for(uint16_t b = 0; b < interface::AT45DBx_Io::COMMAND_BUFFER_SIZE; b++)
  {
    buf_cmd_out[b] = _spi_master.exchange(buf_cmd_in[b]);
  }

  _cs.set();
}

void AT45DBx_IoSpi::exchange(uint8_t const * buf_cmd_in, uint8_t const * buf_data_in, uint16_t const buf_data_in_size)
{
  _cs.clr();

  for(uint16_t b = 0; b < interface::AT45DBx_Io::COMMAND_BUFFER_SIZE; b++)
  {
    _spi_master.exchange(buf_cmd_in[b]);
  }

  for(uint16_t b = 0; b < buf_data_in_size; b++)
  {
    _spi_master.exchange(buf_data_in[b]);
  }

  _cs.set();
}

void AT45DBx_IoSpi::exchange(uint8_t const * buf_cmd_in, uint8_t * buf_data_out, uint16_t const buf_data_out_size)
{
  _cs.clr();

  for(uint16_t b = 0; b < interface::AT45DBx_Io::COMMAND_BUFFER_SIZE; b++)
  {
    _spi_master.exchange(buf_cmd_in[b]);
  }

  for(uint16_t b = 0; b < buf_data_out_size; b++)
  {
    buf_data_out[b] = _spi_master.exchange(0);
  }

  _cs.set();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::memory::AT45DBx */
