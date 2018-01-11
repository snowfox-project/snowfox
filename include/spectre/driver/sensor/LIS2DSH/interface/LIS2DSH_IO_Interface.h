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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_LIS2DSH_INTERFACE_LIS2DSH_IO_INTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_LIS2DSH_INTERFACE_LIS2DSH_IO_INTERFACE_H_

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

namespace LIS2DSH
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  REG_STATUS_REG_AUX  = 0x07,

  REG_OUT_TEMP_L      = 0x0C,
  REG_OUT_TEMP_H      = 0x0D,

  REG_INT_COUNTER_REG = 0x0E,

  REG_WHO_AM_I        = 0x0F,

  REG_TEMP_CFG_REG    = 0x1F,
  REG_CTRL_REG1       = 0x20,
  REG_CTRL_REG2       = 0x21,
  REG_CTRL_REG3       = 0x22,
  REG_CTRL_REG4       = 0x23,
  REG_CTRL_REG5       = 0x24,
  REG_CTRL_REG6       = 0x25,

  REG_STATUS_REG      = 0x27,

  REG_OUT_X_L         = 0x28,
  REG_OUT_X_H         = 0x29,
  REG_OUT_Y_L         = 0x2A,
  REG_OUT_Y_H         = 0x2B,
  REG_OUT_Z_L         = 0x2C,
  REG_OUT_Z_H         = 0x2D,

  REG_FIFO_CTRL_REG   = 0x2E,
  REG_FIFO_SRC_REG    = 0x2F,

  REG_INT1_CFG        = 0x30,
  REG_INT1_SOURCE     = 0x31,
  REG_INT1_THS        = 0x32,
  REG_INT1_DURATION   = 0x33,

  REG_INT2_CFG        = 0x34,
  REG_INT2_SOURCE     = 0x35,
  REG_INT2_THS        = 0x36,
  REG_INT2_DURATION   = 0x37,

  REG_CLICK_CFG       = 0x38,
  REG_CLICK_SRC       = 0x39,
  REG_CLICK_THS       = 0x3A,

  REG_TIME_LIMIT      = 0x3B,
  REG_TIME_LATENCY    = 0x3C,
  REG_TIME_WINDOW     = 0x3D,

  REG_ACT_THS         = 0x3E,
  REG_ACT_DUR         = 0x3F
} RegisterSelect;

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LIS2DSH_IO_Interface
{

public:

           LIS2DSH_IO_Interface() { }
  virtual ~LIS2DSH_IO_Interface() { }


  virtual bool readMultipleRegister (RegisterSelect const reg_sel, uint8_t       * data, uint16_t const num_bytes) = 0;
  virtual bool writeMultipleRegister(RegisterSelect const reg_sel, uint8_t const * data, uint16_t const num_bytes) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS2DSH */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_LIS2DSH_INTERFACE_LIS2DSH_IO_INTERFACE_H_ */
