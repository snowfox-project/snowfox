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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/can/MCP2515/interface/control/MCP2515_EventControl.h>

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
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool MCP2515_EventControl::isMessageErrorEvent(uint8_t const event_flags)
{
  return ((event_flags & MCP2515_REG_CANINTF_MERRF_bm) == MCP2515_REG_CANINTF_MERRF_bm);
}

bool MCP2515_EventControl::isWakeupEvent(uint8_t const event_flags)
{
  return ((event_flags & MCP2515_REG_CANINTF_WAKIF_bm) == MCP2515_REG_CANINTF_WAKIF_bm);
}

bool MCP2515_EventControl::isGeneralErrorEvent(uint8_t const event_flags)
{
  return ((event_flags & MCP2515_REG_CANINTF_ERRIF_bm) == MCP2515_REG_CANINTF_ERRIF_bm);
}

bool MCP2515_EventControl::isTxBuf2EmptyEvent(uint8_t const event_flags)
{
  return ((event_flags & MCP2515_REG_CANINTF_TX2IF_bm) == MCP2515_REG_CANINTF_TX2IF_bm);
}

bool MCP2515_EventControl::isTxBuf1EmptyEvent(uint8_t const event_flags)
{
  return ((event_flags & MCP2515_REG_CANINTF_TX1IF_bm) == MCP2515_REG_CANINTF_TX1IF_bm);
}

bool MCP2515_EventControl::isTxBuf0EmptyEvent(uint8_t const event_flags)
{
  return ((event_flags & MCP2515_REG_CANINTF_TX0IF_bm) == MCP2515_REG_CANINTF_TX0IF_bm);
}

bool MCP2515_EventControl::isRxBuf1FullEvent(uint8_t const event_flags)
{
  return ((event_flags & MCP2515_REG_CANINTF_RX1IF_bm) == MCP2515_REG_CANINTF_RX1IF_bm);
}

bool MCP2515_EventControl::isRxBuf0FullEvent(uint8_t const event_flags)
{
  return ((event_flags & MCP2515_REG_CANINTF_RX0IF_bm) == MCP2515_REG_CANINTF_RX0IF_bm);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */
