/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SPECTRE_DRIVER_CAN_CAN_H_
#define INCLUDE_SPECTRE_DRIVER_CAN_CAN_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/interface/Driver.h>

#include <spectre/driver/can/interface/CanControl.h>
#include <spectre/driver/can/interface/CanConfiguration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace can
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_SET_BITRATE = 0; /* Arg: CanBitRate -> uint8_t * */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class Can : public driver::interface::Driver
{

public:

           Can(interface::CanConfiguration & config, interface::CanControl & control);
  virtual ~Can();


  bool    open (                                                  ) override;
  ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override;
  ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override;
  bool    ioctl(uint32_t const   cmd,    void          * arg      ) override;
  void    close(                                                  ) override;


private:

  interface::CanConfiguration & _config;
  interface::CanControl       & _control;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* can */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_CAN_CAN_H_ */
