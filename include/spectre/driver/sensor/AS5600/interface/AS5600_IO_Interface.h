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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_AS5600_INTERFACE_AS5600_IO_INTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_AS5600_INTERFACE_AS5600_IO_INTERFACE_H_

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

namespace AS5600
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  REG_ZMCO                = 0x00,
  REG_ZPOS_HIGH_BYTE      = 0x01,
  REG_ZPOS_LOW_BYTE       = 0x02,
  REG_MPOS_HIGH_BYTE      = 0x03,
  REG_MPOS_LOW_BYTE       = 0x04,
  REG_MANG_HIGH_BYTE      = 0x05,
  REG_MANG_LOW_BYTE       = 0x06,
  REG_CONF_HIGH_BYTE      = 0x07,
  REG_CONF_LOW_BYTE       = 0x08,
  REG_RAW_ANGLE_HIGH_BYTE = 0x0C,
  REG_RAW_ANGLE_LOW_BYTE  = 0x0D,
  REG_ANGLE_HIGH_BYTE     = 0x0E,
  REG_ANGLE_LOW_BYTE      = 0x0F,
  REG_STATUS              = 0x0B,
  REG_AGC                 = 0x1A,
  REG_MAGNITUDE_HIGH_BYTE = 0x1B,
  REG_MAGNITUDE_LOW_BYTE  = 0x1C
} RegisterSelect;

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AS5600_IO_Interface
{

public:

           AS5600_IO_Interface() { }
  virtual ~AS5600_IO_Interface() { }


  virtual bool readMultipleRegister (RegisterSelect const reg_sel, uint8_t       * data, uint16_t const num_bytes) = 0;
  virtual bool writeMultipleRegister(RegisterSelect const reg_sel, uint8_t const * data, uint16_t const num_bytes) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AS5600 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_AS5600_INTERFACE_AS5600_IO_INTERFACE_H_ */
