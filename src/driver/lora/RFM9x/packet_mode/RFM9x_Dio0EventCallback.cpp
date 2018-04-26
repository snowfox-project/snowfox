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

#include <spectre/driver/lora/RFM9x/packet_mode/RFM9x_Dio0EventCallback.h>

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
 * DEFINES
 **************************************************************************************/

#define RF9x_RX_TIMEOUT          (1<<7)
#define RF9x_RX_DONE             (1<<6)
#define RF9x_PAYLOAD_CRC_ERROR   (1<<5)
#define RF9x_VALID_HEADER        (1<<4)
#define RF9x_TX_DONE             (1<<3)
#define RF9x_CAD_DONE            (1<<2)
#define RF9x_FHSS_CHANGE_CHANNEL (1<<1)
#define RF9x_CAD_DETECTED        (1<<0)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RFM9x_Dio0EventCallback::RFM9x_Dio0EventCallback(interface::RFM9x_InterruptRequestControl & int_req_ctrl,
                                                 interface::RFM9x_onPacketSentCallback    & on_packet_sent_callback,
                                                 interface::RFM9x_onPayloadReadyCallback  & on_payload_ready_callback)
: _int_req_ctrl             (int_req_ctrl             ),
  _on_packet_sent_callback  (on_packet_sent_callback  ),
  _on_payload_ready_callback(on_payload_ready_callback)
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
  uint8_t irq_req_flags = 0;

  _int_req_ctrl.getIntReqFlags(&irq_req_flags);

  if(isRxTimeout(irq_req_flags))
  {
    _int_req_ctrl.clearIntReqFlag(interface::InterruptRequest::RxTimeout);
  }
  if(isRxDone(irq_req_flags))
  {
    _int_req_ctrl.clearIntReqFlag(interface::InterruptRequest::RxDone);
  }
  if(isPayloadCrcError(irq_req_flags))
  {
    _int_req_ctrl.clearIntReqFlag(interface::InterruptRequest::PayloadCrcError);
  }
  if(isValidHeader(irq_req_flags))
  {
    _int_req_ctrl.clearIntReqFlag(interface::InterruptRequest::ValidHeader);
  }
  if(isTxDone(irq_req_flags))
  {
    _int_req_ctrl.clearIntReqFlag(interface::InterruptRequest::TxDone);
  }
  if(isCadDone(irq_req_flags))
  {
    _int_req_ctrl.clearIntReqFlag(interface::InterruptRequest::CadDone);
  }
  if(isFhssChangeChannel(irq_req_flags))
  {
    _int_req_ctrl.clearIntReqFlag(interface::InterruptRequest::FhssChangeChannel);
  }
  if(isCadDetected(irq_req_flags))
  {
    _int_req_ctrl.clearIntReqFlag(interface::InterruptRequest::CadDetected);
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

bool RFM9x_Dio0EventCallback::isRxTimeout(uint8_t const irq_flags)
{
  return (irq_flags & RF9x_RX_TIMEOUT) == RF9x_RX_TIMEOUT;
}

bool RFM9x_Dio0EventCallback::isRxDone(uint8_t const irq_flags)
{
  return (irq_flags & RF9x_RX_DONE) == RF9x_RX_DONE;
}

bool RFM9x_Dio0EventCallback::isPayloadCrcError(uint8_t const irq_flags)
{
  return (irq_flags & RF9x_PAYLOAD_CRC_ERROR) == RF9x_PAYLOAD_CRC_ERROR;
}

bool RFM9x_Dio0EventCallback::isValidHeader(uint8_t const irq_flags)
{
  return (irq_flags & RF9x_VALID_HEADER) == RF9x_VALID_HEADER;
}

bool RFM9x_Dio0EventCallback::isTxDone(uint8_t const irq_flags)
{
  return (irq_flags & RF9x_TX_DONE) == RF9x_TX_DONE;
}

bool RFM9x_Dio0EventCallback::isCadDone(uint8_t const irq_flags)
{
  return (irq_flags & RF9x_CAD_DONE) == RF9x_CAD_DONE;
}

bool RFM9x_Dio0EventCallback::isFhssChangeChannel(uint8_t const irq_flags)
{
  return (irq_flags & RF9x_FHSS_CHANGE_CHANNEL) == RF9x_FHSS_CHANGE_CHANNEL;
}

bool RFM9x_Dio0EventCallback::isCadDetected(uint8_t const irq_flags)
{
  return (irq_flags & RF9x_CAD_DETECTED) == RF9x_CAD_DETECTED;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
