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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_AD7151_INTERFACE_AD7151_IO_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_AD7151_INTERFACE_AD7151_IO_H_

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

namespace AD7151
{

namespace interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Register : uint8_t
{
  STATUS                      = 0x00,
  DATA_HIGH                   = 0x01,
  DATA_LOW                    = 0x02,
  AVERAGE_HIGH                = 0x05,
  AVERAGE_LOW                 = 0x06,
  SENSITIVITY_THRESHOLD_HIGH  = 0x09,
  SENSITIVITY_THRESHOLD_LOW   = 0x0A,
  SETUP                       = 0x0B,
  CONFIGURATION               = 0x0F,
  POWER_DOWN_TIMER            = 0x10,
  CAPDAC                      = 0x11,
  SERIAL_NUMBER_3             = 0x13,
  SERIAL_NUMBER_2             = 0x14,
  SERIAL_NUMBER_1             = 0x15,
  SERIAL_NUMBER_0             = 0x16,
  CHIP_ID                     = 0x17
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AD7151_Io
{

public:

           AD7151_Io() { }
  virtual ~AD7151_Io() { }


  virtual bool readRegister (Register const reg, uint8_t        * data, uint16_t const num_bytes) = 0;
  virtual bool readRegister (Register const reg, uint8_t        * data                          ) = 0;
  virtual bool writeRegister(Register const reg, uint8_t const  * data, uint16_t const num_bytes) = 0;
  virtual bool writeRegister(Register const reg, uint8_t const    data                          ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

}

} /* AD7151 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_AD7151_INTERFACE_AD7151_IO_H_ */
