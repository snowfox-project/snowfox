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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_LIS2DSH_INTERFACE_LIS2DSH_CONFIGURATIONINTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_LIS2DSH_INTERFACE_LIS2DSH_CONFIGURATIONINTERFACE_H_

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

namespace interface
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* LIS2DSH_STATUS_AUX_REG Bit Definitions *********************************************/
#define LIS2DSH_STATUS_AUX_REG_TOR_bm     (1<<6) /* Temperature data overrun */
#define LIS2DSH_STATUS_AUX_REG_TDA_bm     (1<<2) /* Temperature new data available */

/* LIS2DSH_TEMP_CFG_REG Definitions ***************************************************/
#define LIS2DSH_TEMP_CFG_REG_TEMP_EN_1_bm (1<<7)
#define LIS2DSH_TEMP_CFG_REG_TEMP_EN_0_bm (1<<6)

/* LIS2DSH_CTRL_REG_1 Bit Definitions *************************************************/
#define LIS2DSH_CTRL_REG_1_ODR_3_bm       (1<<7)  /* Output data rate and power mode selection bit 3 */
#define LIS2DSH_CTRL_REG_1_ODR_2_bm       (1<<6)  /* Output data rate and power mode selection bit 2 */
#define LIS2DSH_CTRL_REG_1_ODR_1_bm       (1<<5)  /* Output data rate and power mode selection bit 1 */
#define LIS2DSH_CTRL_REG_1_ODR_0_bm       (1<<4)  /* Output data rate and power mode selection bit 0 */
#define LIS2DSH_CTRL_REG_1_LPEN_bm        (1<<3)  /* Enable low power mode */
#define LIS2DSH_CTRL_REG_1_ZEN_bm         (1<<2)  /* Enable Z-axis */
#define LIS2DSH_CTRL_REG_1_YEN_bm         (1<<1)  /* Enable Y-axis */
#define LIS2DSH_CTRL_REG_1_XEN_bm         (1<<0)  /* Enable X-axis */

/* LIS2DSH_CTRL_REG_4 Bit Definitions *************************************************/
#define LIS2DSH_CTRL_REG_4_BDU_bm         (1<<7)
#define LIS2DSH_CTRL_REG_4_BLE_bm         (1<<6)
#define LIS2DSH_CTRL_REG_4_FS1_bm         (1<<5)
#define LIS2DSH_CTRL_REG_4_FS0_bm         (1<<4)
#define LIS2DSH_CTRL_REG_4_HR_bm          (1<<3)
#define LIS2DSH_CTRL_REG_4_ST1_bm         (1<<2)
#define LIS2DSH_CTRL_REG_4_ST0_bm         (1<<1)
#define LIS2DSH_CTRL_REG_4_SIM_bm         (1<<0)

/* LIS2DSH_CTRL_REG_5 Bit Definitions *************************************************/
#define LIS2DSH_CTRL_REG_5_FIFO_EN_bm     (1<<6)

/* LIS2DSH_STATUS_REG Bit Definitions *************************************************/
#define LIS2DSH_STATUS_REG_ZYXOR_bm       (1<<7)
#define LIS2DSH_STATUS_REG_ZOR_bm         (1<<6)
#define LIS2DSH_STATUS_REG_YOR_bm         (1<<5)
#define LIS2DSH_STATUS_REG_XOR_bm         (1<<4)
#define LIS2DSH_STATUS_REG_ZYXDA_bm       (1<<3)
#define LIS2DSH_STATUS_REG_ZDA_bm         (1<<2)
#define LIS2DSH_STATUS_REG_YDA_bm         (1<<1)
#define LIS2DSH_STATUS_REG_XDA_bm         (1<<0)

/* LIS2DSH_FIFO_CTRL_REG Bit Definitions **********************************************/
#define LIS2DSH_FIFO_CTRL_REG_FM1_bm      (1<<7)
#define LIS2DSH_FIFO_CTRL_REG_FM0_bm      (1<<6)
#define LIS2DSH_FIFO_CTRL_REG_TR_bm       (1<<5)

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class OperatingMode : uint8_t
{
  OM_8_Bit_Low_Power,
  OM_10_Bit_Normal,
  OM_12_Bit_High_Resolution
};

enum class OutputDataRate : uint8_t
{
  ODR_OFF     = 0,
  ODR_1_Hz    =                                                                                           LIS2DSH_CTRL_REG_1_ODR_0_bm,
  ODR_10_Hz   =                                                             LIS2DSH_CTRL_REG_1_ODR_1_bm,
  ODR_25_Hz   =                                                             LIS2DSH_CTRL_REG_1_ODR_1_bm | LIS2DSH_CTRL_REG_1_ODR_0_bm,
  ODR_50_Hz   =                               LIS2DSH_CTRL_REG_1_ODR_2_bm,
  ODR_100_Hz  =                               LIS2DSH_CTRL_REG_1_ODR_2_bm |                               LIS2DSH_CTRL_REG_1_ODR_0_bm,
  ODR_200_Hz  =                               LIS2DSH_CTRL_REG_1_ODR_2_bm | LIS2DSH_CTRL_REG_1_ODR_1_bm,
  ODR_400_Hz  =                               LIS2DSH_CTRL_REG_1_ODR_2_bm | LIS2DSH_CTRL_REG_1_ODR_1_bm | LIS2DSH_CTRL_REG_1_ODR_0_bm,
  ODR_1344_Hz = LIS2DSH_CTRL_REG_1_ODR_3_bm
};

enum class FullScaleRange : uint8_t
{
  FS_plus_minus_2g  = 0,
  FS_plus_minus_4g  =                             LIS2DSH_CTRL_REG_4_FS0_bm,
  FS_plus_minus_8g  = LIS2DSH_CTRL_REG_4_FS1_bm,
  FS_plus_minus_16g = LIS2DSH_CTRL_REG_4_FS1_bm | LIS2DSH_CTRL_REG_4_FS0_bm
};

enum class FifoMode : uint8_t
{
  BYPASS  = 0,
  FIFO    =                                LIS2DSH_FIFO_CTRL_REG_FM0_bm,
  STREAM  = LIS2DSH_FIFO_CTRL_REG_FM1_bm,
  TRIGGER = LIS2DSH_FIFO_CTRL_REG_FM1_bm | LIS2DSH_FIFO_CTRL_REG_FM0_bm
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LIS2DSH_Configuration
{

public:

           LIS2DSH_Configuration() { }
  virtual ~LIS2DSH_Configuration() { }


  virtual bool setOperatingMode       (OperatingMode  const operating_mode  ) = 0;
  virtual bool setOutputDataRate      (OutputDataRate const output_data_rate) = 0;
  virtual bool setFullScaleRange      (FullScaleRange const full_scale_range) = 0;
  virtual bool setFifoMode            (FifoMode       const fifo_mode       ) = 0;

  virtual bool enableFIFO             () = 0;
  virtual bool disableFIFO            () = 0;
  virtual bool enableBlockDataUpdate  () = 0;
  virtual bool enableTemperatureSensor() = 0;

  virtual bool enableXYZAxis          () = 0;
  virtual bool enableXAxis            () = 0;
  virtual bool enableYAxis            () = 0;
  virtual bool enableZAxis            () = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* LIS2DSH */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_LIS2DSH_INTERFACE_LIS2DSH_CONFIGURATIONINTERFACE_H_ */
