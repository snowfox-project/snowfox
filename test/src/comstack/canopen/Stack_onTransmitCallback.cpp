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

#include <comstack/canopen/Stack_onTransmitCallback.h>

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

Stack_onTransmitCallback::Stack_onTransmitCallback(/* Reference to test library test manager class */)
{

}

Stack_onTransmitCallback::~Stack_onTransmitCallback()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void Stack_onTransmitCallback::onTransmit(util::type::CanFrame const & /* frame */)
{
  /* TODO */
}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

can_frame toCanFrame(util::type::CanFrame const & frame)
{
  can_frame f;

  f.can_id = frame.id;
  f.can_dlc = frame.dlc;
  memcpy(f.data, frame.data, frame.dlc);

  return f;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* canopen */

} /* comstack */

} /* snowfox */
