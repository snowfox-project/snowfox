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

#include <snowfox/util/type/CanFrame.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::util::type
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr CAN_ID_BITMASK          = 0x000007FF;
static uint32_t constexpr CAN_ID_EXTENDED_BITMASK = 0x1FFFFFFF;

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool isExtendedId(util::type::CanFrame const & frame)
{
  bool const is_extended_id = (frame.id & CAN_EFF_BITMASK) == CAN_EFF_BITMASK;
  return is_extended_id;
}

bool isRTR(util::type::CanFrame const & frame)
{
  bool const is_remote_transmission_request = (frame.id & CAN_RTR_BITMASK) == CAN_RTR_BITMASK;
  return is_remote_transmission_request;
}

bool isErrorFrame(util::type::CanFrame const & frame)
{
  bool const is_error_frame = (frame.id & CAN_ERR_BITMASK) == CAN_ERR_BITMASK;
  return is_error_frame;
}

uint32_t toCanId(util::type::CanFrame const & frame)
{
  return (frame.id & CAN_ID_BITMASK);
}

uint32_t toCanIdExtended(util::type::CanFrame const & frame)
{
  return (frame.id & CAN_ID_EXTENDED_BITMASK);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* namespace snowfox::util::type */
