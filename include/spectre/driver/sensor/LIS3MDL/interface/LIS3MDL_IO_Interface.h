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

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  REG_WHO_AM_I    = 0x0F,
  REG_CTRL_REG_1  = 0x20,
  REG_CTRL_REG_2  = 0x21,
  REG_CTRL_REG_3  = 0x22,
  REG_CTRL_REG_4  = 0x23,
  REG_CTRL_REG_5  = 0x24,
  REG_STATUS_REG  = 0x27,
  REG_OUT_X_L     = 0x28,
  REG_OUT_X_H     = 0x29,
  REG_OUT_Y_L     = 0x2A,
  REG_OUT_Y_H     = 0x2B,
  REG_OUT_Z_L     = 0x2C,
  REG_OUT_Z_H     = 0x2D,
  REG_TEMP_OUT_L  = 0x2E,
  REG_TEMP_OUT_H  = 0x2F,
  REG_INT_CFG     = 0x30,
  REG_INT_SRC     = 0x31,
  REG_INT_THS_L   = 0x32,
  REG_INT_THS_H   = 0x33
} RegisterSelect;

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LIS3MDL_IO_Interface
{

public:

           LIS3MDL_IO_Interface() { }
  virtual ~LIS3MDL_IO_Interface() { }


  virtual bool readMultipleRegister (RegisterSelect const reg_sel, uint8_t       * data, uint16_t const num_bytes) = 0;
  virtual bool writeMultipleRegister(RegisterSelect const reg_sel, uint8_t const * data, uint16_t const num_bytes) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS3MDL */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3MDL_INTERFACE_LIS3MDL_IO_INTERFACE_H_ */
