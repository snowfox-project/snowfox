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

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/can/MCP2515/MCP2515_CanReceiveBuffer.h>

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
 * CTOR/DTOR
 **************************************************************************************/

MCP2515_CanReceiveBuffer::MCP2515_CanReceiveBuffer(uint16_t const size)
: _rx_queue(size)
{

}

MCP2515_CanReceiveBuffer::~MCP2515_CanReceiveBuffer()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool MCP2515_CanReceiveBuffer::isEmpty()
{
  return _rx_queue.isEmpty();
}

void MCP2515_CanReceiveBuffer::getData(hal::interface::CanFrame * can_frame)
{
  _rx_queue.pop(can_frame);
}

void MCP2515_CanReceiveBuffer::onReceiveComplete(hal::interface::CanFrame const can_frame)
{
  if(!_rx_queue.isFull())
  {
    _rx_queue.push(can_frame);
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */
