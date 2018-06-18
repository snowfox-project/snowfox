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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_INA220_INTERFACE_INA220_IO_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_INA220_INTERFACE_INA220_IO_H_

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

namespace INA220
{

namespace interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Register: uint8_t
{
  CONFIG      = 0x00,
  V_SHUNT     = 0x01,
  V_BUS       = 0x02,
  POWER       = 0x03,
  CURRENT     = 0x04,
  CALIBRATION = 0x05
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class INA220_Io
{

public:

           INA220_Io() { }
  virtual ~INA220_Io() { }


  virtual bool readRegister (Register const reg, uint16_t       * data) = 0;
  virtual bool writeRegister(Register const reg, uint16_t const   data) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* INA220 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_INA220_INTERFACE_INA220_IO_H_ */
