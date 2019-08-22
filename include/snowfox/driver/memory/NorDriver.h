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
 * TYPEDEF
 **************************************************************************************/

typedef struct
{
  /* Constants describing the size and the memory layout */
  uint32_t sector_size;
  uint32_t sector_num;
  uint32_t subsector_size;
  uint32_t subsector_num;
  /* Constants describing the capabilities of the flash */
  bool sector_erase;
  bool subsector_erase;
} NorDriverCapabilities;

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_GET_CAPABILITIES = 0; /* Arg: NorDriverCapabilities * capabilities */
static uint32_t constexpr IOCTL_ERASE_CHIP       = 1; /* Arg: none                                 */
static uint32_t constexpr IOCTL_ERASE_SECTOR     = 2; /* Arg: uint32_t * sector                    */
static uint32_t constexpr IOCTL_ERASE_SUBSECTOR  = 3; /* Arg: uint32_t * subsector                 */

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

  virtual bool ioctl_get_capabilities(NorDriverCapabilities * capabilities) = 0;
  virtual bool iotcl_erase_chip      (                                    ) = 0;
  virtual bool ioctl_erase_sector    (uint32_t const sector_num           ) = 0;
  virtual bool ioctl_erase_subsector (uint32_t const subsector_num        ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* memory */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_NORDRIVER_H_ */
