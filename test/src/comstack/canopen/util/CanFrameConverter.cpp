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

#include <test/comstack/canopen/util/CanFrameConverter.h>

#include <string.h>

#include <algorithm>

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
 * STATIC ASSERTIONS
 **************************************************************************************/

static_assert(CAN_MAX_DLEN == util::type::CAN_MAX_DATA_LEN, "linux/can.h CAN max. data payload length must be equal to snowfox::util::type::CanFrame max. data payload length");

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

can_frame toCanFrame(util::type::CanFrame const & frame)
{
  can_frame f;

  f.can_id = frame.id;
  f.can_dlc = frame.dlc;
  memcpy(f.data, frame.data, std::min<uint8_t>(frame.dlc, CAN_MAX_DLEN));

  return f;
}

util::type::CanFrame toCanFrame(can_frame const & frame)
{
  util::type::CanFrame can_frame;

  can_frame.id = frame.can_id;
  can_frame.dlc = frame.can_dlc;
  memcpy(can_frame.data, frame.data, std::min<uint8_t>(frame.can_dlc, util::type::CAN_MAX_DATA_LEN));

  return can_frame;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */

} /* canopen */

} /* comstack */

} /* snowfox */
