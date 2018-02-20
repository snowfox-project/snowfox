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

#ifndef INCLUDE_SPECTRE_DRIVER_CAN_INTERFACE_CANTRANSMITBUFFER_H_
#define INCLUDE_SPECTRE_DRIVER_CAN_INTERFACE_CANTRANSMITBUFFER_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <stdbool.h>

#include <spectre/hal/interface/can/CanFrame.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace can
{

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class CanTransmitBuffer
{

public:

           CanTransmitBuffer() { }
  virtual ~CanTransmitBuffer() { }


  virtual bool isFull            (                                        ) = 0;
  virtual void putData           (hal::interface::CanFrame const can_frame) = 0;
  virtual bool onTransmitComplete(                                        ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* can */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_CAN_INTERFACE_CANTRANSMITBUFFER_H_ */
