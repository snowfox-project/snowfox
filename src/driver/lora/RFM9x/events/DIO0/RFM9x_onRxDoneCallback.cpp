/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#include <snowfox/driver/lora/RFM9x/events/DIO0/RFM9x_onRxDoneCallback.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::lora::RFM9x
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RFM9x_onRxDoneCallback::RFM9x_onRxDoneCallback(os::interface::EventProducer & rx_done_event)
: _rx_done_event(rx_done_event)
{

}

RFM9x_onRxDoneCallback::~RFM9x_onRxDoneCallback()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_onRxDoneCallback::onRxDone()
{
  _rx_done_event.set();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::lora::RFM9x */
