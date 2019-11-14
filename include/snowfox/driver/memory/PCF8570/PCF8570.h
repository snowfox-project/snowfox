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

#ifndef INCLUDE_SNOWFOX_DRIVER_MEMORY_PCF8570_PCF8570_H_
#define INCLUDE_SNOWFOX_DRIVER_MEMORY_PCF8570_PCF8570_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/interface/Driver.h>

#include <snowfox/driver/memory/PCF8570/interface/PCF8570_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace memory
{

namespace PCF8570
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class PCF8570 final : public driver::interface::Driver
{

public:

           PCF8570(interface::PCF8570_Control & ctrl);
  virtual ~PCF8570();


  virtual bool    open (                                                  ) override;
  virtual ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override;
  virtual ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override;
  virtual bool    ioctl(uint32_t const   cmd,    void          * arg      ) override;
  virtual void    close(                                                  ) override;

private:

  interface::PCF8570_Control & _ctrl;

  bool read (uint8_t const address, uint8_t       * buffer, uint32_t const num_bytes);
  bool write(uint8_t const address, uint8_t const * buffer, uint32_t const num_bytes);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* PCF8570 */

} /* memory */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_PCF8570_PCF8570_H_ */
