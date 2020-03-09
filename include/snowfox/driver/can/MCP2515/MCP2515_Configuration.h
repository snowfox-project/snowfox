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

#ifndef INCLUDE_SNOWFOX_DRIVER_CAN_MCP2515_MCP2515_CONFIGURATION_H_
#define INCLUDE_SNOWFOX_DRIVER_CAN_MCP2515_MCP2515_CONFIGURATION_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/can/MCP2515/interface/configuration/MCP2515_Configuration.h>

#include <snowfox/driver/can/MCP2515/interface/MCP2515_Io.h>

#include <snowfox/hal/interface/delay/Delay.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace can
{

namespace MCP2515
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MCP2515_Configuration : public interface::MCP2515_Configuration
{

public:

           MCP2515_Configuration(interface::MCP2515_Io & io, hal::interface::Delay & delay, uint8_t const f_mcp2515_MHz);
  virtual ~MCP2515_Configuration();


  virtual bool setOperationMode(interface::OperationMode const op_mode)        override;
  virtual void setCanBitRate   (can::interface::CanBitRate const can_bit_rate) override;


private:

  interface::MCP2515_Io & _io;
  hal::interface::Delay & _delay;
  uint8_t const           _f_mcp2515_MHz;


  void setCanBitRate_Clock_8MHz (can::interface::CanBitRate const can_bit_rate);
  void setCanBitRate_Clock_16MHz(can::interface::CanBitRate const can_bit_rate);
  void setCanBitRate_Clock_20MHz(can::interface::CanBitRate const can_bit_rate);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_CAN_MCP2515_MCP2515_CONFIGURATION_H_ */
