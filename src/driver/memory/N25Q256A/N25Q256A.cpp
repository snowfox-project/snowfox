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

#include <snowfox/driver/memory/N25Q256A/N25Q256A_FlashInfo.h>

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

N25Q256A::N25Q256A(interface::N25Q256A_Configuration & config,
                   interface::N25Q256A_Control       & control,
                   interface::N25Q256A_Status        & status)
: _config (config)
, _control(control)
, _status (status)
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
  _config.setAdressMode(ADDRESS_MODE);
  while(_status.isNVConfigRegWriteInProgress()) { /* TODO: yield() */ }
  if(_config.getAdressMode() != ADDRESS_MODE) return false;
  return true;
}

ssize_t N25Q256A::read(uint32_t const block, uint32_t const offset, uint8_t * buffer, uint32_t const num_bytes)
{
  if(block > FLASH_INFO.block_count) return -1;
  uint32_t const read_addr = (block * FLASH_INFO.erase_size) + offset;
  _control.read(read_addr, buffer, num_bytes);
  return num_bytes;
}

ssize_t N25Q256A::prog(uint32_t const block, uint32_t const offset, uint8_t const * buffer, uint32_t const num_bytes)
{
  if(block > FLASH_INFO.block_count) return -1;
  if(num_bytes > FLASH_INFO.prog_size) return -2;

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
  uint32_t const write_addr = (block * FLASH_INFO.erase_size) + offset;
  _control.write(write_addr, buffer, num_bytes);
  while(_status.isProgramInProgress()) { /* TODO: yield() */ }
  return num_bytes;
}

bool N25Q256A::erase(uint32_t const block)
{
  if(block > FLASH_INFO.block_count) return false;

  /* The smallest erase block size on the N25Q256A is a subsector-level erase.
   * The erase operation is performed in 3 steps:
   *  - Verify if a valid erase block num has been supplied
   *  - Trigger a subsector erase
   *  - Wait for subsector erase to be completed
   */
  _control.eraseSubsector(block);
  while(_status.isEraseInProgress()) { /* TODO: yield() */ }

  return true;
}

void N25Q256A::close()
{
  /* Do nothing. */
}

/**************************************************************************************
 * PROTECTED MEMBER FUNCTIONS
 **************************************************************************************/

bool N25Q256A::ioctl_get_jedec_code(util::jedec::JedecCode * jedec_code)
{
  *jedec_code = _config.readDeviceId();
  return true;
}

bool N25Q256A::ioctl_get_flash_info(NorFlashInfo * info)
{
  *info = FLASH_INFO;
  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* N25Q256A */

} /* memory */

} /* driver */

} /* snowfox */
