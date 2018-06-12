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

#include <spectre/driver/can/MCP2515/events/MCP2515_onTransmitBufferEmpty.h>

#include <spectre/driver/can/MCP2515/interface/MCP2515_RegisterBits.h>

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

MCP2515_onTransmitBufferEmpty::MCP2515_onTransmitBufferEmpty(interface::MCP2515_Io & io, can::interface::CanFrameBuffer & can_tx_buf)
: _io        (io        ),
  _can_tx_buf(can_tx_buf)
{

}

MCP2515_onTransmitBufferEmpty::~MCP2515_onTransmitBufferEmpty()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void MCP2515_onTransmitBufferEmpty::onTransmitBufferEmpty()
{
  if(!_can_tx_buf.isEmpty())
  {
    hal::interface::CanFrame frame;
    _can_tx_buf.pop(&frame);

    uint8_t sidh = static_cast<uint8_t>(frame.id & 0x000007F8);      /* SID10 - SID3 */
    uint8_t sidl = static_cast<uint8_t>(frame.id & 0x00000007) << 5; /* SID2  - SID0 */
    uint8_t dlc  = (frame.dlc & 0x0F);
    uint8_t eid8 = 0;
    uint8_t eid0 = 0;

    if(hal::interface::isExtendedId(frame))
    {
      sidl |= MCP2515_REG_TXBnSIDL_EXIDE_bm;
      sidl |= static_cast<uint8_t>(frame.id & 0x18000000); /* EID17 - EID16 */
      eid8  = static_cast<uint8_t>(frame.id & 0x07F80000); /* EID15 - EID8 */
      eid0  = static_cast<uint8_t>(frame.id & 0x0007F800); /* EID7  - EID0 */
    }

    if(hal::interface::isRTR(frame))
    {
      dlc |= MCP2515_REG_TXBnDLC_RTR_bm;
    }

    uint8_t tx_buf[interface::MCP2515_Io::TX_BUF_MAX_SIZE] =
    {
      sidh,
      sidl,
      eid8,
      eid0,
      dlc,
      frame.data[0],
      frame.data[1],
      frame.data[2],
      frame.data[3],
      frame.data[4],
      frame.data[5],
      frame.data[6],
      frame.data[7]
    };

    /* TODO: Determine which transmit buffer is empty and load said transmit buffer, e.g. TX0 */
    _io.loadTx0(tx_buf);

    /* TODO: Load via SPI to MCP2515 and enable transmission */
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */
