/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MAX6921_MAX6921_H_
#define INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MAX6921_MAX6921_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/interface/Driver.h>

#include <snowfox/driver/ioexpander/MAX6921/interface/MAX6921_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace ioexpander
{

namespace MAX6921
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_SET_SEGMENT = 0; /* Arg: uint8_t * */
static uint32_t constexpr IOCTL_CLR_SEGMENT = 1; /* Arg: uint8_t * */
static uint32_t constexpr IOCTL_WRITE       = 2; /* Arg: none      */
static uint32_t constexpr IOCTL_LOAD        = 3; /* Arg: none      */
static uint32_t constexpr IOCTL_BLANK       = 4; /* Arg: none      */
static uint32_t constexpr IOCTL_NO_BLANK    = 5; /* Arg: none      */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MAX6921 final : public driver::interface::Driver
{

public:

           MAX6921(interface::MAX6921_Control & control);
  virtual ~MAX6921();


  virtual bool    open (                                                  ) override;
  virtual ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override;
  virtual ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override;
  virtual bool    ioctl(uint32_t const   cmd,    void          * arg      ) override;
  virtual void    close(                                                  ) override;

private:

  interface::MAX6921_Control & _control;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MAX6921 */

} /* ioexpander */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MAX6921_MAX6921_H_ */
