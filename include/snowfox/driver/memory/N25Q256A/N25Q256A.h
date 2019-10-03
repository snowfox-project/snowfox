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

#include <snowfox/driver/memory/NorFlashDriver.h>

#include <snowfox/driver/memory/N25Q256A/interface/N25Q256A_Status.h>
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

class N25Q256A : public NorFlashDriver
{

public:
           N25Q256A(interface::N25Q256A_Configuration & config,
                    interface::N25Q256A_Control       & control,
                    interface::N25Q256A_Status        & status);
  virtual ~N25Q256A();


  virtual bool    open ()                                                                                              override;
  virtual ssize_t read (uint32_t const block, uint32_t const offset, uint8_t       * buffer, uint32_t const num_bytes) override;
  virtual ssize_t prog (uint32_t const block, uint32_t const offset, uint8_t const * buffer, uint32_t const num_bytes) override;
  virtual bool    erase(uint32_t const block)                                                                          override;
  virtual void    close()                                                                                              override;

protected:

  virtual bool    ioctl_get_jedec_code(util::jedec::JedecCode * jedec_code) override;
  virtual bool    ioctl_get_flash_info(NorFlashInfo * info)                 override;

private:

  interface::N25Q256A_Configuration & _config;
  interface::N25Q256A_Control       & _control;
  interface::N25Q256A_Status        & _status;

  static interface::AddressMode const ADDRESS_MODE = interface::AddressMode::AM_4Byte;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* N25Q256A */

} /* memory */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_N25Q256A_H_ */
