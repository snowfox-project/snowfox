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

#ifndef INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_CALLBACKHANDLER_H_
#define INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_CALLBACKHANDLER_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/interface/extint/ExternalInterruptCallback.h>

#include <spectre/driver/lora/RFM9x/interface/packet_mode/RFM9x_onPacketSentCallback.h>
#include <spectre/driver/lora/RFM9x/interface/packet_mode/RFM9x_onPayloadReadyCallback.h>

#include <spectre/driver/lora/RFM9x/interface/RFM9x_InterruptControl.h>

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
 * CLASS DECLARATION
 **************************************************************************************/

/* For information in DIO mapping in LoRa mode check out
 * Table 63. There are three events which can be mapped
 * on DIO0: RxDone, TxDone, CadDone
 */

class RFM9x_Dio0EventCallback :  public hal::interface::ExternalInterruptCallback
{

public:

           RFM9x_Dio0EventCallback(interface::RFM9x_InterruptControl       & int_ctrl,
                                   interface::RFM9x_onPacketSentCallback   & on_packet_sent_callback,
                                   interface::RFM9x_onPayloadReadyCallback & on_payload_ready_callback);
  virtual ~RFM9x_Dio0EventCallback();


  virtual void onExternalEventCallback() override;


private:

  interface::RFM9x_InterruptControl       & _int_ctrl;
  interface::RFM9x_onPacketSentCallback   & _on_packet_sent_callback;
  interface::RFM9x_onPayloadReadyCallback & _on_payload_ready_callback;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_CALLBACKHANDLER_H_ */
