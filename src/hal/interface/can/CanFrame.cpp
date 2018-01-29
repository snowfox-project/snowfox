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

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/interface/can/CanFrame.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace interface
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

#define CAN_EFF_BITMASK (0x80000000U)
#define CAN_RTR_BITMASK (0x40000000U)
#define CAN_ERR_BITMASK (0x20000000U)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

CanFrame::CanFrame()
: _id(0), _dlc(0)
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool CanFrame::isExtendedId() const
{
  bool const is_extended_id = (_id & CAN_EFF_BITMASK) == CAN_EFF_BITMASK;
  return is_extended_id;
}

bool CanFrame::isRTR() const
{
  bool const is_remote_transmission_request = (_id & CAN_RTR_BITMASK) == CAN_RTR_BITMASK;
  return is_remote_transmission_request;
}

bool CanFrame::isErrorFrame() const
{
  bool const is_error_frame = (_id & CAN_ERR_BITMASK) == CAN_ERR_BITMASK;
  return is_error_frame;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* hal */

} /* spectre */
