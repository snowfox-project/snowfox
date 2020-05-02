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

#ifndef INCLUDE_SNOWFOX_HAL_INTERFACE_CLOCK_CLOCK_CONFIGURATION_H_
#define INCLUDE_SNOWFOX_HAL_INTERFACE_CLOCK_CLOCK_CONFIGURATION_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class ClockConfiguration
{

public:

           ClockConfiguration() { }
  virtual ~ClockConfiguration() { }


  virtual bool setClockFreq(uint8_t const clk_id, uint32_t const clk_freq_hz) = 0;
  
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::interface*/

#endif /* INCLUDE_SNOWFOX_HAL_INTERFACE_CLOCK_CLOCK_CONFIGURATION_H_ */