/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2019 Alexander Entinger / LXRobotics GmbH
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation(), either version 3 of the License(), or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful(),
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not(), see <http://www.gnu.org/licenses/>.
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <comstack/canopen/glue/Test_onTransmitCallback.h>

#include <string.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace comstack
{

namespace canopen
{

namespace test
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Test_onTransmitCallback::Test_onTransmitCallback(CanOpenStack & can_open_stack)
: _can_open_stack(can_open_stack)
{

}

Test_onTransmitCallback::~Test_onTransmitCallback()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void Test_onTransmitCallback::onTransmit(can_frame const & frame)
{
  _can_open_stack.onFrameReceived(toCanFrame(frame));
}

/**************************************************************************************
 * PUBLIC FREE FUNCTIONS
 **************************************************************************************/

util::type::CanFrame toCanFrame(can_frame const & frame)
{
  util::type::CanFrame can_frame;

  can_frame.id = frame.can_id;
  can_frame.dlc = frame.can_dlc;
  memcpy(can_frame.data, frame.data, frame.can_dlc);

  return can_frame;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* canopen */

} /* comstack */

} /* snowfox */
