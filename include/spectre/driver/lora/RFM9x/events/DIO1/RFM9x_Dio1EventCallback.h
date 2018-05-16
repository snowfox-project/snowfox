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

#ifndef INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_DIO1_RFM9X_DIO1EVENTCALLBACK_H_
#define INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_DIO1_RFM9X_DIO1EVENTCALLBACK_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/interface/extint/ExternalInterruptCallback.h>

#include <spectre/driver/lora/RFM9x/interface/events/DIO1/RFM9x_onRxTimeoutCallback.h>
#include <spectre/driver/lora/RFM9x/interface/events/DIO1/RFM9x_onCadDetectedCallback.h>
#include <spectre/driver/lora/RFM9x/interface/events/DIO1/RFM9x_onFhssChangeChannelCallback.h>

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
 * on DIO1: RxTimeout, FhssChangeChannel, CadDetected
 */

class RFM9x_Dio1EventCallback :  public hal::interface::ExternalInterruptCallback
{

public:

           RFM9x_Dio1EventCallback(interface::RFM9x_InterruptControl            & int_ctrl,
                                   interface::RFM9x_onRxTimeoutCallback         & on_rx_timeout_callback,
                                   interface::RFM9x_onFhssChangeChannelCallback & on_fhss_change_channel_callback,
                                   interface::RFM9x_onCadDetectedCallback       & on_cad_detected_callback);
  virtual ~RFM9x_Dio1EventCallback();


  virtual void onExternalEventCallback() override;


private:

  interface::RFM9x_InterruptControl            & _int_ctrl;
  interface::RFM9x_onRxTimeoutCallback         & _on_rx_timeout_callback;
  interface::RFM9x_onFhssChangeChannelCallback & _on_fhss_change_channel_callback;
  interface::RFM9x_onCadDetectedCallback       & _on_cad_detected_callback;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_DIO1_RFM9X_DIO1EVENTCALLBACK_H_ */
