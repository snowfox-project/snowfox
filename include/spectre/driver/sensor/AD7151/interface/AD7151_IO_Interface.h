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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_AD7151_INTERFACE_AD7151_IO_INTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_AD7151_INTERFACE_AD7151_IO_INTERFACE_H_

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

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  REG_STATUS                      = 0x00,
  REG_DATA_HIGH                   = 0x01,
  REG_DATA_LOW                    = 0x02,
  REG_AVERAGE_HIGH                = 0x05,
  REG_AVERAGE_LOW                 = 0x06,
  REG_SENSITIVITY_THRESHOLD_HIGH  = 0x09,
  REG_SENSITIVITY_THRESHOLD_LOW   = 0x0A,
  REG_SETUP                       = 0x0B,
  REG_CONFIGURATION               = 0x0F,
  REG_POWER_DOWN_TIMER            = 0x10,
  REG_CAPDAC                      = 0x11,
  REG_SERIAL_NUMBER_3             = 0x13,
  REG_SERIAL_NUMBER_2             = 0x14,
  REG_SERIAL_NUMBER_1             = 0x15,
  REG_SERIAL_NUMBER_0             = 0x16,
  REG_CHIP_ID                     = 0x17
} RegisterSelect;

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AD7151_IO_Interface
{

public:

           AD7151_IO_Interface() { }
  virtual ~AD7151_IO_Interface() { }


  virtual bool writeMultipleRegister(RegisterSelect const reg_sel, uint8_t const  * data, uint16_t const num_bytes) = 0;
  virtual bool readMultipleRegister (RegisterSelect const reg_sel, uint8_t        * data, uint16_t const num_bytes) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AD7151 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_AD7151_INTERFACE_AD7151_IO_INTERFACE_H_ */
