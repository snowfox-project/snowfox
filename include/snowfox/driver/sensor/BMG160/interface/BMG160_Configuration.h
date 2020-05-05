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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_BMG160_INTERFACE_BMG160_CONFIGURATIONINTERFACE_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_BMG160_INTERFACE_BMG160_CONFIGURATIONINTERFACE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensor::BMG160::interface
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* BMG160_BW_REG Bit Definitions ******************************************************/
#define BMG160_BW_REG_ODR_2_bm         (1 << 2)  /* Output data rate selection bit 2 */
#define BMG160_BW_REG_ODR_1_bm         (1 << 1)  /* Output data rate selection bit 1 */
#define BMG160_BW_REG_ODR_0_bm         (1 << 0)  /* Output data rate selection bit 0 */

/* BMG160_RANGE_REG Bit Definitions ***************************************************/
#define BMG160_RANGE_REG_FSR_2_bm      (1 << 2)  /* Full scale selection bit 2 */
#define BMG160_RANGE_REG_FSR_1_bm      (1 << 1)  /* Full scale selection bit 1 */
#define BMG160_RANGE_REG_FSR_0_bm      (1 << 0)  /* Full scale selection bit 0 */

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class OutputDataRateAndBandwith : uint8_t
{
  ODR_2000_Hz_BandWidth_523_Hz  = 0,
  ODR_2000_Hz_BandWidth_230_Hz  =                                                   BMG160_BW_REG_ODR_0_bm,
  ODR_1000_Hz_BandWidth_116_Hz  =                          BMG160_BW_REG_ODR_1_bm,
  ODR_400_Hz_BandWidth_47_Hz    =                          BMG160_BW_REG_ODR_1_bm | BMG160_BW_REG_ODR_0_bm,
  ODR_200_Hz_BandWidth_23_Hz    = BMG160_BW_REG_ODR_2_bm,
  ODR_100_Hz_BandWidth_12_Hz    = BMG160_BW_REG_ODR_2_bm |                          BMG160_BW_REG_ODR_0_bm,
  ODR_200_Hz_BandWidth_64_Hz    = BMG160_BW_REG_ODR_2_bm | BMG160_BW_REG_ODR_1_bm,
  ODR_100_Hz_BandWidth_32_Hz    = BMG160_BW_REG_ODR_2_bm | BMG160_BW_REG_ODR_1_bm | BMG160_BW_REG_ODR_0_bm
};

enum class FullScaleRange : uint8_t
{
  FS_plus_minus_2000_DPS  = 0,
  FS_plus_minus_1000_DPS  =                                                         BMG160_RANGE_REG_FSR_0_bm,
  FS_plus_minus_500_DPS   =                             BMG160_RANGE_REG_FSR_1_bm,
  FS_plus_minus_250_DPS   =                             BMG160_RANGE_REG_FSR_1_bm | BMG160_RANGE_REG_FSR_0_bm,
  FS_plus_minus_125_DPS   = BMG160_RANGE_REG_FSR_2_bm
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class BMG160_Configuration
{

public:

           BMG160_Configuration() { }
  virtual ~BMG160_Configuration() { }


  virtual bool setOutputDataRateAndBandwith (OutputDataRateAndBandwith const output_data_rate_and_bandwidth) = 0;
  virtual bool setFullScaleRange            (FullScaleRange            const full_scale_range              ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensor::BMG160::interface */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_BMG160_INTERFACE_BMG160_CONFIGURATIONINTERFACE_H_ */
