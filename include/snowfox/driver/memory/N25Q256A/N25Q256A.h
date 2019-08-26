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

#ifndef INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_N25Q256A_H_
#define INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_N25Q256A_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/memory/NorDriver.h>

#include <snowfox/driver/memory/N25Q256A/interface/N25Q256A_Control.h>
#include <snowfox/driver/memory/N25Q256A/interface/N25Q256A_Configuration.h>

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
 * CLASS DECLARATION
 **************************************************************************************/

class N25Q256A : public NorDriver
{

public:
           N25Q256A(interface::N25Q256A_Configuration & config,
                    interface::N25Q256A_Control       & control);
  virtual ~N25Q256A();


  virtual bool    open (                                                  ) override;
  virtual ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override;
  virtual ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override;
  virtual void    close(                                                  ) override;

protected:

  virtual bool ioctl_get_capabilities(NorDriverCapabilities * capabilities) override;
  virtual bool ioctl_erase           (uint32_t const erase_block_num      ) override;

private:

  interface::N25Q256A_Configuration & _config;
  interface::N25Q256A_Control & _control;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* N25Q256A */

} /* memory */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_N25Q256A_H_ */
