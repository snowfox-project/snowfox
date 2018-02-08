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

#ifndef INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_MCP2515_H_
#define INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_MCP2515_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/interface/Driver.h>

#include <spectre/driver/can/MCP2515/interface/MCP2515_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace can
{

namespace MCP2515
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_SET_BITRATE = 0; /* Arg: CanBitRate -> uint8_t * */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MCP2515 : public driver::interface::Driver
{

public:

           MCP2515(interface::MCP2515_Control & mcp2515_ctrl, uint8_t const f_mcp2515_MHz);
  virtual ~MCP2515();


  bool    open (                                                  ) override;
  ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override;
  ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override;
  bool    ioctl(uint32_t const   cmd,    void          * arg      ) override;
  void    close(                                                  ) override;


private:

  interface::MCP2515_Control       & _mcp2515_ctrl;
  uint8_t                    const   _f_mcp2515_MHz;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_MCP2515_H_ */
