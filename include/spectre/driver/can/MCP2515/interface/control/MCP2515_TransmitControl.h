/**
 * Spectre is a modular RTOS with extensive IO support.
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

#ifndef INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_INTERFACE_CONTROL_MCP2515_TRANSMITCONTROL_H_
#define INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_INTERFACE_CONTROL_MCP2515_TRANSMITCONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/util/type/CanFrame.h>

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

namespace interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class TransmitBufferSelect : uint8_t
{
  TB_0 = 0,
  TB_1 = 1,
  TB_2 = 2
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MCP2515_TransmitControl
{

public:

           MCP2515_TransmitControl() { }
  virtual ~MCP2515_TransmitControl() { }


  virtual bool isTransmitRequestPending(TransmitBufferSelect const tx_buf_sel                                           ) = 0;
  virtual void writeToTransmitBuffer   (TransmitBufferSelect const tx_buf_sel, util::type::CanFrame const & frame) = 0;
  virtual void requestTransmit         (TransmitBufferSelect const tx_buf_sel                                           ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_INTERFACE_CONTROL_MCP2515_TRANSMITCONTROL_H_ */
