/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SPECTRE_DRIVER_MEMORY_AT45DBX_H_
#define INCLUDE_SPECTRE_DRIVER_MEMORY_AT45DBX_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/interface/Driver.h>

#include <spectre/driver/memory/AT45DBx/interface/AT45DBx_Control.h>
#include <spectre/driver/memory/AT45DBx/interface/AT45DBx_Configuration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace memory
{

namespace AT45DBx
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AT45DBx : public driver::interface::Driver
{

public:

           AT45DBx(interface::AT45DBx_Configuration & config,
                   interface::AT45DBx_Control       & control);
  virtual ~AT45DBx();


  virtual bool    open (                                                  ) override;
  virtual ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override;
  virtual ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override;
  virtual bool    ioctl(uint32_t const   cmd,    void          * arg      ) override;
  virtual void    close(                                                  ) override;


private:

  interface::AT45DBx_Configuration & _config;
  interface::AT45DBx_Control       & _control;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT45DBx */

} /* memory */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_MEMORY_AT45DBX_H_ */
