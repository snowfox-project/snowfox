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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_L3GD20_INTERFACE_L3GD20_CONFIGURATIONINTERFACE_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_L3GD20_INTERFACE_L3GD20_CONFIGURATIONINTERFACE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
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
 * DEFINES
 **************************************************************************************/

/* L3GD20_CTRL_REG1 Bit Definitions ***************************************************/
#define L3GD20_CTRL_REG1_DR1_bm    (1<<7)
#define L3GD20_CTRL_REG1_DR0_bm    (1<<6)
#define L3GD20_CTRL_REG1_BW1_bm    (1<<5)
#define L3GD20_CTRL_REG1_BW0_bm    (1<<4)
#define L3GD20_CTRL_REG1_PD_bm     (1<<3)
#define L3GD20_CTRL_REG1_ZEN_bm    (1<<2)
#define L3GD20_CTRL_REG1_YEN_bm    (1<<1)
#define L3GD20_CTRL_REG1_XEN_bm    (1<<0)

/* L3GD20_CTRL_REG4 Bit Definitions ***************************************************/
#define L3GD20_CTRL_REG4_BDU_bm    (1<<7)
#define L3GD20_CTRL_REG4_BLE_bm    (1<<6)
#define L3GD20_CTRL_REG4_FS1_bm    (1<<5)
#define L3GD20_CTRL_REG4_FS0_bm    (1<<4)
#define L3GD20_CTRL_REG4_SIM_bm    (1<<0)

/* L3GD20_STATUS_REG Bit Definitions **************************************************/
#define L3GD20_STATUS_REG_ZYXOR_bm (1<<7)
#define L3GD20_STATUS_REG_ZOR_bm   (1<<6)
#define L3GD20_STATUS_REG_YOR_bm   (1<<5)
#define L3GD20_STATUS_REG_XOR_bm   (1<<4)
#define L3GD20_STATUS_REG_ZYXDA_bm (1<<3)
#define L3GD20_STATUS_REG_ZDA_bm   (1<<2)
#define L3GD20_STATUS_REG_YDA_bm   (1<<1)
#define L3GD20_STATUS_REG_XDA_bm   (1<<0)

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class OutputDataRateAndBandwith : uint8_t
{
  /* ODR = 95 Hz  */
  ODR_95_Hz_CutOff_12_5_Hz    = 0,
  ODR_95_Hz_CutOff_25_Hz      =                                                                               L3GD20_CTRL_REG1_BW0_bm,
  /* ODR = 190 Hz */
  ODR_190_Hz_CutOff_12_5_Hz   =                           L3GD20_CTRL_REG1_DR0_bm,
  ODR_190_Hz_CutOff_25_Hz     =                           L3GD20_CTRL_REG1_DR0_bm |                           L3GD20_CTRL_REG1_BW0_bm,
  ODR_190_Hz_CutOff_50_Hz     =                           L3GD20_CTRL_REG1_DR0_bm | L3GD20_CTRL_REG1_BW1_bm,
  ODR_190_Hz_CutOff_70_Hz     =                           L3GD20_CTRL_REG1_DR0_bm | L3GD20_CTRL_REG1_BW1_bm | L3GD20_CTRL_REG1_BW0_bm,
  /* ODR = 380 Hz */
  ODR_380_Hz_CutOff_20_Hz     = L3GD20_CTRL_REG1_DR1_bm,
  ODR_380_Hz_CutOff_25_Hz     = L3GD20_CTRL_REG1_DR1_bm |                                                     L3GD20_CTRL_REG1_BW0_bm,
  ODR_380_Hz_CutOff_50_Hz     = L3GD20_CTRL_REG1_DR1_bm |                           L3GD20_CTRL_REG1_BW1_bm,
  ODR_380_Hz_CutOff_100_Hz    = L3GD20_CTRL_REG1_DR1_bm |                           L3GD20_CTRL_REG1_BW1_bm | L3GD20_CTRL_REG1_BW0_bm,
  /* ODR = 760 Hz */
  ODR_760_Hz_CutOff_30_Hz     = L3GD20_CTRL_REG1_DR1_bm | L3GD20_CTRL_REG1_DR0_bm,
  ODR_760_Hz_CutOff_35_Hz     = L3GD20_CTRL_REG1_DR1_bm | L3GD20_CTRL_REG1_DR0_bm |                           L3GD20_CTRL_REG1_BW0_bm,
  ODR_760_Hz_CutOff_50_Hz     = L3GD20_CTRL_REG1_DR1_bm | L3GD20_CTRL_REG1_DR0_bm | L3GD20_CTRL_REG1_BW1_bm,
  ODR_760_Hz_CutOff_100_Hz    = L3GD20_CTRL_REG1_DR1_bm | L3GD20_CTRL_REG1_DR0_bm | L3GD20_CTRL_REG1_BW1_bm | L3GD20_CTRL_REG1_BW0_bm
};

enum class FullScaleRange : uint8_t
{
  FS_plus_minus_250_DPS  = 0,
  FS_plus_minus_500_DPS  =                           L3GD20_CTRL_REG4_FS0_bm,
  FS_plus_minus_2000_DPS = L3GD20_CTRL_REG4_FS1_bm | L3GD20_CTRL_REG4_FS0_bm
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class L3GD20_Configuration
{

public:

           L3GD20_Configuration() { }
  virtual ~L3GD20_Configuration() { }


  virtual bool enablePower                  () = 0;
  virtual bool disableAllAxis               () = 0;
  virtual bool enableBlockDataUpdate        () = 0;

  virtual bool setOutputDataRateAndBandwith (OutputDataRateAndBandwith const output_data_rate_and_bandwidth) = 0;
  virtual bool setFullScaleRange            (FullScaleRange            const full_scale_range              ) = 0;

  virtual bool enableXYZAxis                () = 0;
  virtual bool enableXAxis                  () = 0;
  virtual bool enableYAxis                  () = 0;
  virtual bool enableZAxis                  () = 0;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* L3GD20 */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_L3GD20_INTERFACE_L3GD20_CONFIGURATIONINTERFACE_H_ */
