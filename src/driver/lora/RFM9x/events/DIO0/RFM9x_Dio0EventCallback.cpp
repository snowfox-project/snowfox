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

#include <spectre/driver/lora/RFM9x/events/DIO0/RFM9x_Dio0EventCallback.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace lora
{

namespace RFM9x
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RFM9x_Dio0EventCallback::RFM9x_Dio0EventCallback(interface::RFM9x_EventControl      & event_ctrl,
                                                 interface::RFM9x_onTxDoneCallback  & on_tx_done_callback,
                                                 interface::RFM9x_onRxDoneCallback  & on_rx_done_callback,
                                                 interface::RFM9x_onCadDoneCallback & on_cad_done_callback)
: _event_ctrl           (event_ctrl          ),
  _on_tx_done_callback  (on_tx_done_callback ),
  _on_rx_done_callback  (on_rx_done_callback ),
  _on_cad_done_callback (on_cad_done_callback)
{

}

RFM9x_Dio0EventCallback::~RFM9x_Dio0EventCallback()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_Dio0EventCallback::onExternalEventCallback()
{
  uint8_t const event_flags = _event_ctrl.getEventFlags();

  /* RX DONE **************************************************************************/
  if(interface::RFM9x_EventControl::isRxDoneEvent(event_flags))
  {
    _on_rx_done_callback.onRxDone();
    _event_ctrl.clearEventFlag(interface::EventFlag::RxDone);
  }
  /* TX DONE **************************************************************************/
  if(interface::RFM9x_EventControl::isTxDoneEvent(event_flags))
  {
    _on_tx_done_callback.onTxDone();
    _event_ctrl.clearEventFlag(interface::EventFlag::TxDone);
  }
  /* CAD DONE *************************************************************************/
  if(interface::RFM9x_EventControl::isCadDoneEvent(event_flags))
  {
    _on_cad_done_callback.onCadDone();
    _event_ctrl.clearEventFlag(interface::EventFlag::CadDone);
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
