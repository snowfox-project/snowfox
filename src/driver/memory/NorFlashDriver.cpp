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

#include <snowfox/driver/memory/NorFlashDriver.h>

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

bool NorFlashDriver::ioctl(uint32_t const cmd, void * arg)
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
  /* IOCTL_GET_FLASH_INFO *************************************************************/
  case IOCTL_GET_FLASH_INFO:
  {
    NorFlashInfo * info = reinterpret_cast<NorFlashInfo *>(arg);
    return ioctl_get_flash_info(info);
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
