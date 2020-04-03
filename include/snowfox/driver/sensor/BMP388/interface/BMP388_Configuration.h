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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_INTERFACE_BMP388_CONFIGURATION_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_INTERFACE_BMP388_CONFIGURATION_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/BMP388/interface/BMP388_RegisterBits.h>

#include <snowfox/util/EnumClassConv.hpp>

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
 * TYPEDEF
 **************************************************************************************/

union CalibrationData
{
  struct __attribute__((packed))
  {
    uint16_t T1;
    uint16_t T2;
    int8_t   T3;
    int16_t  P1;
    int16_t  P2;
    int8_t   P3;
    int8_t   P4;
    uint16_t P5;
    uint16_t P6;
    int8_t   P7;
    int8_t   P8;
    int16_t  P9;
    int8_t   P10;
    int8_t   P11;
  } coefficient;
  uint8_t buf[21];
};

enum class PressureOversampling : uint8_t
{
  x1  = 0,
  x2  =                                                   util::bm(OSR::OSR_P_0),
  x4  =                          util::bm(OSR::OSR_P_1),
  x8  =                          util::bm(OSR::OSR_P_1) | util::bm(OSR::OSR_P_0),
  x16 = util::bm(OSR::OSR_P_2),
  x32 = util::bm(OSR::OSR_P_2)                          | util::bm(OSR::OSR_P_0),
};

enum class TemperatureOversampling : uint8_t
{
  x1  = 0,
  x2  =                                                   util::bm(OSR::OSR_T_0),
  x4  =                          util::bm(OSR::OSR_T_1),
  x8  =                          util::bm(OSR::OSR_T_1) | util::bm(OSR::OSR_T_0),
  x16 = util::bm(OSR::OSR_T_2),
  x32 = util::bm(OSR::OSR_T_2)                          | util::bm(OSR::OSR_T_0),
};

enum class OutputDataRate : uint8_t
{
  ODR_200_Hz    = 0x00,
  ODR_100_Hz    = 0x01,
  ODR_50_Hz     = 0x02,
  ODR_25_Hz     = 0x03,
  ODR_12_5_Hz   = 0x04,
  ODR_6_25_Hz   = 0x05,
  ODR_3_1_Hz    = 0x06,
  ODR_1_5_Hz    = 0x07,
  ODR_0_78_Hz   = 0x08,
  ODR_0_39_Hz   = 0x09,
  ODR_0_2_Hz    = 0x0A,
  ODR_0_1_Hz    = 0x0B,
  ODR_0_05_Hz   = 0x0C,
  ODR_0_02_Hz   = 0x0D,
  ODR_0_01_Hz   = 0x0E,
  ODR_0_006_Hz  = 0x0F,
  ODR_0_003_Hz  = 0x10,
  ODR_0_0015_Hz = 0x11
};

enum class IntPinOutputType : uint8_t
{
  PushPull  = 0,
  OpenDrain = util::bm(INT_CTRL::INT_OD)
};

enum class Interrupt : uint8_t
{
  FifoWatermarkReached = util::bm(INT_CTRL::FWTM_EN),
  FifoFull             = util::bm(INT_CTRL::FFULL_EN),
  DataReady            = util::bm(INT_CTRL::DRDY_EN)
};

enum class PowerMode : uint8_t
{
  Sleep  = 0,
  Normal = util::bm(PWR_CTRL::MODE_1) | util::bm(PWR_CTRL::MODE_0)
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class BMP388_Configuration
{

public:

  virtual ~BMP388_Configuration() { }


  virtual void readCalibData                (CalibrationData & calib_data)                = 0;
  virtual void configPressureOversampling   (PressureOversampling const over_sampling)    = 0;
  virtual void configTemperatureOversampling(TemperatureOversampling const over_sampling) = 0;
  virtual void configOutputDataRate         (OutputDataRate const odr)                    = 0;
  virtual void setIntPinOutputType          (IntPinOutputType const type)                 = 0;
  virtual void enableInterrupt              (Interrupt const interrupt)                   = 0;
  virtual void disableInterrupt             (Interrupt const interrupt)                   = 0;
  virtual void configPowerMode              (PowerMode const mode)                        = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* BMP388 */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_INTERFACE_BMP388_CONFIGURATION_H_ */
