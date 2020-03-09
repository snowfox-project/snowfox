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

#ifndef INCLUDE_SNOWFOX_DRIVER_CONSOLE_CONSOLE_H_
#define INCLUDE_SNOWFOX_DRIVER_CONSOLE_CONSOLE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/interface/Driver.h>

#include <snowfox/driver/serial/interface/SerialControl.h>
#include <snowfox/driver/serial/interface/SerialConfiguration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace serial
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_SET_BAUDRATE = 0; /* Arg: SerialBaudRate -> uint8_t * */
static uint32_t constexpr IOCTL_SET_PARITY   = 1; /* Arg: SerialParity   -> uint8_t * */
static uint32_t constexpr IOCTL_SET_STOPBIT  = 2; /* Arg: SerialStopBit  -> uint8_t * */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class Serial final : public driver::interface::Driver
{

public:


           Serial(interface::SerialConfiguration & config,
                  interface::SerialControl       & control);
  virtual ~Serial();


  bool    open (                                                  ) override;
  ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override;
  ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override;
  bool    ioctl(uint32_t const   cmd,    void          * arg      ) override;
  void    close(                                                  ) override;


private:

  interface::SerialConfiguration & _config;
  interface::SerialControl       & _control;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* serial */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_CONSOLE_CONSOLE_H_ */
