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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_AS5600_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_AS5600_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include <spectre/debug/interface/Debug.h>
#include <spectre/hal/interface/i2c/I2CMaster.h>

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
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  PM_NORMAL = 0,
  PM_LPM1   =                                   AS5600_CONF_LOW_BYTE_REG_PM0_bm,
  PM_LPM2   = AS5600_CONF_LOW_BYTE_REG_PM1_bm,
  PM_LPM3   = AS5600_CONF_LOW_BYTE_REG_PM1_bm | AS5600_CONF_LOW_BYTE_REG_PM0_bm
} PowerModeSelect;

typedef enum
{
  HYST_OFF   = 0,
  HYST_1_LSB =                                     AS5600_CONF_LOW_BYTE_REG_HYST0_bm,
  HYST_2_LSB = AS5600_CONF_LOW_BYTE_REG_HYST1_bm,
  HYST_3_LSB = AS5600_CONF_LOW_BYTE_REG_HYST1_bm | AS5600_CONF_LOW_BYTE_REG_HYST0_bm
} HysteresisSelect;

typedef enum
{
  OUTPUT_STAGE_FULL_ANALOG    = 0,
  OUTPUT_STAGE_REDUCED_ANALOG =                                     AS5600_CONF_LOW_BYTE_REG_OUTS0_bm,
  OUTPUT_STAGE_DIGITAL_PWM    = AS5600_CONF_LOW_BYTE_REG_OUTS1_bm
} OutputStageSelect;

typedef enum
{
  PWM_FREQ_115_Hz = 0,
  PWM_FREQ_230_Hz =                                     AS5600_CONF_LOW_BYTE_REG_PWMF0_bm,
  PWM_FREQ_460_Hz = AS5600_CONF_LOW_BYTE_REG_PWMF1_bm,
  PWM_FREQ_920_Hz = AS5600_CONF_LOW_BYTE_REG_PWMF1_bm | AS5600_CONF_LOW_BYTE_REG_PWMF0_bm
} PWMFrequencySelect;

typedef enum
{
  SF_16x  = 0,
  SF_8x   =                                    AS5600_CONF_HIGH_BYTE_REG_SF0_bm,
  SF_4x   = AS5600_CONF_HIGH_BYTE_REG_SF1_bm,
  SF_2x   = AS5600_CONF_HIGH_BYTE_REG_SF1_bm | AS5600_CONF_HIGH_BYTE_REG_SF0_bm
} SlowFilterSelect;

typedef enum
{
  FTH_ONLY_SLOW_FILTER = 0,
  FTH_6_LSB            =                                                                         AS5600_CONF_HIGH_BYTE_REG_FTH0_bm,
  FTH_7_LSB            =                                     AS5600_CONF_HIGH_BYTE_REG_FTH1_bm,
  FTH_9_LSB            =                                     AS5600_CONF_HIGH_BYTE_REG_FTH1_bm | AS5600_CONF_HIGH_BYTE_REG_FTH0_bm,
  FTH_18_LSB           = AS5600_CONF_HIGH_BYTE_REG_FTH2_bm,
  FTH_21_LSB           = AS5600_CONF_HIGH_BYTE_REG_FTH2_bm                                     | AS5600_CONF_HIGH_BYTE_REG_FTH0_bm,
  FTH_24_LSB           = AS5600_CONF_HIGH_BYTE_REG_FTH2_bm | AS5600_CONF_HIGH_BYTE_REG_FTH1_bm,
  FTH_10_LSB           = AS5600_CONF_HIGH_BYTE_REG_FTH2_bm | AS5600_CONF_HIGH_BYTE_REG_FTH1_bm | AS5600_CONF_HIGH_BYTE_REG_FTH0_bm
} FastFilterThreshold;

typedef enum
{
  REG_ZMCO                = 0x00,
  REG_ZPOS_HIGH_BYTE      = 0x01,
  REG_ZPOS_LOW_BYTE       = 0x02,
  REG_MPOS_HIGH_BYTE      = 0x03,
  REG_MPOS_LOW_BYTE       = 0x04,
  REG_MANG_HIGH_BYTE      = 0x05,
  REG_MANG_LOW_BYTE       = 0x06,
  REG_CONF_HIGH_BYTE      = 0x07,
  REG_CONF_LOW_BYTE       = 0x08,
  REG_RAW_ANGLE_HIGH_BYTE = 0x0C,
  REG_RAW_ANGLE_LOW_BYTE  = 0x0D,
  REG_ANGLE_HIGH_BYTE     = 0x0E,
  REG_ANGLE_LOW_BYTE      = 0x0F,
  REG_STATUS              = 0x0B,
  REG_AGC                 = 0x1A,
  REG_MAGNITUDE_HIGH_BYTE = 0x1B,
  REG_MAGNITUDE_LOW_BYTE  = 0x1C
} RegisterSelect;

/**************************************************************************************
 * CLASS DECLARATION Interface
 **************************************************************************************/

class Interface
{

public:

           Interface() { }
  virtual ~Interface() { }


  virtual bool readAngle    (uint16_t * angle    ) = 0;
  virtual bool readAngleRaw (uint16_t * angle_raw) = 0;

  virtual bool readStatus   (uint8_t  * status   ) = 0;
  virtual bool readAGC      (uint8_t  * agc      ) = 0;
  virtual bool readMagnitude(uint16_t * mag      ) = 0;


};

/**************************************************************************************
 * CLASS DECLARATION ConfigurationInterface
 **************************************************************************************/

class ConfigurationInterface
{

public:

           ConfigurationInterface() { }
  virtual ~ConfigurationInterface() { }


  virtual bool setPowerMode           (PowerModeSelect     const   sel        ) = 0;
  virtual bool setHysteresis          (HysteresisSelect    const   sel        ) = 0;
  virtual bool setOutputStage         (OutputStageSelect   const   sel        ) = 0;
  virtual bool setPWMFrequency        (PWMFrequencySelect  const   sel        ) = 0;
  virtual bool setSlowFilter          (SlowFilterSelect    const   sel        ) = 0;
  virtual bool setFastFilterThreshold (FastFilterThreshold const   sel        ) = 0;
  virtual bool enableWatchog          (                                       ) = 0;
  virtual bool disableWatchog         (                                       ) = 0;

  virtual bool setAngularStartPosition(uint16_t            const   angle_start) = 0;
  virtual bool setAngularStopPosition (uint16_t            const   angle_stop ) = 0;
  virtual bool setMaximumAngle        (uint16_t            const   angle_max  ) = 0;

};

/**************************************************************************************
 * CLASS DECLARATION AS5600
 **************************************************************************************/

class AS5600 : public Interface,
               public ConfigurationInterface
{

public:

           AS5600(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master);
  virtual ~AS5600();


  /* AS5600 Interface */

  virtual bool readAngle    (uint16_t * angle    ) override;
  virtual bool readAngleRaw (uint16_t * angle_raw) override;

  virtual bool readStatus   (uint8_t  * status   ) override;
  virtual bool readAGC      (uint8_t  * agc      ) override;
  virtual bool readMagnitude(uint16_t * mag      ) override;


  /* AS5600 Configuration Interface */

  virtual bool setPowerMode           (PowerModeSelect     const   sel        ) override;
  virtual bool setHysteresis          (HysteresisSelect    const   sel        ) override;
  virtual bool setOutputStage         (OutputStageSelect   const   sel        ) override;
  virtual bool setPWMFrequency        (PWMFrequencySelect  const   sel        ) override;
  virtual bool setSlowFilter          (SlowFilterSelect    const   sel        ) override;
  virtual bool setFastFilterThreshold (FastFilterThreshold const   sel        ) override;
  virtual bool enableWatchog          (                                       ) override;
  virtual bool disableWatchog         (                                       ) override;

  virtual bool setAngularStartPosition(uint16_t            const   angle_start) override;
  virtual bool setAngularStopPosition (uint16_t            const   angle_stop ) override;
  virtual bool setMaximumAngle        (uint16_t            const   angle_max  ) override;


  static bool  isMagnetTooStrong      (uint8_t             const   status     );
  static bool  isMagnetTooWeak        (uint8_t             const   status     );
  static bool  isMagnetDetected       (uint8_t             const   status     );

         void  debug_dumpAllRegs      (debug::interface::Debug & debug_interface);

private:

  uint8_t                     _i2c_address;
  hal::interface::I2CMaster & _i2c_master;

  bool readSingleRegister   (uint8_t const reg_addr, uint8_t       * data);
  bool writeSingleRegister  (uint8_t const reg_addr, uint8_t const    data);
  bool readMultipleRegister (uint8_t const reg_addr, uint8_t       * data, uint16_t const num_bytes);
  bool writeMultipleRegister(uint8_t const reg_addr, uint8_t const * data, uint16_t const num_bytes);

  void debug_dumpSingleReg  (debug::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AS5600 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_AS5600_H_ */
