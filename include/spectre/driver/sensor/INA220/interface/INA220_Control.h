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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_INA220_INTERFACE_INA220_CONTROL_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_INA220_INTERFACE_INA220_CONTROL_H_

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
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  V_BUS_RANGE_16V = 0,
  V_BUS_RANGE_32V = INA220_CONFIG_REG_BRNG_bm
} BusVoltageRangeSelect;

typedef enum
{
  GAIN_1_0_RANGE_plus_minus_40_mV     = 0,
  GAIN_0_5_RANGE_plus_minus_80_mV     =                            INA220_CONFIG_REG_PG0_bm,
  GAIN_0_25_RANGE_plus_minus_160_mV   = INA220_CONFIG_REG_PG1_bm,
  GAIN_0_125_RANGE_plus_minus_320_mV  = INA220_CONFIG_REG_PG1_bm | INA220_CONFIG_REG_PG0_bm
} ShuntPGAGainSelect;

typedef enum
{
  RES_BUS_9_Bit   = 0,
  RES_BUS_10_Bit  =                              INA220_CONFIG_REG_BADC1_bm,
  RES_BUS_11_Bit  = INA220_CONFIG_REG_BADC2_bm,
  RES_BUS_12_Bit  = INA220_CONFIG_REG_BADC2_bm | INA220_CONFIG_REG_BADC1_bm
} BusADCResolutionSelect;

typedef enum
{
  RES_SHUNT_9_Bit   = 0,
  RES_SHUNT_10_Bit  =                              INA220_CONFIG_REG_SADC1_bm,
  RES_SHUNT_11_Bit  = INA220_CONFIG_REG_SADC2_bm,
  RES_SHUNT_12_Bit  = INA220_CONFIG_REG_SADC2_bm | INA220_CONFIG_REG_SADC1_bm
} ShuntADCResolutionSelect;

typedef enum
{
  OM_Power_Down                 = 0,
  OM_V_SHUNT_triggered          =                                                           INA220_CONFIG_REG_MODE1_bm,
  OM_V_BUS_triggered            =                              INA220_CONFIG_REG_MODE2_bm,
  OM_V_SHUNT_and_BUS_triggered  =                              INA220_CONFIG_REG_MODE2_bm | INA220_CONFIG_REG_MODE1_bm,
  OM_ADC_OFF                    = INA220_CONFIG_REG_MODE3_bm,
  OM_V_SHUNT_continous          = INA220_CONFIG_REG_MODE3_bm |                              INA220_CONFIG_REG_MODE1_bm,
  OM_V_BUS_continous            = INA220_CONFIG_REG_MODE3_bm | INA220_CONFIG_REG_MODE2_bm,
  OM_V_SHUNT_and_BUS_continous  = INA220_CONFIG_REG_MODE3_bm | INA220_CONFIG_REG_MODE2_bm | INA220_CONFIG_REG_MODE1_bm
} OperatingModeSelect;

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


  virtual bool setBusVoltageRange   (BusVoltageRangeSelect    const sel) = 0;
  virtual bool setShuntPGAGain      (ShuntPGAGainSelect       const sel) = 0;
  virtual bool setBusADCResolution  (BusADCResolutionSelect   const sel) = 0;
  virtual bool setShuntADCResolution(ShuntADCResolutionSelect const sel) = 0;
  virtual bool setOperatingMode     (OperatingModeSelect      const sel) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* INA220 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_INA220_INTERFACE_INA220_CONTROL_H_ */
