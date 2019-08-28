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

#include <snowfox/driver/memory/N25Q256A/N25Q256A_Control.h>

#include <snowfox/driver/memory/N25Q256A/util/N25Q256A_Util.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace memory
{

namespace N25Q256A
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

N25Q256A_Control::N25Q256A_Control(interface::N25Q256A_Io & io)
: _io(io)
{

}

N25Q256A_Control::~N25Q256A_Control()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void N25Q256A_Control::read(uint32_t const read_addr, uint8_t * buffer, uint32_t const num_bytes)
{
  _io.transfer(interface::Command::READ_4_BYTE_ADDR,
               reinterpret_cast<uint8_t const *>(&read_addr), /* tx_buf       */
               4,                                             /* tx_num_bytes */
               0,                                             /* tx_fill_data */
               buffer,                                        /* rx_buf       */
               num_bytes,                                     /* rx_num_bytes */
               4);                                            /* rx_start_pos */
}

void N25Q256A_Control::write(uint32_t const write_addr, uint8_t const * buffer, uint32_t const num_bytes)
{
  _io.enableWrite();

  _io.transfer(interface::Command::PAGE_PROGRAM_4_BYTE_ADDR,
               reinterpret_cast<uint8_t const *>(&write_addr), /* tx_buf_1       */
               4,                                              /* tx_num_bytes_1 */
               buffer,                                         /* tx_buf_2       */
               num_bytes);                                     /* tx_num_bytes_2 */
}

void N25Q256A_Control::eraseSubsector(uint32_t const subsector_num)
{
  /* The subsector erase command byte is followed by a address within
   * subsector which the user intends to delete. Therefore we must
   * first calculate a valid address from the supplied subsector_num.
   */
  uint32_t const subsector_base_addr = util::toSubsectorBaseAddr(subsector_num);

  _io.enableWrite();

  _io.transfer(interface::Command::SUBSECTOR_ERASE_4_BYTE_ADDR,
               reinterpret_cast<uint8_t const *>(&subsector_base_addr), /* tx_buf       */
               4);                                                      /* tx_num_bytes */
}

bool N25Q256A_Control::isEraseComplete()
{
  return !_io.isBusy();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* N25Q256A */

} /* memory */

} /* driver */

} /* snowfox */
