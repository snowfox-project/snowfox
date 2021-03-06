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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS3MDL_INTERFACE_LIS3MDL_CONFIGURATIONINTERFACE_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS3MDL_INTERFACE_LIS3MDL_CONFIGURATIONINTERFACE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensor::LIS3MDL::interface
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* LIS3MDL_CTRL_REG_1 Bit Definitions *************************************************/
#define LIS3MDL_CTRL_REG_1_TEMP_EN_bm      (1<<7)   /* Enable the temperature sensor                   */
#define LIS3MDL_CTRL_REG_1_OM_1_bm         (1<<6)   /* Select the operating mode of X and Y axis bit 1 */
#define LIS3MDL_CTRL_REG_1_OM_0_bm         (1<<5)   /* Select the operating mode of X and Y axis bit 0 */
#define LIS3MDL_CTRL_REG_1_DO2_bm          (1<<4)   /* Output data rate selection bit 2                */
#define LIS3MDL_CTRL_REG_1_DO1_bm          (1<<3)   /* Output data rate selection bit 1                */
#define LIS3MDL_CTRL_REG_1_DO0_bm          (1<<2)   /* Output data rate selection bit 2                */
#define LIS3MDL_CTRL_REG_1_FAST_ODR_bm     (1<<1)   /* Enable higher output data rates                 */

/* LIS3MDL_CTRL_REG_2 Bit Definitions *************************************************/
#define LIS3MDL_CTRL_REG_2_FS_1_bm         (1<<6)   /* Full scale selection bit 1 */
#define LIS3MDL_CTRL_REG_2_FS_0_bm         (1<<5)   /* Full scale selection bit 0 */
#define LIS3MDL_CTRL_REG_2_REBOOT_bm       (1<<3)   /* Reboot Memory Content      */
#define LIS3MDL_CTRL_REG_2_SOFT_RST_bm     (1<<2)   /* Soft Reset                 */

/* LIS3MDL_CTRL_REG_3 Bit Definitions *************************************************/
#define LIS3MDL_CTRL_REG_3_MD_1_bm         (1<<1)   /* Mode selection bit 1 */
#define LIS3MDL_CTRL_REG_3_MD_0_bm         (1<<0)   /* Mode selection bit 0 */

/* LIS3MDL_CTRL_REG_4 Bit Definitions *************************************************/
#define LIS3MDL_CTRL_REG_4_OMZ_1_bm        (1<<3)   /* Select the operating mode of Z axis bit 1 */
#define LIS3MDL_CTRL_REG_4_OMZ_0_bm        (1<<2)   /* Select the operating mode of Z axis bit 0 */

/* LIS3MDL_CTRL_REG_5 Bit Definitions *************************************************/
#define LIS3MDL_CTRL_REG_5_BDU_bm          (1<<6)   /* Enable block data update for magnetic data (prevent race conditions while reading) */

/* LIS3MDL_STATUS_REG Bit Definitions *************************************************/
#define LIS3MDL_STATUS_REG_ZYXOR_bm       (1<<7)
#define LIS3MDL_STATUS_REG_ZOR_bm         (1<<6)
#define LIS3MDL_STATUS_REG_YOR_bm         (1<<5)
#define LIS3MDL_STATUS_REG_XOR_bm         (1<<4)
#define LIS3MDL_STATUS_REG_ZYXDA_bm       (1<<3)
#define LIS3MDL_STATUS_REG_ZDA_bm         (1<<2)
#define LIS3MDL_STATUS_REG_YDA_bm         (1<<1)
#define LIS3MDL_STATUS_REG_XDA_bm         (1<<0)

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class OperationMode_XY : uint8_t
{
  LP   = 0,
  MP   =                              LIS3MDL_CTRL_REG_1_OM_0_bm,
  HP   = LIS3MDL_CTRL_REG_1_OM_1_bm,
  UHP  = LIS3MDL_CTRL_REG_1_OM_1_bm | LIS3MDL_CTRL_REG_1_OM_0_bm
};

enum class OperationMode_Z : uint8_t
{
  LP    = 0,
  MP    =                              LIS3MDL_CTRL_REG_4_OMZ_0_bm,
  HP    = LIS3MDL_CTRL_REG_4_OMZ_1_bm,
  UHP   = LIS3MDL_CTRL_REG_4_OMZ_1_bm | LIS3MDL_CTRL_REG_4_OMZ_0_bm
};

enum class OutputDataRate : uint8_t
{
  ODR_0_625_Hz  = 0,
  ODR_1_25_Hz   =                                                         LIS3MDL_CTRL_REG_1_DO0_bm,
  ODR_2_5_Hz    =                             LIS3MDL_CTRL_REG_1_DO1_bm,
  ODR_5_Hz      =                             LIS3MDL_CTRL_REG_1_DO1_bm | LIS3MDL_CTRL_REG_1_DO0_bm,
  ODR_10_Hz     = LIS3MDL_CTRL_REG_1_DO2_bm,
  ODR_20_Hz     = LIS3MDL_CTRL_REG_1_DO2_bm |                             LIS3MDL_CTRL_REG_1_DO0_bm,
  ODR_40_Hz     = LIS3MDL_CTRL_REG_1_DO2_bm | LIS3MDL_CTRL_REG_1_DO1_bm,
  ODR_80_Hz     = LIS3MDL_CTRL_REG_1_DO2_bm | LIS3MDL_CTRL_REG_1_DO1_bm | LIS3MDL_CTRL_REG_1_DO0_bm
};

enum class FullScaleRange : uint8_t
{
  FS_plus_minus_4_Gauss   = 0,
  FS_plus_minus_8_Gauss   =                              LIS3MDL_CTRL_REG_2_FS_0_bm,
  FS_plus_minus_12_Gauss  = LIS3MDL_CTRL_REG_2_FS_1_bm,
  FS_plus_minus_16_Gauss  = LIS3MDL_CTRL_REG_2_FS_1_bm | LIS3MDL_CTRL_REG_2_FS_0_bm
};

enum class ConversionMode : uint8_t
{
  CONTINUOUS = 0,
  SINGLE     = LIS3MDL_CTRL_REG_3_MD_0_bm
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LIS3MDL_Configuration
{

public:

           LIS3MDL_Configuration() { }
  virtual ~LIS3MDL_Configuration() { }


  virtual bool setOperationMode_XY    (OperationMode_XY const operation_mode_xy) = 0;
  virtual bool setOperationMode_Z     (OperationMode_Z  const operation_mode_z ) = 0;
  virtual bool setOutputDataRate      (OutputDataRate   const output_data_rate ) = 0;
  virtual bool setFullScaleRange      (FullScaleRange   const full_scale_range ) = 0;
  virtual bool setConversionMode      (ConversionMode   const conversion_mode  ) = 0;
  virtual bool enableTemperatureSensor(                                        ) = 0;
  virtual bool enableBlockDataUpdate  (                                        ) = 0;


};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensor::LIS3MDL::interface */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS3MDL_INTERFACE_LIS3MDL_CONFIGURATIONINTERFACE_H_ */
