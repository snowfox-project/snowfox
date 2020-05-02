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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_INTERFACE_AS5600_INTERFACE_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_INTERFACE_AS5600_INTERFACE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensor::AD7151::interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AS5600_Interface
{

public:

           AS5600_Interface() { }
  virtual ~AS5600_Interface() { }


  virtual bool readAngle    (uint16_t * angle    ) = 0;
  virtual bool readAngleRaw (uint16_t * angle_raw) = 0;

  virtual bool readStatus   (uint8_t  * status   ) = 0;
  virtual bool readAGC      (uint8_t  * agc      ) = 0;
  virtual bool readMagnitude(uint16_t * mag      ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensor::AD7151::interface */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_INTERFACE_AS5600_INTERFACE_H_ */
