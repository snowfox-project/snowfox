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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/can/MCP2515/events/MCP2515_EventCallback.h>

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

MCP2515_EventCallback::MCP2515_EventCallback(interface::MCP2515_EventControl          & event_ctrl,
                                             interface::MCP2515_onMessageError        & on_message_error,
                                             interface::MCP2515_onWakeup              & on_wakeup,
                                             interface::MCP2515_onTransmitBufferEmpty & on_transmit_buffer_2_empty,
                                             interface::MCP2515_onTransmitBufferEmpty & on_transmit_buffer_1_empty,
                                             interface::MCP2515_onTransmitBufferEmpty & on_transmit_buffer_0_empty,
                                             interface::MCP2515_onReceiveBufferFull   & on_receive_buffer_1_full,
                                             interface::MCP2515_onReceiveBufferFull   & on_receive_buffer_0_full)
: _event_ctrl                 (event_ctrl                ),
  _on_message_error           (on_message_error          ),
  _on_wakeup                  (on_wakeup                 ),
  _on_transmit_buffer_2_empty (on_transmit_buffer_2_empty),
  _on_transmit_buffer_1_empty (on_transmit_buffer_1_empty),
  _on_transmit_buffer_0_empty (on_transmit_buffer_0_empty),
  _on_receive_buffer_1_full   (on_receive_buffer_1_full  ),
  _on_receive_buffer_0_full   (on_receive_buffer_0_full  )
{

}

MCP2515_EventCallback::~MCP2515_EventCallback()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void MCP2515_EventCallback::onExternalEvent()
{
  uint8_t const event_flags = _event_ctrl.getEventFlags();

  /* MESSAGE ERROR ********************************************************************/
  if(interface::MCP2515_EventControl::isMessageErrorEvent(event_flags))
  {
    _on_message_error.onMessageError();
    _event_ctrl.clearEventFlag(interface::EventFlag::MessageError);
  }
  /* WAKEUP ***************************************************************************/
  if(interface::MCP2515_EventControl::isWakeupEvent(event_flags))
  {
    _on_wakeup.onWakeup();
    _event_ctrl.clearEventFlag(interface::EventFlag::Wakeup);
  }
  /* GENERAL ERROR ********************************************************************/
  if(interface::MCP2515_EventControl::isGeneralErrorEvent(event_flags))
  {
    /* No callback yet */
    _event_ctrl.clearEventFlag(interface::EventFlag::GeneralError);
  }
  /* TRANSMIT BUFFER 2 EMPTY **********************************************************/
  if(interface::MCP2515_EventControl::isTxBuf2EmptyEvent(event_flags))
  {
    _on_transmit_buffer_2_empty.onTransmitBufferEmpty(interface::TransmitBufferSelect::TB_2);
    _event_ctrl.clearEventFlag(interface::EventFlag::TxBuf2Empty);
  }
  /* TRANSMIT BUFFER 1 EMPTY **********************************************************/
  if(interface::MCP2515_EventControl::isTxBuf1EmptyEvent(event_flags))
  {
    _on_transmit_buffer_1_empty.onTransmitBufferEmpty(interface::TransmitBufferSelect::TB_1);
    _event_ctrl.clearEventFlag(interface::EventFlag::TxBuf1Empty);
  }
  /* TRANSMIT BUFFER 0 EMPTY **********************************************************/
  if(interface::MCP2515_EventControl::isTxBuf0EmptyEvent(event_flags))
  {
    _on_transmit_buffer_0_empty.onTransmitBufferEmpty(interface::TransmitBufferSelect::TB_0);
    _event_ctrl.clearEventFlag(interface::EventFlag::TxBuf0Empty);
  }
  /* RECEIVE BUFFER 1 FULL ************************************************************/
  if(interface::MCP2515_EventControl::isRxBuf1FullEvent(event_flags))
  {
    _on_receive_buffer_1_full.onReceiveBufferFull(interface::ReceiveBufferSelect::RB_1);
    _event_ctrl.clearEventFlag(interface::EventFlag::RxBuf1Full);
  }
  /* RECEIVE BUFFER 0 FULL ************************************************************/
  if(interface::MCP2515_EventControl::isRxBuf0FullEvent(event_flags))
  {
    _on_receive_buffer_0_full.onReceiveBufferFull(interface::ReceiveBufferSelect::RB_0);
    _event_ctrl.clearEventFlag(interface::EventFlag::RxBuf0Full);
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */
