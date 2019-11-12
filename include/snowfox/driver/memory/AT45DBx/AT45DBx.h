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

#ifndef INCLUDE_SNOWFOX_DRIVER_MEMORY_AT45DBX_H_
#define INCLUDE_SNOWFOX_DRIVER_MEMORY_AT45DBX_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/interface/Driver.h>

#include <snowfox/driver/memory/AT45DBx/interface/AT45DBx_Control.h>
#include <snowfox/driver/memory/AT45DBx/interface/AT45DBx_Configuration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace memory
{

namespace AT45DBx
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_GET_CHIP_SIZE_BYTE = 0; /* Arg: uint32_t * */
static uint32_t constexpr IOCTL_ERASE_CHIP         = 1; /* Arg: None       */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AT45DBx final : public driver::interface::Driver
{

public:

           AT45DBx(interface::AT45DBx_Configuration & config,
                   interface::AT45DBx_Control       & control);
  virtual ~AT45DBx();


  virtual bool    open (                                                  ) override final;
  virtual ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override final;
  virtual ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override final;
  virtual bool    ioctl(uint32_t const   cmd,    void          * arg      ) override final;
  virtual void    close(                                                  ) override final;


private:

  interface::AT45DBx_Configuration & _config;
  interface::AT45DBx_Control       & _control;

  uint32_t                           _page_size,
                                     _num_pages;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT45DBx */

} /* memory */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_AT45DBX_H_ */
