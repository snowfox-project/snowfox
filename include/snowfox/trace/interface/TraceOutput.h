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

#ifndef INCLUDE_SNOWFOX_DRIVER_HAPTIC_DRV2605_DEBUGINTERFACE_H_
#define INCLUDE_SNOWFOX_DRIVER_HAPTIC_DRV2605_DEBUGINTERFACE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::trace::interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class TraceOutput
{

public:

           TraceOutput() { }
  virtual ~TraceOutput() { }


  virtual void write(uint8_t const * buf, uint16_t const length) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::trace::interface */

#endif /* INCLUDE_SNOWFOX_DRIVER_HAPTIC_DRV2605_DEBUGINTERFACE_H_ */
