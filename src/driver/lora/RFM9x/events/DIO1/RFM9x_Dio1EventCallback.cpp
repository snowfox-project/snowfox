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

#include <spectre/driver/lora/RFM9x/events/DIO1/RFM9x_Dio1EventCallback.h>

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

RFM9x_Dio1EventCallback::RFM9x_Dio1EventCallback(interface::RFM9x_InterruptControl            & int_ctrl,
                                                 interface::RFM9x_onRxTimeoutCallback         & on_rx_timeout_callback,
                                                 interface::RFM9x_onFhssChangeChannelCallback & on_fhss_change_channel_callback,
                                                 interface::RFM9x_onCadDetectedCallback       & on_cad_detected_callback)
: _int_ctrl                       (int_ctrl                       ),
  _on_rx_timeout_callback         (on_rx_timeout_callback         ),
  _on_fhss_change_channel_callback(on_fhss_change_channel_callback),
  _on_cad_detected_callback       (on_cad_detected_callback       )
{

}

RFM9x_Dio1EventCallback::~RFM9x_Dio1EventCallback()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_Dio1EventCallback::onExternalEventCallback()
{
  uint8_t irq_req_flags = 0;

  _int_ctrl.getIntReqFlags(&irq_req_flags);

  /* RX TIMEOUT ***********************************************************************/
  if(interface::RFM9x_InterruptControl::isRxTimeout(irq_req_flags))
  {
    _on_rx_timeout_callback.onRxTimeout();
    _int_ctrl.clearIntReqFlag(interface::InterruptRequest::RxTimeout);
  }
  /* FHSS CHANGE CHANNEL **************************************************************/
  if(interface::RFM9x_InterruptControl::isFhssChangeChannel(irq_req_flags))
  {
    _on_fhss_change_channel_callback.onFhssChangeChannel();
    _int_ctrl.clearIntReqFlag(interface::InterruptRequest::FhssChangeChannel);
  }
  /* CAD DETECTED *********************************************************************/
  if(interface::RFM9x_InterruptControl::isCadDetected(irq_req_flags))
  {
    _on_cad_detected_callback.onCadDetected();
    _int_ctrl.clearIntReqFlag(interface::InterruptRequest::CadDetected);
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
