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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3DSH_INTERFACE_LIS3DSH_CONFIGURATIONINTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3DSH_INTERFACE_LIS3DSH_CONFIGURATIONINTERFACE_H_

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
 * DEFINES
 **************************************************************************************/

/* LIS3DSH_CTRL_REG_4 Definitions *****************************************************/
#define LIS3DSH_CTRL_REG_4_ODR_3_bm       (1<<7)  /* Output data rate and power mode selection bit 3 */
#define LIS3DSH_CTRL_REG_4_ODR_2_bm       (1<<6)  /* Output data rate and power mode selection bit 2 */
#define LIS3DSH_CTRL_REG_4_ODR_1_bm       (1<<5)  /* Output data rate and power mode selection bit 1 */
#define LIS3DSH_CTRL_REG_4_ODR_0_bm       (1<<4)  /* Output data rate and power mode selection bit 0 */
#define LIS3DSH_CTRL_REG_4_BDU_bm         (1<<3)  /* Enable block data update for accelerating data */
#define LIS3DSH_CTRL_REG_4_ZEN_bm         (1<<2)  /* Enable Z-axis */
#define LIS3DSH_CTRL_REG_4_YEN_bm         (1<<1)  /* Enable Y-axis */
#define LIS3DSH_CTRL_REG_4_XEN_bm         (1<<0)  /* Enable X-axis */

/* LIS3DSH_CTRL_REG_5 Definitions *****************************************************/
#define LIS3DSH_CTRL_REG_5_BW_2_bm        (1<<7)  /* Anti-aliasing filter bandwidth bit 2 */
#define LIS3DSH_CTRL_REG_5_BW_1_bm        (1<<6)  /* Anti-aliasing filter bandwidth bit 1 */
#define LIS3DSH_CTRL_REG_5_FSCALE_2_bm    (1<<5)  /* Full-scale selection bit 2 */
#define LIS3DSH_CTRL_REG_5_FSCALE_1_bm    (1<<4)  /* Full-scale selection bit 1 */
#define LIS3DSH_CTRL_REG_5_FSCALE_0_bm    (1<<3)  /* Full-scale selection bit 0 */
#define LIS3DSH_CTRL_REG_5_ST_2_bm        (1<<2)  /* Enable self-test bit 2 */
#define LIS3DSH_CTRL_REG_5_ST_1_bm        (1<<1)  /* Enable self-test bit 1 */
#define LIS3DSH_CTRL_REG_5_SIM_bm         (1<<0)  /* Enable SPI 4-wire interface */

/* LIS3DSH_CTRL_REG_6 Definitions *****************************************************/
#define LIS3DSH_CTRL_REG_6_FIFO_EN_bm     (1<<6)

/* LIS3DSH_STATUS_REG Bit Definitions *************************************************/
#define LIS3DSH_STATUS_REG_ZYXOR_bm       (1<<7)
#define LIS3DSH_STATUS_REG_ZOR_bm         (1<<6)
#define LIS3DSH_STATUS_REG_YOR_bm         (1<<5)
#define LIS3DSH_STATUS_REG_XOR_bm         (1<<4)
#define LIS3DSH_STATUS_REG_ZYXDA_bm       (1<<3)
#define LIS3DSH_STATUS_REG_ZDA_bm         (1<<2)
#define LIS3DSH_STATUS_REG_YDA_bm         (1<<1)
#define LIS3DSH_STATUS_REG_XDA_bm         (1<<0)

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  ODR_OFF       = 0,
  ODR_3_125_Hz  =                                                                                           LIS3DSH_CTRL_REG_4_ODR_0_bm,
  ODR_6_25_Hz   =                                                             LIS3DSH_CTRL_REG_4_ODR_1_bm,
  ODR_12_5_Hz   =                                                             LIS3DSH_CTRL_REG_4_ODR_1_bm | LIS3DSH_CTRL_REG_4_ODR_0_bm,
  ODR_25_Hz     =                               LIS3DSH_CTRL_REG_4_ODR_2_bm,
  ODR_50_Hz     =                               LIS3DSH_CTRL_REG_4_ODR_2_bm |                               LIS3DSH_CTRL_REG_4_ODR_0_bm,
  ODR_100_Hz    =                               LIS3DSH_CTRL_REG_4_ODR_2_bm | LIS3DSH_CTRL_REG_4_ODR_1_bm,
  ODR_400_Hz    =                               LIS3DSH_CTRL_REG_4_ODR_2_bm | LIS3DSH_CTRL_REG_4_ODR_1_bm | LIS3DSH_CTRL_REG_4_ODR_0_bm,
  ODR_800_Hz    = LIS3DSH_CTRL_REG_4_ODR_3_bm,
  ODR_1600_Hz   = LIS3DSH_CTRL_REG_4_ODR_3_bm |                                                             LIS3DSH_CTRL_REG_4_ODR_0_bm
} OutputDataRateSelect;

typedef enum
{
  FS_plus_minus_2g  = 0,
  FS_plus_minus_4g  =                                                                   LIS3DSH_CTRL_REG_5_FSCALE_0_bm,
  FS_plus_minus_6g  =                                  LIS3DSH_CTRL_REG_5_FSCALE_1_bm,
  FS_plus_minus_8g  =                                  LIS3DSH_CTRL_REG_5_FSCALE_1_bm | LIS3DSH_CTRL_REG_5_FSCALE_0_bm,
  FS_plus_minus_16g = LIS3DSH_CTRL_REG_5_FSCALE_2_bm
} FullScaleRangeSelect;

typedef enum
{
  BW_800_Hz = 0,
  BW_200_Hz =                              LIS3DSH_CTRL_REG_5_BW_1_bm,
  BW_400_Hz = LIS3DSH_CTRL_REG_5_BW_2_bm,
  BW_50_Hz  = LIS3DSH_CTRL_REG_5_BW_2_bm | LIS3DSH_CTRL_REG_5_BW_1_bm
} FilterBandwidth;

/**************************************************************************************
 * CLASS DECLARATION ConfigurationInterface
 **************************************************************************************/

class LIS3DSH_Configuration
{

public:

           LIS3DSH_Configuration() { }
  virtual ~LIS3DSH_Configuration() { }


  virtual bool setOutputDataRate    (OutputDataRateSelect const sel) = 0;
  virtual bool setFullScaleRange    (FullScaleRangeSelect const sel) = 0;
  virtual bool setFilterBandwidth   (FilterBandwidth      const sel) = 0;

  virtual bool enableFIFO           () = 0;
  virtual bool disableFIFO          () = 0;
  virtual bool enableBlockDataUpdate() = 0;

  virtual bool enableXYZAxis        () = 0;
  virtual bool enableXAxis          () = 0;
  virtual bool enableYAxis          () = 0;
  virtual bool enableZAxis          () = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* LIS3DSH */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3DSH_INTERFACE_LIS3DSH_CONFIGURATIONINTERFACE_H_ */
