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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_TPA81_INTERFACE_TPA81_INTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_TPA81_INTERFACE_TPA81_INTERFACE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace TPA81
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef struct
{
  uint8_t pixel_1;
  uint8_t pixel_2;
  uint8_t pixel_3;
  uint8_t pixel_4;
  uint8_t pixel_5;
  uint8_t pixel_6;
  uint8_t pixel_7;
  uint8_t pixel_8;
} ThermophileData;

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class TPA81_Interface
{

public:

           TPA81_Interface() { }
  virtual ~TPA81_Interface() { }

  virtual bool readSoftwareRevision   (uint8_t         * software_revision  ) = 0;
  virtual bool readAmbientTemperature (uint8_t         * ambient_temperature) = 0;
  virtual bool readThermophileArray   (ThermophileData * thermo_data        ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* TPA81 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_TPA81_INTERFACE_TPA81_INTERFACE_H_ */
