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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_INTERFACE_BMP388_TYPES_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_INTERFACE_BMP388_TYPES_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace BMP388
{

namespace interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

union CalibrationData
{
  struct __attribute__((packed))
  {
    uint16_t T1;
    uint16_t T2;
    int8_t   T3;
    int16_t  P1;
    int16_t  P2;
    int8_t   P3;
    int8_t   P4;
    uint16_t P5;
    uint16_t P6;
    int8_t   P7;
    int8_t   P8;
    int16_t  P9;
    int8_t   P10;
    int8_t   P11;
  } coefficient;
  uint8_t buf[21];
};

typedef struct
{
  double T1;
  double T2;
  double T3;
  double P1;
  double P2;
  double P3;
  double P4;
  double P5;
  double P6;
  double P7;
  double P8;
  double P9;
  double P10;
  double P11;
} QuantizedCalibrationData;

union SensorData
{
  struct __attribute__((packed))
  {
    uint8_t pres_xlsb;
    uint8_t pres_lsb;
    uint8_t pres_msb;
    uint8_t temp_xlsb;
    uint8_t temp_lsb;
    uint8_t temp_msb;
  } reg;
  uint8_t buf[6];
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* BMP388 */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_INTERFACE_BMP388_TYPES_H_ */
