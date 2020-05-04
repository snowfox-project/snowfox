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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS2DSH_INTERFACE_LIS2DSH_IO_INTERFACE_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS2DSH_INTERFACE_LIS2DSH_IO_INTERFACE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensor::LIS2DSH::interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Register : uint8_t
{
  STATUS_REG_AUX  = 0x07,

  OUT_TEMP_L      = 0x0C,
  OUT_TEMP_H      = 0x0D,

  INT_COUNTER_REG = 0x0E,

  WHO_AM_I        = 0x0F,

  TEMP_CFG_REG    = 0x1F,
  CTRL_REG1       = 0x20,
  CTRL_REG2       = 0x21,
  CTRL_REG3       = 0x22,
  CTRL_REG4       = 0x23,
  CTRL_REG5       = 0x24,
  CTRL_REG6       = 0x25,

  STATUS_REG      = 0x27,

  OUT_X_L         = 0x28,
  OUT_X_H         = 0x29,
  OUT_Y_L         = 0x2A,
  OUT_Y_H         = 0x2B,
  OUT_Z_L         = 0x2C,
  OUT_Z_H         = 0x2D,

  FIFO_CTRL_REG   = 0x2E,
  FIFO_SRC_REG    = 0x2F,

  INT1_CFG        = 0x30,
  INT1_SOURCE     = 0x31,
  INT1_THS        = 0x32,
  INT1_DURATION   = 0x33,

  INT2_CFG        = 0x34,
  INT2_SOURCE     = 0x35,
  INT2_THS        = 0x36,
  INT2_DURATION   = 0x37,

  CLICK_CFG       = 0x38,
  CLICK_SRC       = 0x39,
  CLICK_THS       = 0x3A,

  TIME_LIMIT      = 0x3B,
  TIME_LATENCY    = 0x3C,
  TIME_WINDOW     = 0x3D,

  ACT_THS         = 0x3E,
  ACT_DUR         = 0x3F
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LIS2DSH_Io
{

public:

           LIS2DSH_Io() { }
  virtual ~LIS2DSH_Io() { }


  virtual bool readRegister (Register const reg, uint8_t       * data, uint16_t const num_bytes) = 0;
  virtual bool readRegister (Register const reg, uint8_t       * data                          ) = 0;
  virtual bool writeRegister(Register const reg, uint8_t const * data, uint16_t const num_bytes) = 0;
  virtual bool writeRegister(Register const reg, uint8_t const   data                          ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensor::LIS2DSH::interface */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS2DSH_INTERFACE_LIS2DSH_IO_INTERFACE_H_ */
