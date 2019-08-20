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

bool NorDriver::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* IOCTL_ERASE_CHIP *****************************************************************/
  case IOCTL_ERASE_CHIP:
  {
    return iotcl_erase_chip();
  }
  break;
  /* IOCTL_ERASE_SECTOR ***************************************************************/
  case IOCTL_ERASE_SECTOR:
  {
    uint32_t const * sector = static_cast<uint32_t const *>(arg);
    return ioctl_erase_sector(*sector);
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
