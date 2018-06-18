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

#ifndef INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_MCP2515_CANCONFIGURATION_H_
#define INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_MCP2515_CANCONFIGURATION_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/can/interface/CanConfiguration.h>

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

class MCP2515_CanConfiguration : public can::interface::CanConfiguration
{

public:

           MCP2515_CanConfiguration(interface::MCP2515_Io & io, uint8_t const f_mcp2515_MHz);
  virtual ~MCP2515_CanConfiguration();


  virtual void setCanBitRate(can::interface::CanBitRate const can_bit_rate) override;


private:

  interface::MCP2515_Io       & _io;
  uint8_t               const   _f_mcp2515_MHz;

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

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_MCP2515_CANCONFIGURATION_H_ */
