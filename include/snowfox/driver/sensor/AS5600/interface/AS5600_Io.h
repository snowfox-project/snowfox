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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_INTERFACE_AS5600_IO_INTERFACE_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_INTERFACE_AS5600_IO_INTERFACE_H_

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
 * TYPEDEF
 **************************************************************************************/

enum class Register : uint8_t
{
  ZMCO                = 0x00,
  ZPOS_HIGH_BYTE      = 0x01,
  ZPOS_LOW_BYTE       = 0x02,
  MPOS_HIGH_BYTE      = 0x03,
  MPOS_LOW_BYTE       = 0x04,
  MANG_HIGH_BYTE      = 0x05,
  MANG_LOW_BYTE       = 0x06,
  CONF_HIGH_BYTE      = 0x07,
  CONF_LOW_BYTE       = 0x08,
  RAW_ANGLE_HIGH_BYTE = 0x0C,
  RAW_ANGLE_LOW_BYTE  = 0x0D,
  ANGLE_HIGH_BYTE     = 0x0E,
  ANGLE_LOW_BYTE      = 0x0F,
  STATUS              = 0x0B,
  AGC                 = 0x1A,
  MAGNITUDE_HIGH_BYTE = 0x1B,
  MAGNITUDE_LOW_BYTE  = 0x1C
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AS5600_Io
{

public:

           AS5600_Io() { }
  virtual ~AS5600_Io() { }


  virtual bool readRegister (Register const reg, uint8_t       * data, uint16_t const num_bytes) = 0;
  virtual bool readRegister (Register const reg, uint8_t       * data                          ) = 0;
  virtual bool writeRegister(Register const reg, uint8_t const * data, uint16_t const num_bytes) = 0;
  virtual bool writeRegister(Register const reg, uint8_t const   data                          ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensor::AD7151 */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_INTERFACE_AS5600_IO_INTERFACE_H_ */
