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

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  REG_INFO_1      = 0x0D,
  REG_INFO_2      = 0x0E,
  REG_WHO_AM_I    = 0x0F,
  REG_CTRL_REG_1  = 0x21,
  REG_CTRL_REG_2  = 0x22,
  REG_CTRL_REG_3  = 0x23,
  REG_CTRL_REG_4  = 0x20,
  REG_CTRL_REG_5  = 0x24,
  REG_CTRL_REG_6  = 0x25,
  REG_STATUS      = 0x27,
  REG_OUT_T       = 0x0C,
  REG_OFF_X       = 0x10,
  REG_OFF_Y       = 0x11,
  REG_OFF_Z       = 0x12,
  REG_CS_X        = 0x13,
  REG_CS_Y        = 0x14,
  REG_CS_Z        = 0x15,
  REG_LC_L        = 0x16,
  REG_LC_H        = 0x17,
  REG_STAT        = 0x18,
  REG_PEAK1       = 0x19,
  REG_PEAK2       = 0x1A,
  REG_VFC_1       = 0x1B,
  REG_VFC_2       = 0x1C,
  REG_VFC_3       = 0x1D,
  REG_VFC_4       = 0x1E,
  REG_THRS3       = 0x1F,
  REG_OUT_X_L     = 0x28,
  REG_OUT_X_H     = 0x29,
  REG_OUT_Y_L     = 0x2A,
  REG_OUT_Y_H     = 0x2B,
  REG_OUT_Z_L     = 0x2C,
  REG_OUT_Z_H     = 0x2D,
  REG_FIFO_CTRL   = 0x2E,
  REG_FIFO_SRC    = 0x2F,
  REG_ST1_1       = 0x40,
  REG_ST1_2       = 0x41,
  REG_ST1_3       = 0x42,
  REG_ST1_4       = 0x43,
  REG_ST1_5       = 0x44,
  REG_ST1_6       = 0x45,
  REG_ST1_7       = 0x46,
  REG_ST1_8       = 0x47,
  REG_ST1_9       = 0x48,
  REG_ST1_10      = 0x49,
  REG_ST1_11      = 0x4A,
  REG_ST1_12      = 0x4B,
  REG_ST1_13      = 0x4C,
  REG_ST1_14      = 0x4D,
  REG_ST1_15      = 0x4E,
  REG_ST1_16      = 0x4F,
  REG_TIM4_1      = 0x50,
  REG_TIM3_1      = 0x51,
  REG_TIM2_1_1    = 0x52,
  REG_TIM2_1_2    = 0x53,
  REG_TIM1_1_1    = 0x54,
  REG_TIM1_1_5    = 0x55,
  REG_THRS2_1     = 0x56,
  REG_THRS1_1     = 0x57,
  REG_MASK1_B     = 0x59,
  REG_MASK1_A     = 0x5A,
  REG_SETT1       = 0x5B,
  REG_PR1         = 0x5C,
  REG_TC1_1       = 0x5D,
  REG_TC1_2       = 0x5E,
  REG_OUTS1       = 0x5F,
  REG_ST2_1       = 0x60,
  REG_ST2_2       = 0x61,
  REG_ST2_3       = 0x62,
  REG_ST2_4       = 0x63,
  REG_ST2_5       = 0x64,
  REG_ST2_6       = 0x65,
  REG_ST2_7       = 0x66,
  REG_ST2_8       = 0x67,
  REG_ST2_9       = 0x68,
  REG_ST2_10      = 0x69,
  REG_ST2_11      = 0x6A,
  REG_ST2_12      = 0x6B,
  REG_ST2_13      = 0x6C,
  REG_ST2_14      = 0x6D,
  REG_ST2_15      = 0x6E,
  REG_ST2_16      = 0x6F,
  REG_TIM4_2      = 0x70,
  REG_TIM3_2      = 0x71,
  REG_TIM2_2_1    = 0x72,
  REG_TIM2_2_2    = 0x73,
  REG_TIM1_2_1    = 0x74,
  REG_TIM1_2_5    = 0x75,
  REG_THRS2_2     = 0x76,
  REG_THRS1_2     = 0x77,
  REG_DES2        = 0x78,
  REG_MASK2_B     = 0x79,
  REG_MASK2_A     = 0x7A,
  REG_SETT2       = 0x7B,
  REG_PR2         = 0x7C,
  REG_TC2_1       = 0x7D,
  REG_TC2_2       = 0x7E
} RegisterSelect;

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LIS3DSH_IO_Interface
{

public:

           LIS3DSH_IO_Interface() { }
  virtual ~LIS3DSH_IO_Interface() { }


  virtual bool readMultipleRegister (RegisterSelect const reg_sel, uint8_t       * data, uint16_t const num_bytes) = 0;
  virtual bool writeMultipleRegister(RegisterSelect const reg_sel, uint8_t const * data, uint16_t const num_bytes) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS3DSH */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3DSH_INTERFACE_LIS3DSH_IO_INTERFACE_H_ */
