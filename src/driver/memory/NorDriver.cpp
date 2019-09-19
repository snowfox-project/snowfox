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
  return read(toReadAddr(buffer), toReadBuffer(buffer), toReadNumBytes(num_bytes));
}

ssize_t NorDriver::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  return write(toWriteAddr(buffer), toWriteBuffer(buffer), toWriteNumBytes(num_bytes));
}

bool NorDriver::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* IOCTL_GET_JEDEC_CODE *************************************************************/
  case IOCTL_GET_JEDEC_CODE:
  {
    util::jedec::JedecCode * jedec_code = reinterpret_cast<util::jedec::JedecCode *>(arg);
    return ioctl_get_jedec_code(jedec_code);
  }
  break;
  /* IOCTL_GET_CAPABILITIES ***********************************************************/
  case IOCTL_GET_CAPABILITIES:
  {
    NorDriverCapabilities * capabilities = reinterpret_cast<NorDriverCapabilities *>(arg);
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
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

uint32_t NorDriver::toReadAddr(uint8_t * buffer)
{
  uint32_t read_addr = 0;
  memcpy(reinterpret_cast<void *>(&read_addr), buffer, READ_ADDR_SIZE);
  return read_addr;
}

uint32_t NorDriver::toWriteAddr(uint8_t const * buffer)
{
  uint32_t write_addr = 0;
  memcpy(reinterpret_cast<void *>(&write_addr), buffer, WRITE_ADDR_SIZE);
  return write_addr;
}

uint8_t * NorDriver::toReadBuffer(uint8_t * buffer)
{
  return (buffer + READ_ADDR_SIZE);
}

uint8_t const * NorDriver::toWriteBuffer(uint8_t const * buffer)
{
  return (buffer + WRITE_ADDR_SIZE);
}

ssize_t NorDriver::toReadNumBytes(ssize_t const num_bytes)
{
  return (num_bytes - READ_ADDR_SIZE);
}

ssize_t NorDriver::toWriteNumBytes(ssize_t const num_bytes)
{
  return (num_bytes - WRITE_ADDR_SIZE);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* memory */

} /* driver */

} /* snowfox */
