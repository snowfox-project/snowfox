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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_AD7151_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_AD7151_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include <spectre/driver/interface/Debug.h>

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

namespace AD7151
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* AD7151_STATUS_REG Bit Definitions **************************************************/
#define AD7151_SETUP_REG_nDRDY_bm                 (1<<0)

/* AD7151_SETUP_REG Bit Definitions ***************************************************/
#define AD7151_SETUP_REG_RNG_H_bm                 (1<<7)
#define AD7151_SETUP_REG_RNG_L_bm                 (1<<6)
#define AD7151_SETUP_REG_HYST_bm                  (1<<4)
#define AD7151_SETUP_REG_THRESHOLD_SETTING_3_bm   (1<<3)
#define AD7151_SETUP_REG_THRESHOLD_SETTING_2_bm   (1<<2)
#define AD7151_SETUP_REG_THRESHOLD_SETTING_1_bm   (1<<1)
#define AD7151_SETUP_REG_THRESHOLD_SETTING_0_bm   (1<<0)

/* AD7151_CONFIG_REG Bit Definitions **************************************************/
#define AD7151_CONFIG_REG_THRESHOLD_FIXED_bm      (1<<7)
#define AD7151_CONFIG_REG_THRESHOLD_MODE_1_bm     (1<<6)
#define AD7151_CONFIG_REG_THRESHOLD_MODE_2_bm     (1<<5)
#define AD7151_CONFIG_REG_ENABLE_CONVERSION_bm    (1<<4)
#define AD7151_CONFIG_REG_MODE_2_bm               (1<<2)
#define AD7151_CONFIG_REG_MODE_1_bm               (1<<1)
#define AD7151_CONFIG_REG_MODE_0_bm               (1<<0)

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  CAPACITIVE_INPUT_RANGE_2_0_pF = 0,
  CAPACITIVE_INPUT_RANGE_0_5_pF =                             AD7151_SETUP_REG_RNG_L_bm,
  CAPACITIVE_INPUT_RANGE_1_0_pF = AD7151_SETUP_REG_RNG_H_bm,
  CAPACITIVE_INPUT_RANGE_4_0_pF = AD7151_SETUP_REG_RNG_H_bm | AD7151_SETUP_REG_RNG_L_bm
} CapacitiveInputRangeSelect;

typedef enum
{
  REG_STATUS                      = 0x00,
  REG_DATA_HIGH                   = 0x01,
  REG_DATA_LOW                    = 0x02,
  REG_AVERAGE_HIGH                = 0x05,
  REG_AVERAGE_LOW                 = 0x06,
  REG_SENSITIVITY_THRESHOLD_HIGH  = 0x09,
  REG_SENSITIVITY_THRESHOLD_LOW   = 0x0A,
  REG_SETUP                       = 0x0B,
  REG_CONFIGURATION               = 0x0F,
  REG_POWER_DOWN_TIMER            = 0x10,
  REG_CAPDAC                      = 0x11,
  REG_SERIAL_NUMBER_3             = 0x13,
  REG_SERIAL_NUMBER_2             = 0x14,
  REG_SERIAL_NUMBER_1             = 0x15,
  REG_SERIAL_NUMBER_0             = 0x16,
  REG_CHIP_ID                     = 0x17
} RegisterSelect;

/**************************************************************************************
 * CLASS DECLARATION Interface
 **************************************************************************************/

class Interface
{

public:

           Interface() { }
  virtual ~Interface() { }


  virtual bool startSingleConversion        (                                 ) = 0;
  virtual bool checkIfConversionIsComplete  (bool     * is_conversion_complete) = 0;
  virtual bool readConversionResult         (uint16_t * raw_data              ) = 0;

};

/**************************************************************************************
 * CLASS DECLARATION ConfigurationInterface
 **************************************************************************************/

class ConfigurationInterface
{

public:

           ConfigurationInterface() { }
  virtual ~ConfigurationInterface() { }


  virtual bool setCapacitiveInputRange(CapacitiveInputRangeSelect const sel) = 0;

};

/**************************************************************************************
 * CLASS DECLARATION AD7151
 **************************************************************************************/

class AD7151 : public Interface,
               public ConfigurationInterface
{

public:

   AD7151(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master);
  ~AD7151();


  /* AD7151 Interface */

  virtual bool startSingleConversion        (                                 ) override;
  virtual bool checkIfConversionIsComplete  (bool     * is_conversion_complete) override;
  virtual bool readConversionResult         (uint16_t * raw_data              ) override;


  /* AD7151 Configuration Interface */

  virtual bool setCapacitiveInputRange      (CapacitiveInputRangeSelect const sel) override;


          void debug_dumpAllRegs            (driver::interface::Debug & debug_interface);

private:

  uint8_t                     _i2c_address;
  hal::interface::I2CMaster & _i2c_master;

  bool readSingleRegister   (uint8_t const reg_addr, uint8_t        * data);
  bool writeSingleRegister  (uint8_t const reg_addr, uint8_t const    data);
  bool readMultipleRegister (uint8_t const reg_addr, uint8_t        * data, uint16_t const num_bytes);

  void debug_dumpSingleReg  (driver::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AD7151 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_AD7151_H_ */
