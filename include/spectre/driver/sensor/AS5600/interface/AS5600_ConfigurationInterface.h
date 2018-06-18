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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_AS5600_INTERFACE_AS5600_CONFIGURATIONINTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_AS5600_INTERFACE_AS5600_CONFIGURATIONINTERFACE_H_

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

namespace AS5600
{

namespace interface
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* AS5600_CONF_HIGH_BYTE_REG Bit Definitions ******************************************/
#define AS5600_CONF_HIGH_BYTE_REG_WD_bm     (1<<5)
#define AS5600_CONF_HIGH_BYTE_REG_FTH2_bm   (1<<4)
#define AS5600_CONF_HIGH_BYTE_REG_FTH1_bm   (1<<3)
#define AS5600_CONF_HIGH_BYTE_REG_FTH0_bm   (1<<2)
#define AS5600_CONF_HIGH_BYTE_REG_SF1_bm    (1<<1)
#define AS5600_CONF_HIGH_BYTE_REG_SF0_bm    (1<<0)

/* AS5600_CONF_LOW_BYTE_REG Bit Definitions *******************************************/
#define AS5600_CONF_LOW_BYTE_REG_PWMF1_bm   (1<<7)
#define AS5600_CONF_LOW_BYTE_REG_PWMF0_bm   (1<<6)
#define AS5600_CONF_LOW_BYTE_REG_OUTS1_bm   (1<<5)
#define AS5600_CONF_LOW_BYTE_REG_OUTS0_bm   (1<<4)
#define AS5600_CONF_LOW_BYTE_REG_HYST1_bm   (1<<3)
#define AS5600_CONF_LOW_BYTE_REG_HYST0_bm   (1<<2)
#define AS5600_CONF_LOW_BYTE_REG_PM1_bm     (1<<1)
#define AS5600_CONF_LOW_BYTE_REG_PM0_bm     (1<<0)

/* AS5600_STATUS_REG Bit Definitions **************************************************/
#define AS5600_STATUS_REG_MD_bm             (1<<5)
#define AS5600_STATUS_REG_ML_bm             (1<<4)
#define AS5600_STATUS_REG_MH_bm             (1<<3)

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class PowerMode : uint8_t
{
  NORMAL = 0,
  LPM1   =                                   AS5600_CONF_LOW_BYTE_REG_PM0_bm,
  LPM2   = AS5600_CONF_LOW_BYTE_REG_PM1_bm,
  LPM3   = AS5600_CONF_LOW_BYTE_REG_PM1_bm | AS5600_CONF_LOW_BYTE_REG_PM0_bm
};

enum class Hysteresis : uint8_t
{
  HYST_OFF   = 0,
  HYST_1_LSB =                                     AS5600_CONF_LOW_BYTE_REG_HYST0_bm,
  HYST_2_LSB = AS5600_CONF_LOW_BYTE_REG_HYST1_bm,
  HYST_3_LSB = AS5600_CONF_LOW_BYTE_REG_HYST1_bm | AS5600_CONF_LOW_BYTE_REG_HYST0_bm
};

enum class OutputStage : uint8_t
{
  FULL_ANALOG    = 0,
  REDUCED_ANALOG =                                     AS5600_CONF_LOW_BYTE_REG_OUTS0_bm,
  DIGITAL_PWM    = AS5600_CONF_LOW_BYTE_REG_OUTS1_bm
};

enum class PwmFrequency : uint8_t
{
  F_115_Hz = 0,
  F_230_Hz =                                     AS5600_CONF_LOW_BYTE_REG_PWMF0_bm,
  F_460_Hz = AS5600_CONF_LOW_BYTE_REG_PWMF1_bm,
  F_920_Hz = AS5600_CONF_LOW_BYTE_REG_PWMF1_bm | AS5600_CONF_LOW_BYTE_REG_PWMF0_bm
};

enum class SlowFilter : uint8_t
{
  SF_16x  = 0,
  SF_8x   =                                    AS5600_CONF_HIGH_BYTE_REG_SF0_bm,
  SF_4x   = AS5600_CONF_HIGH_BYTE_REG_SF1_bm,
  SF_2x   = AS5600_CONF_HIGH_BYTE_REG_SF1_bm | AS5600_CONF_HIGH_BYTE_REG_SF0_bm
};

enum class FastFilterThreshold : uint8_t
{
  ONLY_SLOW_FILTER = 0,
  TH_6_LSB         =                                                                         AS5600_CONF_HIGH_BYTE_REG_FTH0_bm,
  TH_7_LSB         =                                     AS5600_CONF_HIGH_BYTE_REG_FTH1_bm,
  TH_9_LSB         =                                     AS5600_CONF_HIGH_BYTE_REG_FTH1_bm | AS5600_CONF_HIGH_BYTE_REG_FTH0_bm,
  TH_18_LSB        = AS5600_CONF_HIGH_BYTE_REG_FTH2_bm,
  TH_21_LSB        = AS5600_CONF_HIGH_BYTE_REG_FTH2_bm                                     | AS5600_CONF_HIGH_BYTE_REG_FTH0_bm,
  TH_24_LSB        = AS5600_CONF_HIGH_BYTE_REG_FTH2_bm | AS5600_CONF_HIGH_BYTE_REG_FTH1_bm,
  TH_10_LSB        = AS5600_CONF_HIGH_BYTE_REG_FTH2_bm | AS5600_CONF_HIGH_BYTE_REG_FTH1_bm | AS5600_CONF_HIGH_BYTE_REG_FTH0_bm
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AS5600_ConfigurationInterface
{

public:

           AS5600_ConfigurationInterface() { }
  virtual ~AS5600_ConfigurationInterface() { }


  virtual bool setPowerMode           (PowerMode           const power_mode           ) = 0;
  virtual bool setHysteresis          (Hysteresis          const hysteresis           ) = 0;
  virtual bool setOutputStage         (OutputStage         const output_stage         ) = 0;
  virtual bool setPwmFrequency        (PwmFrequency        const pwm_frequency        ) = 0;
  virtual bool setSlowFilter          (SlowFilter          const slow_filter          ) = 0;
  virtual bool setFastFilterThreshold (FastFilterThreshold const fast_filter_threshold) = 0;
  virtual bool enableWatchog          (                                               ) = 0;
  virtual bool disableWatchog         (                                               ) = 0;

  virtual bool setAngularStartPosition(uint16_t            const angle_start          ) = 0;
  virtual bool setAngularStopPosition (uint16_t            const angle_stop           ) = 0;
  virtual bool setMaximumAngle        (uint16_t            const angle_max            ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* AS5600 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_AS5600_INTERFACE_AS5600_CONFIGURATIONINTERFACE_H_ */
