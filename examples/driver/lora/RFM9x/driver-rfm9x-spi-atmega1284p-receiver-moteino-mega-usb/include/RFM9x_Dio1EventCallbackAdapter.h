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

#ifndef EXAMPLES_DRIVER_LORA_RFM9X_DRIVER_RFM9X_SPI_ATMEGA1284P_TRANSMITTER_MOTEINO_MEGA_USB_RFM9X_DIO1EVENTCALLBACKADAPTER_H_
#define EXAMPLES_DRIVER_LORA_RFM9X_DRIVER_RFM9X_SPI_ATMEGA1284P_TRANSMITTER_MOTEINO_MEGA_USB_RFM9X_DIO1EVENTCALLBACKADAPTER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/extint/ExternalInterruptCallback.h>

#include <spectre/hal/interface/gpio/DigitalInPin.h>
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
 * CLASS DECLARATION
 **************************************************************************************/

class RFM9x_Dio1EventCallbackAdapter : public hal::interface::ExternalInterruptCallback
{

public:

           RFM9x_Dio1EventCallbackAdapter(RFM9x_Dio1EventCallback      & rfm9x_dio1_event_callback,
                                          hal::interface::DigitalInPin & rfm9x_dio1_int_pin);
  virtual ~RFM9x_Dio1EventCallbackAdapter();


  virtual void onExternalEventCallback() override;

private:

  RFM9x_Dio1EventCallback      & _rfm9x_dio1_event_callback;
  hal::interface::DigitalInPin & _rfm9x_dio1_int_pin;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */

#endif /* EXAMPLES_DRIVER_LORA_RFM9X_DRIVER_RFM9X_SPI_ATMEGA1284P_TRANSMITTER_MOTEINO_MEGA_USB_RFM9X_DIO1EVENTCALLBACKADAPTER_H_ */
