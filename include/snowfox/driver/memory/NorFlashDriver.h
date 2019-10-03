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

#ifndef INCLUDE_SNOWFOX_DRIVER_MEMORY_NORFLASHDRIVER_H_
#define INCLUDE_SNOWFOX_DRIVER_MEMORY_NORFLASHDRIVER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/interface/Driver.h>

#include <snowfox/driver/memory/NorFlashInfo.h>
#include <snowfox/driver/memory/util/jedec/JedecCode.h>

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
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_GET_JEDEC_CODE = 0; /* Arg: util::jedec::JedecCode * jedec_code  */
static uint32_t constexpr IOCTL_GET_FLASH_INFO = 1; /* Arg: NorFlashInfo * info */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class NorFlashDriver
{

public:

           NorFlashDriver() { }
  virtual ~NorFlashDriver() { }


  virtual bool    open ()                                                                                              = 0;
  virtual ssize_t read (uint32_t const block, uint32_t const offset, uint8_t       * buffer, uint32_t const num_bytes) = 0;
  virtual ssize_t prog (uint32_t const block, uint32_t const offset, uint8_t const * buffer, uint32_t const num_bytes) = 0;
  virtual bool    erase(uint32_t const block)                                                                          = 0;
  virtual bool    ioctl(uint32_t const cmd, void * arg);
  virtual void    close()                                                                                              = 0;

protected:

  virtual bool    ioctl_get_jedec_code(util::jedec::JedecCode * jedec_code) = 0;
  virtual bool    ioctl_get_flash_info(NorFlashInfo * info)                 = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* memory */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_NORFLASHDRIVER_H_ */
