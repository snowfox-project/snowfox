/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3MDL_INTERFACE_LIS3MDL_IO_INTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3MDL_INTERFACE_LIS3MDL_IO_INTERFACE_H_

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

namespace LIS3MDL
{

namespace interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Register : uint8_t
{
  WHO_AM_I    = 0x0F,
  CTRL_REG_1  = 0x20,
  CTRL_REG_2  = 0x21,
  CTRL_REG_3  = 0x22,
  CTRL_REG_4  = 0x23,
  CTRL_REG_5  = 0x24,
  STATUS_REG  = 0x27,
  OUT_X_L     = 0x28,
  OUT_X_H     = 0x29,
  OUT_Y_L     = 0x2A,
  OUT_Y_H     = 0x2B,
  OUT_Z_L     = 0x2C,
  OUT_Z_H     = 0x2D,
  TEMP_OUT_L  = 0x2E,
  TEMP_OUT_H  = 0x2F,
  INT_CFG     = 0x30,
  INT_SRC     = 0x31,
  INT_THS_L   = 0x32,
  INT_THS_H   = 0x33
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LIS3MDL_Io
{

public:

           LIS3MDL_Io() { }
  virtual ~LIS3MDL_Io() { }


  virtual bool readRegister (Register const reg, uint8_t       * data, uint16_t const num_bytes) = 0;
  virtual bool readRegister (Register const reg, uint8_t       * data                          ) = 0;
  virtual bool writeRegister(Register const reg, uint8_t const * data, uint16_t const num_bytes) = 0;
  virtual bool writeRegister(Register const reg, uint8_t const   data                          ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* LIS3MDL */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3MDL_INTERFACE_LIS3MDL_IO_INTERFACE_H_ */
