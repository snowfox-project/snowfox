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

#ifndef INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_MCP2515_CONTROL_H_
#define INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_MCP2515_CONTROL_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/can/MCP2515/interface/MCP2515_Control.h>


#include <spectre/driver/can/MCP2515/interface/MCP2515_Io.h>

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
 * CLASS DECLARATION
 **************************************************************************************/

class MCP2515_Control : public interface::MCP2515_Control
{

public:

           MCP2515_Control(interface::MCP2515_Io & io);
  virtual ~MCP2515_Control();


  virtual void setCanBitRate(uint8_t const clk_MHz, interface::CanBitRate const can_bit_rate) override;


private:

  interface::MCP2515_Io & _io;

  void setCanBitRate_Clock_8MHz (interface::CanBitRate const can_bit_rate);
  void setCanBitRate_Clock_16MHz(interface::CanBitRate const can_bit_rate);
  void setCanBitRate_Clock_20MHz(interface::CanBitRate const can_bit_rate);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_MCP2515_CONTROL_H_ */
