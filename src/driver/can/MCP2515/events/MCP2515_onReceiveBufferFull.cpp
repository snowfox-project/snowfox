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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/can/MCP2515/events/MCP2515_onReceiveBufferFull.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::can::MCP2515
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

MCP2515_onReceiveBufferFull::MCP2515_onReceiveBufferFull(can::interface::CanFrameBuffer & can_rx_buf, interface::MCP2515_ReceiveControl & ctrl)
: _can_rx_buf(can_rx_buf),
  _ctrl      (ctrl      )
{

}

MCP2515_onReceiveBufferFull::~MCP2515_onReceiveBufferFull()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void MCP2515_onReceiveBufferFull::onReceiveBufferFull(interface::ReceiveBufferSelect const rx_buf_sel)
{
  if(!_can_rx_buf.isFull())
  {
    util::type::CanFrame frame;

    _ctrl.readFromReceiveBuffer(rx_buf_sel, &frame);

    _can_rx_buf.push(frame);
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::can::MCP2515 */
