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

#ifndef INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_RFM9X_CALLBACKHANDLER_H_
#define INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_RFM9X_CALLBACKHANDLER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/interface/extint/ExternalInterruptCallback.h>

#include <snowfox/driver/lora/RFM9x/interface/events/DIO0/RFM9x_onTxDoneCallback.h>
#include <snowfox/driver/lora/RFM9x/interface/events/DIO0/RFM9x_onRxDoneCallback.h>
#include <snowfox/driver/lora/RFM9x/interface/events/DIO0/RFM9x_onCadDoneCallback.h>

#include <snowfox/driver/lora/RFM9x/interface/control/RFM9x_EventControl.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
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

class RFM9x_Dio0EventCallback : public hal::interface::ExternalInterruptCallback
{

public:

           RFM9x_Dio0EventCallback(interface::RFM9x_EventControl      & event_ctrl,
                                   interface::RFM9x_onTxDoneCallback  & on_tx_done_callback,
                                   interface::RFM9x_onRxDoneCallback  & on_rx_done_callback,
                                   interface::RFM9x_onCadDoneCallback & on_cad_done_callback);
  virtual ~RFM9x_Dio0EventCallback();


  virtual void onExternalInterrupt() override;


private:

  interface::RFM9x_EventControl      & _event_ctrl;
  interface::RFM9x_onTxDoneCallback  & _on_tx_done_callback;
  interface::RFM9x_onRxDoneCallback  & _on_rx_done_callback;
  interface::RFM9x_onCadDoneCallback & _on_cad_done_callback;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_RFM9X_CALLBACKHANDLER_H_ */
