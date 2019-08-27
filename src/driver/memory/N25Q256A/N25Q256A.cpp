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

#include <snowfox/driver/memory/N25Q256A/N25Q256A.h>

#include <snowfox/driver/memory/N25Q256A/util/N25Q256A_Util.h>
#include <snowfox/driver/memory/N25Q256A/N25Q256A_Capabilities.h>

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

N25Q256A::N25Q256A(interface::N25Q256A_Io            & io,
                   interface::N25Q256A_Configuration & config,
                   interface::N25Q256A_Control       & control)
: _io     (io)
, _config (config)
, _control(control)
{

}

N25Q256A::~N25Q256A()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool N25Q256A::open()
{
  if(!_config.setAdressMode(interface::AddressMode::AM_4Byte)) return false;
  /* TODO */
  return true;
}

void N25Q256A::close()
{
  /* TODO */
}

/**************************************************************************************
 * PROTECTE MEMBER FUNCTIONS
 **************************************************************************************/

ssize_t N25Q256A::read(uint32_t const read_addr, uint8_t * buffer, ssize_t const num_bytes)
{
  if(!_io.readFromMemory(read_addr, buffer, num_bytes)) return -1;
  return num_bytes;
}

ssize_t N25Q256A::write(uint32_t const write_addr, uint8_t const * buffer, ssize_t const num_bytes)
{
  /* If the bits of the least significant address, which is the starting address,
   * are not all zero (= 256 byte page size), all data transmitted beyond the end
   * of the current page is programmed from the starting address of the same page.
   * If the number of bytes sent to the device exceed the maximum page size, prev-
   * iously latched data is discarded and only the last maximum page-size number
   * of data bytes are guaranteed to be programmed correctly within the same page.
   * If the number of bytes sent to the device is less than the maximum page size,
   * they are correctly programmed at the specified addresses without any effect on
   * the other bytes of the same page. (Source: N25Q256A datasheet, page 54).
   */
  if(num_bytes < 0)                                                                   return -1;
  if(static_cast<uint32_t>(num_bytes) > CAPABILITIES.write_block_size)                return -1;
  if(!_io.enableWrite())                                                              return -1;
  if(!_io.writeToProgramBuffer(write_addr, buffer, static_cast<uint32_t>(num_bytes))) return -1;
  return num_bytes;
}

bool N25Q256A::ioctl_get_capabilities(NorDriverCapabilities * capabilities)
{
  *capabilities = CAPABILITIES;
  return true;
}

bool N25Q256A::ioctl_erase(uint32_t const erase_block_num)
{
  /* The smallest erase block size on the N25Q256A is a subsector-level erase.
   * The erase operation is performed in 3 steps:
   *  - Verify if a valid erase block num has been supplied
   *  - Trigger a subsector erase
   *  - Wait for subsector erase to be completed
   */
  if(!util::isValidSubsector(erase_block_num)) return false;
  
  if(!_io.enableWrite())                          return false;
  if(!_io.triggerSubsectorErase(erase_block_num)) return false;

  bool is_erase_in_progress = true;
  do
  {
    if(!_control.isEraseInProgress(&is_erase_in_progress)) return false;
  } while(is_erase_in_progress);

  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* N25Q256A */

} /* memory */

} /* driver */

} /* snowfox */
