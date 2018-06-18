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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3DSH_INTERFACE_LIS3DSH_IO_INTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3DSH_INTERFACE_LIS3DSH_IO_INTERFACE_H_

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

namespace LIS3DSH
{

namespace interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Register : uint8_t
{
  INFO_1      = 0x0D,
  INFO_2      = 0x0E,
  WHO_AM_I    = 0x0F,
  CTRL_REG_1  = 0x21,
  CTRL_REG_2  = 0x22,
  CTRL_REG_3  = 0x23,
  CTRL_REG_4  = 0x20,
  CTRL_REG_5  = 0x24,
  CTRL_REG_6  = 0x25,
  STATUS      = 0x27,
  OUT_T       = 0x0C,
  OFF_X       = 0x10,
  OFF_Y       = 0x11,
  OFF_Z       = 0x12,
  CS_X        = 0x13,
  CS_Y        = 0x14,
  CS_Z        = 0x15,
  LC_L        = 0x16,
  LC_H        = 0x17,
  STAT        = 0x18,
  PEAK1       = 0x19,
  PEAK2       = 0x1A,
  VFC_1       = 0x1B,
  VFC_2       = 0x1C,
  VFC_3       = 0x1D,
  VFC_4       = 0x1E,
  THRS3       = 0x1F,
  OUT_X_L     = 0x28,
  OUT_X_H     = 0x29,
  OUT_Y_L     = 0x2A,
  OUT_Y_H     = 0x2B,
  OUT_Z_L     = 0x2C,
  OUT_Z_H     = 0x2D,
  FIFO_CTRL   = 0x2E,
  FIFO_SRC    = 0x2F,
  ST1_1       = 0x40,
  ST1_2       = 0x41,
  ST1_3       = 0x42,
  ST1_4       = 0x43,
  ST1_5       = 0x44,
  ST1_6       = 0x45,
  ST1_7       = 0x46,
  ST1_8       = 0x47,
  ST1_9       = 0x48,
  ST1_10      = 0x49,
  ST1_11      = 0x4A,
  ST1_12      = 0x4B,
  ST1_13      = 0x4C,
  ST1_14      = 0x4D,
  ST1_15      = 0x4E,
  ST1_16      = 0x4F,
  TIM4_1      = 0x50,
  TIM3_1      = 0x51,
  TIM2_1_1    = 0x52,
  TIM2_1_2    = 0x53,
  TIM1_1_1    = 0x54,
  TIM1_1_5    = 0x55,
  THRS2_1     = 0x56,
  THRS1_1     = 0x57,
  MASK1_B     = 0x59,
  MASK1_A     = 0x5A,
  SETT1       = 0x5B,
  PR1         = 0x5C,
  TC1_1       = 0x5D,
  TC1_2       = 0x5E,
  OUTS1       = 0x5F,
  ST2_1       = 0x60,
  ST2_2       = 0x61,
  ST2_3       = 0x62,
  ST2_4       = 0x63,
  ST2_5       = 0x64,
  ST2_6       = 0x65,
  ST2_7       = 0x66,
  ST2_8       = 0x67,
  ST2_9       = 0x68,
  ST2_10      = 0x69,
  ST2_11      = 0x6A,
  ST2_12      = 0x6B,
  ST2_13      = 0x6C,
  ST2_14      = 0x6D,
  ST2_15      = 0x6E,
  ST2_16      = 0x6F,
  TIM4_2      = 0x70,
  TIM3_2      = 0x71,
  TIM2_2_1    = 0x72,
  TIM2_2_2    = 0x73,
  TIM1_2_1    = 0x74,
  TIM1_2_5    = 0x75,
  THRS2_2     = 0x76,
  THRS1_2     = 0x77,
  DES2        = 0x78,
  MASK2_B     = 0x79,
  MASK2_A     = 0x7A,
  SETT2       = 0x7B,
  PR2         = 0x7C,
  TC2_1       = 0x7D,
  TC2_2       = 0x7E
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LIS3DSH_Io
{

public:

           LIS3DSH_Io() { }
  virtual ~LIS3DSH_Io() { }


  virtual bool readRegister (Register const reg, uint8_t       * data, uint16_t const num_bytes) = 0;
  virtual bool readRegister (Register const reg, uint8_t       * data                          ) = 0;
  virtual bool writeRegister(Register const reg, uint8_t const * data, uint16_t const num_bytes) = 0;
  virtual bool writeRegister(Register const reg, uint8_t const   data                          ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* LIS3DSH */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3DSH_INTERFACE_LIS3DSH_IO_INTERFACE_H_ */
