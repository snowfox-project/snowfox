/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2019 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_INA220_INTERFACE_INA220_CONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_INA220_INTERFACE_INA220_CONTROL_H_

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

namespace INA220
{

namespace interface
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* INA220_CONFIG_REG Bit Definitions **************************************************/
#define INA220_CONFIG_REG_RST_bm      (1<<15)
#define INA220_CONFIG_REG_RESERVED_bm (1<<14)
#define INA220_CONFIG_REG_BRNG_bm     (1<<13)
#define INA220_CONFIG_REG_PG1_bm      (1<<12)
#define INA220_CONFIG_REG_PG0_bm      (1<<11)
#define INA220_CONFIG_REG_BADC4_bm    (1<<10)
#define INA220_CONFIG_REG_BADC3_bm    (1<<0)
#define INA220_CONFIG_REG_BADC2_bm    (1<<8)
#define INA220_CONFIG_REG_BADC1_bm    (1<<7)
#define INA220_CONFIG_REG_SADC4_bm    (1<<6)
#define INA220_CONFIG_REG_SADC3_bm    (1<<5)
#define INA220_CONFIG_REG_SADC2_bm    (1<<4)
#define INA220_CONFIG_REG_SADC1_bm    (1<<3)
#define INA220_CONFIG_REG_MODE3_bm    (1<<2)
#define INA220_CONFIG_REG_MODE2_bm    (1<<1)
#define INA220_CONFIG_REG_MODE1_bm    (1<<0)

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class BusVoltageRange : uint16_t
{
  RANGE_16V = 0,
  RANGE_32V = INA220_CONFIG_REG_BRNG_bm
};

enum class ShuntPgaGain : uint16_t
{
  GAIN_1_0_RANGE_plus_minus_40_mV     = 0,
  GAIN_0_5_RANGE_plus_minus_80_mV     =                            INA220_CONFIG_REG_PG0_bm,
  GAIN_0_25_RANGE_plus_minus_160_mV   = INA220_CONFIG_REG_PG1_bm,
  GAIN_0_125_RANGE_plus_minus_320_mV  = INA220_CONFIG_REG_PG1_bm | INA220_CONFIG_REG_PG0_bm
};

enum class BusAdcResolution : uint16_t
{
  RES_9_Bit   = 0,
  RES_10_Bit  =                              INA220_CONFIG_REG_BADC1_bm,
  RES_11_Bit  = INA220_CONFIG_REG_BADC2_bm,
  RES_12_Bit  = INA220_CONFIG_REG_BADC2_bm | INA220_CONFIG_REG_BADC1_bm
};

enum class ShuntAdcResolution : uint16_t
{
  RES_9_Bit   = 0,
  RES_10_Bit  =                              INA220_CONFIG_REG_SADC1_bm,
  RES_11_Bit  = INA220_CONFIG_REG_SADC2_bm,
  RES_12_Bit  = INA220_CONFIG_REG_SADC2_bm | INA220_CONFIG_REG_SADC1_bm
};

enum class OperatingMode : uint16_t
{
  Power_Down                 = 0,
  V_SHUNT_triggered          =                                                           INA220_CONFIG_REG_MODE1_bm,
  V_BUS_triggered            =                              INA220_CONFIG_REG_MODE2_bm,
  V_SHUNT_and_BUS_triggered  =                              INA220_CONFIG_REG_MODE2_bm | INA220_CONFIG_REG_MODE1_bm,
  ADC_OFF                    = INA220_CONFIG_REG_MODE3_bm,
  V_SHUNT_continous          = INA220_CONFIG_REG_MODE3_bm |                              INA220_CONFIG_REG_MODE1_bm,
  V_BUS_continous            = INA220_CONFIG_REG_MODE3_bm | INA220_CONFIG_REG_MODE2_bm,
  V_SHUNT_and_BUS_continous  = INA220_CONFIG_REG_MODE3_bm | INA220_CONFIG_REG_MODE2_bm | INA220_CONFIG_REG_MODE1_bm
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class INA220_Control
{

public:

           INA220_Control() { }
  virtual ~INA220_Control() { }


  virtual bool readShuntVoltage     (int16_t * shunt_voltage) = 0;
  virtual bool readBusVoltage       (int16_t * bus_voltage  ) = 0;


  virtual bool setBusVoltageRange   (BusVoltageRange    const bus_voltage_range   ) = 0;
  virtual bool setShuntPgaGain      (ShuntPgaGain       const shunt_pga_gain      ) = 0;
  virtual bool setBusAdcResolution  (BusAdcResolution   const bus_adc_resolution  ) = 0;
  virtual bool setShuntAdcResolution(ShuntAdcResolution const shunt_adc_resolution) = 0;
  virtual bool setOperatingMode     (OperatingMode      const operating_mode      ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* INA220 */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_INA220_INTERFACE_INA220_CONTROL_H_ */
