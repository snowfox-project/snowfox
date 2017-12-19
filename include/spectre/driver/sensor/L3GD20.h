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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_L3GD20_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_L3GD20_H_

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

namespace L3GD20
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
 * TYPEDEFS
 **************************************************************************************/

typedef enum
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
} OutputDataRateAndBandwithSelect;

typedef enum
{
  FS_plus_minus_250_DPS  = 0,
  FS_plus_minus_500_DPS  =                           L3GD20_CTRL_REG4_FS0_bm,
  FS_plus_minus_2000_DPS = L3GD20_CTRL_REG4_FS1_bm | L3GD20_CTRL_REG4_FS0_bm
} FullScaleSelect;

typedef enum
{
  REG_WHO_AM_I      = 0x0F,
  REG_CTRL_REG1     = 0x20,
  REG_CTRL_REG2     = 0x21,
  REG_CTRL_REG3     = 0x22,
  REG_CTRL_REG4     = 0x23,
  REG_CTRL_REG5     = 0x24,
  REG_REFERENCE     = 0x25,
  REG_OUT_TEMP      = 0x26,
  REG_STATUS_REG    = 0x27,
  REG_OUT_X_L       = 0x28,
  REG_OUT_X_H       = 0x29,
  REG_OUT_Y_L       = 0x2A,
  REG_OUT_Y_H       = 0x2B,
  REG_OUT_Z_L       = 0x2C,
  REG_OUT_Z_H       = 0x2D,
  REG_FIFO_CTRL_REG = 0x2E,
  REG_FIFO_SRC_REG  = 0x2F,
  REG_INT1_CFG      = 0x30,
  REG_INT1_SRC      = 0x31,
  REG_TSH_XH        = 0x32,
  REG_TSH_XL        = 0x33,
  REG_TSH_YH        = 0x34,
  REG_TSH_YL        = 0x35,
  REG_TSH_ZH        = 0x36,
  REG_TSH_ZL        = 0x37,
  REG_INT1_DURATION = 0x38
} RegisterSelect;

/**************************************************************************************
 * CLASS DECLARATION Interface
 **************************************************************************************/

class Interface
{

public:

           Interface() { }
  virtual ~Interface() { }


  virtual bool checkIfNewDataIsAvailable_XYZ(bool * is_new_data_available_xyz) = 0;
  virtual bool checkIfNewDataIsAvailable_X  (bool * is_new_data_available_x  ) = 0;
  virtual bool checkIfNewDataIsAvailable_Y  (bool * is_new_data_available_y  ) = 0;
  virtual bool checkIfNewDataIsAvailable_Z  (bool * is_new_data_available_z  ) = 0;

  virtual bool checkIfDataOverrun_XYZ       (bool * is_data_overrun_xyz      ) = 0;
  virtual bool checkIfDataOverrun_X         (bool * is_data_overrun_x        ) = 0;
  virtual bool checkIfDataOverrun_Y         (bool * is_data_overrun_y        ) = 0;
  virtual bool checkIfDataOverrun_Z         (bool * is_data_overrun_z        ) = 0;

  virtual bool readXYZAxis                  (int16_t * raw_x, int16_t * raw_y, int16_t * raw_z) = 0;
  virtual bool readXAxis                    (int16_t * raw_x                                  ) = 0;
  virtual bool readYAxis                    (int16_t * raw_y                                  ) = 0;
  virtual bool readZAxis                    (int16_t * raw_z                                  ) = 0;

};

/**************************************************************************************
 * CLASS DECLARATION ConfigurationInterface
 **************************************************************************************/

class ConfigurationInterface
{

public:

           ConfigurationInterface() { }
  virtual ~ConfigurationInterface() { }


  virtual bool enablePower                  () = 0;
  virtual bool disableAllAxis               () = 0;
  virtual bool enableBlockDataUpdate        () = 0;

  virtual bool setOutputDataRateAndBandwith (OutputDataRateAndBandwithSelect const sel) = 0;
  virtual bool setFullScale                 (FullScaleSelect                 const sel) = 0;

  virtual bool enableXYZAxis                () = 0;
  virtual bool enableXAxis                  () = 0;
  virtual bool enableYAxis                  () = 0;
  virtual bool enableZAxis                  () = 0;
};

/**************************************************************************************
 * CLASS DECLARATION L3GD20
 **************************************************************************************/

class L3GD20 : public Interface,
               public ConfigurationInterface
{

public:

           L3GD20(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master);
  virtual ~L3GD20();


  /* L3GD20 Interface */

  virtual bool checkIfNewDataIsAvailable_XYZ(bool * is_new_data_available_xyz) override;
  virtual bool checkIfNewDataIsAvailable_X  (bool * is_new_data_available_x  ) override;
  virtual bool checkIfNewDataIsAvailable_Y  (bool * is_new_data_available_y  ) override;
  virtual bool checkIfNewDataIsAvailable_Z  (bool * is_new_data_available_z  ) override;

  virtual bool checkIfDataOverrun_XYZ       (bool * is_data_overrun_xyz      ) override;
  virtual bool checkIfDataOverrun_X         (bool * is_data_overrun_x        ) override;
  virtual bool checkIfDataOverrun_Y         (bool * is_data_overrun_y        ) override;
  virtual bool checkIfDataOverrun_Z         (bool * is_data_overrun_z        ) override;

  virtual bool readXYZAxis                  (int16_t * raw_x, int16_t * raw_y, int16_t * raw_z) override;
  virtual bool readXAxis                    (int16_t * raw_x                                  ) override;
  virtual bool readYAxis                    (int16_t * raw_y                                  ) override;
  virtual bool readZAxis                    (int16_t * raw_z                                  ) override;


  /* L3GD20 Configuration Interface */

  virtual bool enablePower                  () override;
  virtual bool disableAllAxis               () override;
  virtual bool enableBlockDataUpdate        () override;

  virtual bool setOutputDataRateAndBandwith (OutputDataRateAndBandwithSelect const sel) override;
  virtual bool setFullScale                 (FullScaleSelect                 const sel) override;

  virtual bool enableXYZAxis                () override;
  virtual bool enableXAxis                  () override;
  virtual bool enableYAxis                  () override;
  virtual bool enableZAxis                  () override;


          void debug_dumpAllRegs            (debug::interface::Debug & debug_interface);

private:

  uint8_t                     _i2c_address;
  hal::interface::I2CMaster & _i2c_master;

  bool readSingleRegister   (uint8_t const reg_addr, uint8_t       * data);
  bool writeSingleRegister  (uint8_t const reg_addr, uint8_t const   data);
  bool readMultipleRegister (uint8_t const reg_addr, uint8_t       * data, uint16_t const num_bytes);

  void debug_dumpSingleReg  (debug::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* L3GD20 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_L3GD20_H_ */
