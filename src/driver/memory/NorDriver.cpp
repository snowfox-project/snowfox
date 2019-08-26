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

#include <snowfox/driver/memory/NorDriver.h>

#include <string.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace memory
{

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

ssize_t NorDriver::read(uint8_t * buffer, ssize_t const num_bytes)
{
  /* The read address is contained in first 4 bytes of the buffer */
  uint32_t read_addr = 0;
  memcpy(reinterpret_cast<void *>(&read_addr), buffer, sizeof(read_addr));
  uint8_t * read_buffer = buffer + sizeof(read_addr);
  ssize_t read_num_bytes = num_bytes - sizeof(read_addr);

  /* The actual read call is handled by the template method implemented
   * in the derived base class.
   */
  return read(read_addr, read_buffer, read_num_bytes);
}

ssize_t NorDriver::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  /* The write address is contained in first 4 bytes of the buffer */
  uint32_t write_addr = 0;
  memcpy(reinterpret_cast<void *>(&write_addr), buffer, sizeof(write_addr));
  uint8_t const * write_buffer = buffer + sizeof(write_addr);
  ssize_t write_num_bytes = num_bytes - sizeof(write_addr);

  /* The actual write call is handled by the template method implemented
   * in the derived base class.
   */
  return write(write_addr, write_buffer, write_num_bytes);
}

bool NorDriver::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* IOCTL_GET_CAPABILITIES ***********************************************************/
  case IOCTL_GET_CAPABILITIES:
  {
    NorDriverCapabilities * capabilities = static_cast<NorDriverCapabilities *>(arg);
    return ioctl_get_capabilities(capabilities);
  }
  break;
  /* IOCTL_ERASE **********************************************************************/
  case IOCTL_ERASE:
  {
    uint32_t const * erase_block_num = static_cast<uint32_t const *>(arg);
    return ioctl_erase(*erase_block_num);
  }
  break;
  }

  return false;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* memory */

} /* driver */

} /* snowfox */
