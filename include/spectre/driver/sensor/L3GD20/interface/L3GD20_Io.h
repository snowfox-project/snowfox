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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_L3GD20_INTERFACE_L3GD20_IO_INTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_L3GD20_INTERFACE_L3GD20_IO_INTERFACE_H_

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

namespace L3GD20
{

namespace interface
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  REG_WHO_AM_I      = 0x0F,
  REG_CTRL_REG1     = 0x20,
  REG_CTRL_REG2     = 0x21,
  REG_CTRL_REG3     = 0x22,
  REG_CTRL_REG4     = 0x23,
  REG_CTRL_REG5     = 0x24,
  REG_REFERENCE     = 0x25,
  REG_OUT_TEMP      = 0x26,
  REG_STATUS_REG    = 0x27,
  REG_OUT_X_L       = 0x28,
  REG_OUT_X_H       = 0x29,
  REG_OUT_Y_L       = 0x2A,
  REG_OUT_Y_H       = 0x2B,
  REG_OUT_Z_L       = 0x2C,
  REG_OUT_Z_H       = 0x2D,
  REG_FIFO_CTRL_REG = 0x2E,
  REG_FIFO_SRC_REG  = 0x2F,
  REG_INT1_CFG      = 0x30,
  REG_INT1_SRC      = 0x31,
  REG_TSH_XH        = 0x32,
  REG_TSH_XL        = 0x33,
  REG_TSH_YH        = 0x34,
  REG_TSH_YL        = 0x35,
  REG_TSH_ZH        = 0x36,
  REG_TSH_ZL        = 0x37,
  REG_INT1_DURATION = 0x38
} RegisterSelect;

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class L3GD20_Io
{

public:

           L3GD20_Io() { }
  virtual ~L3GD20_Io() { }


  virtual bool readMultipleRegister (RegisterSelect const reg_sel, uint8_t       * data, uint16_t const num_bytes) = 0;
  virtual bool writeMultipleRegister(RegisterSelect const reg_sel, uint8_t const * data, uint16_t const num_bytes) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* L3GD20 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_L3GD20_INTERFACE_L3GD20_IO_INTERFACE_H_ */
