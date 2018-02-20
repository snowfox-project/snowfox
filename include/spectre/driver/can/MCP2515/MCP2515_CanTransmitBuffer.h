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

#ifndef INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_MCP2515_CANTRANSMITBUFFER_H_
#define INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_MCP2515_CANTRANSMITBUFFER_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/can/interface/CanTransmitBuffer.h>

#include <stdint.h>

#include <spectre/memory/container/Queue.h>

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

class MCP2515_CanTransmitBuffer : public can::interface::CanTransmitBuffer
{

public:

           MCP2515_CanTransmitBuffer(uint16_t const size);
  virtual ~MCP2515_CanTransmitBuffer();


  virtual bool isFull            (                                        ) override;
  virtual void putData           (hal::interface::CanFrame const can_frame) override;
  virtual void onTransmitComplete(                                        ) override;

private:

  memory::container::Queue<hal::interface::CanFrame> _tx_queue;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_MCP2515_CANTRANSMITBUFFER_H_ */
