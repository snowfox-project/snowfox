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

#ifndef INCLUDE_SNOWFOX_DRIVER_MEMORY_NORDRIVER_H_
#define INCLUDE_SNOWFOX_DRIVER_MEMORY_NORDRIVER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/interface/Driver.h>

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

static uint32_t constexpr IOCTL_ERASE_CHIP   = 0; /* Arg: none              */
static uint32_t constexpr IOCTL_ERASE_SECTOR = 1; /* Arg: uint32_t * sector */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class NorDriver : public interface::Driver
{

public:

           NorDriver() { }
  virtual ~NorDriver() { }


  virtual bool    open (                                                  ) = 0;
  virtual ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) = 0;
  virtual ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) = 0;
  virtual bool    ioctl(uint32_t const   cmd,    void          * arg      ) override;
  virtual void    close(                                                  ) = 0;

protected:

  virtual bool iotcl_erase_chip  (                     ) = 0;
  virtual bool ioctl_erase_sector(uint32_t const sector) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* memory */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_NORDRIVER_H_ */
