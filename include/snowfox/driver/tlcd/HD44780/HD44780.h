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

#ifndef INCLUDE_SNOWFOX_DRIVER_TLCD_HD44780_HD44780_H_
#define INCLUDE_SNOWFOX_DRIVER_TLCD_HD44780_HD44780_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/interface/Driver.h>

#include <snowfox/driver/tlcd/HD44780/interface/HD44780_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace tlcd
{

namespace HD44780
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_CLEAR_DISPLAY = 0; /* Arg: None */
static uint32_t constexpr IOCTL_RETURN_HOME   = 1; /* Arg: None */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class HD44780 final : public driver::interface::Driver
{

public:


           HD44780(interface::HD44780_Control & ctrl);
  virtual ~HD44780();


  bool    open (                                                  ) override final;
  ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override final;
  ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override final;
  bool    ioctl(uint32_t const   cmd,    void          * arg      ) override final;
  void    close(                                                  ) override final;


private:

  interface::HD44780_Control & _ctrl;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* HD44780 */

} /* tlcd */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_TLCD_HD44780_HD44780_H_ */
