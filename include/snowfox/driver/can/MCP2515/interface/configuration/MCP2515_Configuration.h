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

#ifndef INCLUDE_SNOWFOX_DRIVER_CAN_MCP2515_INTERFACE_CONFIGURATION_MCP2515_CONFIGURATION_H_
#define INCLUDE_SNOWFOX_DRIVER_CAN_MCP2515_INTERFACE_CONFIGURATION_MCP2515_CONFIGURATION_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include <snowfox/driver/can/interface/CanConfiguration.h>

#include <snowfox/driver/can/MCP2515/interface/MCP2515_RegisterBits.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::can::MCP2515::interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class OperationMode : uint8_t
{
  Normal     = 0,
  Sleep      =                                                                 MCP2515_REG_CANCTRL_REQOP0_bm,
  Loopback   =                                 MCP2515_REG_CANCTRL_REQOP1_bm,
  ListenOnly =                                 MCP2515_REG_CANCTRL_REQOP1_bm | MCP2515_REG_CANCTRL_REQOP0_bm,
  Config     = MCP2515_REG_CANCTRL_REQOP2_bm
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MCP2515_Configuration
{

public:

  virtual ~MCP2515_Configuration() { }


  virtual bool setOperationMode(OperationMode const op_mode)                   = 0;
  virtual void setCanBitRate   (can::interface::CanBitRate const can_bit_rate) = 0;


};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::can::MCP2515::interface */

#endif /* INCLUDE_SNOWFOX_DRIVER_CAN_MCP2515_INTERFACE_CONFIGURATION_MCP2515_CONFIGURATION_H_ */
