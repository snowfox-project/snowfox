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
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/can/MCP2515/interface/control/MCP2515_Control.h>

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


  virtual uint8_t getEventFlags (                                          ) override;
  virtual void    clearEventFlag(interface::EventFlag      const event_flag) override;


  virtual bool    isTxPending   (interface::TransmitBuffer const tx_buf                                        ) override;
  virtual void    loadTxBuffer  (interface::TransmitBuffer const tx_buf, hal::interface::CanFrame const & frame) override;


private:

  interface::MCP2515_Io & _io;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_MCP2515_CONTROL_H_ */
