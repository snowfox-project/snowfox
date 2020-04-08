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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/BMP388/interface/BMP388_Configuration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace BMP388
{

namespace interface
{

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

QuantizedCalibrationData convertToQuantizedCalibrationData(CalibrationData const & calib_data)
{
  QuantizedCalibrationData quant_calib_data;

  quant_calib_data.T1  = (static_cast<double>(calib_data.coefficient.T1)         / 0.00390625f);
  quant_calib_data.T2  = (static_cast<double>(calib_data.coefficient.T2)         / 1073741824.0f);
  quant_calib_data.T3  = (static_cast<double>(calib_data.coefficient.T3)         / 281474976710656.0f);
  quant_calib_data.P1  = (static_cast<double>(calib_data.coefficient.P1 - 16384) / 1048576.0f);
  quant_calib_data.P2  = (static_cast<double>(calib_data.coefficient.P2 - 16384) / 536870912.0f);
  quant_calib_data.P3  = (static_cast<double>(calib_data.coefficient.P3)         / 4294967296.0f);
  quant_calib_data.P4  = (static_cast<double>(calib_data.coefficient.P4)         / 137438953472.0f);
  quant_calib_data.P5  = (static_cast<double>(calib_data.coefficient.P5)         / 0.125f);
  quant_calib_data.P6  = (static_cast<double>(calib_data.coefficient.P6)         / 64.0f);
  quant_calib_data.P7  = (static_cast<double>(calib_data.coefficient.P7)         / 256.0f);
  quant_calib_data.P8  = (static_cast<double>(calib_data.coefficient.P8)         / 32768.0f);
  quant_calib_data.P9  = (static_cast<double>(calib_data.coefficient.P9)         / 281474976710656.0f);
  quant_calib_data.P10 = (static_cast<double>(calib_data.coefficient.P10)         / 281474976710656.0f);
  quant_calib_data.P11 = (static_cast<double>(calib_data.coefficient.P11)         / 36893488147419103232.0f);

  return quant_calib_data;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* BMP388 */

} /* sensor */

} /* driver */

} /* snowfox */
