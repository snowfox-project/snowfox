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

#include <RFM9x_Dio1EventCallbackAdapter.h>

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

RFM9x_Dio1EventCallbackAdapter::RFM9x_Dio1EventCallbackAdapter(RFM9x_Dio1EventCallback      & rfm9x_dio1_event_callback,
                                                               hal::interface::DigitalInPin & rfm9x_dio1_int_pin)
: _rfm9x_dio1_event_callback(rfm9x_dio1_event_callback),
  _rfm9x_dio1_int_pin       (rfm9x_dio1_int_pin       )
{

}

RFM9x_Dio1EventCallbackAdapter::~RFM9x_Dio1EventCallbackAdapter()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_Dio1EventCallbackAdapter::onExternalEventCallback()
{
  /* Trigger on rising edge only - if we had an event and the
   * input is high then we have had a rising edge event.
   */
  if(_rfm9x_dio1_int_pin.isSet())
  {
    _rfm9x_dio1_event_callback.onExternalEventCallback();
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
