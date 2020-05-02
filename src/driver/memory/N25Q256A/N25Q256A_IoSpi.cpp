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

#include <snowfox/driver/memory/N25Q256A/N25Q256A_IoSpi.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::memory::N25Q256A
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

N25Q256A_IoSpi::N25Q256A_IoSpi(hal::interface::SpiMasterControl & spi_master, hal::interface::DigitalOutPin & cs)
: _spi_master(spi_master)
, _cs(cs)
{
  _cs.set();
}

N25Q256A_IoSpi::~N25Q256A_IoSpi()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void N25Q256A_IoSpi::transfer(interface::Command  const   cmd,
                              uint8_t             const * tx_buf,
                              uint32_t            const   tx_num_bytes,
                              uint8_t             const   tx_fill_data,
                              uint8_t                   * rx_buf,
                              uint32_t            const   rx_num_bytes,
                              uint32_t            const   rx_start_pos)
{
  _cs.clr();

  _spi_master.exchange(static_cast<uint8_t>(cmd));

  uint32_t const complete_transfer_num_bytes = (tx_num_bytes > (rx_num_bytes + rx_start_pos)) ? tx_num_bytes : (rx_num_bytes + rx_start_pos);

  for(uint32_t b = 0; b < complete_transfer_num_bytes; b++)
  {
    uint8_t rx_data = 0;

    if(b < tx_num_bytes) {
      rx_data = _spi_master.exchange(tx_buf[b]);
    } else {
      rx_data = _spi_master.exchange(tx_fill_data);
    }

    if(b >= rx_start_pos)
    {
      uint32_t const rx_buf_idx = b - rx_start_pos;
      if(rx_buf_idx < rx_num_bytes) {
        rx_buf[rx_buf_idx] = rx_data;
      }
    }
  }

  _cs.set();
}

void N25Q256A_IoSpi::transfer(interface::Command  const   cmd,
                              uint8_t             const * tx_buf_1,
                              uint32_t            const   tx_num_bytes_1,
                              uint8_t             const * tx_buf_2,
                              uint32_t            const   tx_num_bytes_2)
{
  _cs.clr();

  _spi_master.exchange(static_cast<uint8_t>(cmd));

  for(uint32_t b = 0; b < tx_num_bytes_1; b++) {
    _spi_master.exchange(tx_buf_1[b]);
  }

  for(uint32_t b = 0; b < tx_num_bytes_2; b++) {
    _spi_master.exchange(tx_buf_2[b]);
  }

  _cs.set();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::memory::N25Q256A */
