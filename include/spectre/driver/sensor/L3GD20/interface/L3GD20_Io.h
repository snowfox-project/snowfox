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
 * TYPEDEF
 **************************************************************************************/

enum class Register : uint8_t
{
  WHO_AM_I      = 0x0F,
  CTRL_REG1     = 0x20,
  CTRL_REG2     = 0x21,
  CTRL_REG3     = 0x22,
  CTRL_REG4     = 0x23,
  CTRL_REG5     = 0x24,
  REFERENCE     = 0x25,
  OUT_TEMP      = 0x26,
  STATUS_REG    = 0x27,
  OUT_X_L       = 0x28,
  OUT_X_H       = 0x29,
  OUT_Y_L       = 0x2A,
  OUT_Y_H       = 0x2B,
  OUT_Z_L       = 0x2C,
  OUT_Z_H       = 0x2D,
  FIFO_CTRL_REG = 0x2E,
  FIFO_SRC_REG  = 0x2F,
  INT1_CFG      = 0x30,
  INT1_SRC      = 0x31,
  TSH_XH        = 0x32,
  TSH_XL        = 0x33,
  TSH_YH        = 0x34,
  TSH_YL        = 0x35,
  TSH_ZH        = 0x36,
  TSH_ZL        = 0x37,
  INT1_DURATION = 0x38
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class L3GD20_Io
{

public:

           L3GD20_Io() { }
  virtual ~L3GD20_Io() { }


  virtual bool readRegister (Register const reg, uint8_t       * data, uint16_t const num_bytes) = 0;
  virtual bool readRegister (Register const reg, uint8_t       * data                          ) = 0;
  virtual bool writeRegister(Register const reg, uint8_t const * data, uint16_t const num_bytes) = 0;
  virtual bool writeRegister(Register const reg, uint8_t const   data                          ) = 0;

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
