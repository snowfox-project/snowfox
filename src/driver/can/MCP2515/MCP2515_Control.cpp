/**
 * Snowfox is a modular RTOS with extensive IO support.
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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/can/MCP2515/MCP2515_Control.h>

#include <string.h>

#include <snowfox/driver/can/MCP2515/interface/MCP2515_RegisterBits.h>

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
 * CTOR/DTOR
 **************************************************************************************/

MCP2515_Control::MCP2515_Control(interface::MCP2515_Io & io)
: _io(io)
{

}

MCP2515_Control::~MCP2515_Control()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

uint8_t MCP2515_Control::getEventFlags()
{
  uint8_t reg_cantintf_content = 0;

  _io.readRegister(interface::Register::CANINTF, &reg_cantintf_content);

  return reg_cantintf_content;
}

void MCP2515_Control::clearEventFlag(interface::EventFlag const event_flag)
{
  /* The interrupt request flag can be cleared by writing
   * a '0' to the corresponding bit in the IRQ register.
   */

  uint8_t reg_cantintf_content = 0;

  _io.readRegister(interface::Register::CANINTF, &reg_cantintf_content);

  reg_cantintf_content &= ~(static_cast<uint8_t>(event_flag));

  _io.writeRegister(interface::Register::CANINTF, reg_cantintf_content);
}

bool MCP2515_Control::isTransmitRequestPending(interface::TransmitBufferSelect const tx_buf_sel)
{
  uint8_t reg_txbnctrl_content = 0;

  switch(tx_buf_sel)
  {
  case interface::TransmitBufferSelect::TB_0: _io.readRegister(interface::Register::TXB0CTRL, &reg_txbnctrl_content); break;
  case interface::TransmitBufferSelect::TB_1: _io.readRegister(interface::Register::TXB1CTRL, &reg_txbnctrl_content); break;
  case interface::TransmitBufferSelect::TB_2: _io.readRegister(interface::Register::TXB2CTRL, &reg_txbnctrl_content); break;
  }

  bool const is_tx_pending = (reg_txbnctrl_content & MCP2515_REG_TXBnCTRL_TXREQ_bm) == MCP2515_REG_TXBnCTRL_TXREQ_bm;

  return is_tx_pending;
}

void MCP2515_Control::writeToTransmitBuffer(interface::TransmitBufferSelect const tx_buf_sel, util::type::CanFrame const & frame)
{
  uint8_t sidh = static_cast<uint8_t>(frame.id & 0x000007F8);      /* SID10 - SID3 */
  uint8_t sidl = static_cast<uint8_t>(frame.id & 0x00000007) << 5; /* SID2  - SID0 */
  uint8_t dlc  = (frame.dlc & 0x0F);
  uint8_t eid8 = 0;
  uint8_t eid0 = 0;

  if(util::type::isExtendedId(frame))
  {
    sidl |= MCP2515_REG_TXBnSIDL_EXIDE_bm;
    sidl |= static_cast<uint8_t>(frame.id & 0x18000000); /* EID17 - EID16 */
    eid8  = static_cast<uint8_t>(frame.id & 0x07F80000); /* EID15 - EID8 */
    eid0  = static_cast<uint8_t>(frame.id & 0x0007F800); /* EID7  - EID0 */
  }

  if(util::type::isRTR(frame))
  {
    dlc |= MCP2515_REG_TXBnDLC_RTR_bm;
  }

  uint8_t tx_buf_content[interface::MCP2515_Io::TX_BUF_MAX_SIZE] =
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

  switch(tx_buf_sel)
  {
  case interface::TransmitBufferSelect::TB_0: _io.loadTx0(tx_buf_content); break;
  case interface::TransmitBufferSelect::TB_1: _io.loadTx1(tx_buf_content); break;
  case interface::TransmitBufferSelect::TB_2: _io.loadTx2(tx_buf_content); break;
  }
}

void MCP2515_Control::requestTransmit(interface::TransmitBufferSelect const tx_buf_sel)
{
  switch(tx_buf_sel)
  {
  case interface::TransmitBufferSelect::TB_0: _io.requestToTransmitTx0(); break;
  case interface::TransmitBufferSelect::TB_1: _io.requestToTransmitTx1(); break;
  case interface::TransmitBufferSelect::TB_2: _io.requestToTransmitTx2(); break;
  }
}

void MCP2515_Control::readFromReceiveBuffer(interface::ReceiveBufferSelect const rx_buf_sel, util::type::CanFrame * frame)
{
  uint8_t rx_buf_content[interface::MCP2515_Io::RX_BUF_MAX_SIZE] = { 0 };

  switch(rx_buf_sel)
  {
  case interface::ReceiveBufferSelect::RB_0: _io.readRx0(rx_buf_content); break;
  case interface::ReceiveBufferSelect::RB_1: _io.readRx1(rx_buf_content); break;
  }

  uint8_t const sidh = rx_buf_content[0];
  uint8_t const sidl = rx_buf_content[1];
  uint8_t const dlc  = rx_buf_content[2];
  uint8_t const eid8 = rx_buf_content[3];
  uint8_t const eid0 = rx_buf_content[4];


  bool const is_extended_id     = (sidl & MCP2515_REG_RXBnSIDL_IDE_bm) == MCP2515_REG_RXBnSIDL_IDE_bm;
  bool const is_rtr_standard_id = (sidl & MCP2515_REG_RXBnSIDL_SRR_bm) == MCP2515_REG_RXBnSIDL_SRR_bm;
  bool const is_rtr_extended_id = (dlc  & MCP2515_REG_RXBnDLC_RTR_bm ) == MCP2515_REG_RXBnDLC_RTR_bm ;

  frame->id  = static_cast<uint32_t>(sidh       ) <<  3; /* SID10 - SID3  */
  frame->id |= static_cast<uint32_t>(sidl & 0xE0) >>  5; /* SID2  - SID0  */

  if(is_extended_id)
  {
    frame->id |= static_cast<uint32_t>(sidl & 0x03) << 27; /* EID17 - EID16 */
    frame->id |= static_cast<uint32_t>(eid8       ) << 19; /* EID15 - EID8  */
    frame->id |= static_cast<uint32_t>(eid0       ) << 11; /* EID7  - EID0  */
  }

  if(is_rtr_standard_id && !is_extended_id) frame->id |= util::type::CAN_RTR_BITMASK;
  if(is_rtr_extended_id &&  is_extended_id) frame->id |= util::type::CAN_RTR_BITMASK;

  frame->dlc = (dlc & 0x0F);

  memcpy(frame->data, rx_buf_content + 5, frame->dlc);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* snowfox */
