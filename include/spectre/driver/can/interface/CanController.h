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

#ifndef INCLUDE_SPECTRE_DRIVER_CAN_INTERFACE_CANCONTROLLER_H_
#define INCLUDE_SPECTRE_DRIVER_CAN_INTERFACE_CANCONTROLLER_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/interface/Driver.h>

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
 * TYPEDEFS
 **************************************************************************************/

enum class CanBitRate
{
  BR_1MBPS,
  BR_500kBPS,
  BR_250kBPS,
  BR_125kBPS
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class CanController
{

public:

           CanController() { }
  virtual ~CanController() { }


  virtual void setCanBitRate(CanBitRate const can_bit_rate) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* can */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_CAN_INTERFACE_CANCONTROLLER_H_ */
