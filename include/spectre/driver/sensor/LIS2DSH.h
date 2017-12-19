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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_LIS2DSH_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_LIS2DSH_H_

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

namespace LIS2DSH
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* LIS2DSH_STATUS_AUX_REG Bit Definitions *********************************************/
#define LIS2DSH_STATUS_AUX_REG_TOR_bm     (1<<6) /* Temperature data overrun */
#define LIS2DSH_STATUS_AUX_REG_TDA_bm     (1<<2) /* Temperature new data available */

/* LIS2DSH_TEMP_CFG_REG Definitions ***************************************************/
#define LIS2DSH_TEMP_CFG_REG_TEMP_EN_1_bm (1<<7)
#define LIS2DSH_TEMP_CFG_REG_TEMP_EN_0_bm (1<<6)

/* LIS2DSH_CTRL_REG_1 Bit Definitions *************************************************/
#define LIS2DSH_CTRL_REG_1_ODR_3_bm       (1<<7)  /* Output data rate and power mode selection bit 3 */
#define LIS2DSH_CTRL_REG_1_ODR_2_bm       (1<<6)  /* Output data rate and power mode selection bit 2 */
#define LIS2DSH_CTRL_REG_1_ODR_1_bm       (1<<5)  /* Output data rate and power mode selection bit 1 */
#define LIS2DSH_CTRL_REG_1_ODR_0_bm       (1<<4)  /* Output data rate and power mode selection bit 0 */
#define LIS2DSH_CTRL_REG_1_LPEN_bm        (1<<3)  /* Enable low power mode */
#define LIS2DSH_CTRL_REG_1_ZEN_bm         (1<<2)  /* Enable Z-axis */
#define LIS2DSH_CTRL_REG_1_YEN_bm         (1<<1)  /* Enable Y-axis */
#define LIS2DSH_CTRL_REG_1_XEN_bm         (1<<0)  /* Enable X-axis */

/* LIS2DSH_CTRL_REG_4 Bit Definitions *************************************************/
#define LIS2DSH_CTRL_REG_4_BDU_bm         (1<<7)
#define LIS2DSH_CTRL_REG_4_BLE_bm         (1<<6)
#define LIS2DSH_CTRL_REG_4_FS1_bm         (1<<5)
#define LIS2DSH_CTRL_REG_4_FS0_bm         (1<<4)
#define LIS2DSH_CTRL_REG_4_HR_bm          (1<<3)
#define LIS2DSH_CTRL_REG_4_ST1_bm         (1<<2)
#define LIS2DSH_CTRL_REG_4_ST0_bm         (1<<1)
#define LIS2DSH_CTRL_REG_4_SIM_bm         (1<<0)

/* LIS2DSH_CTRL_REG_5 Bit Definitions *************************************************/
#define LIS2DSH_CTRL_REG_5_FIFO_EN_bm     (1<<6)

/* LIS2DSH_STATUS_REG Bit Definitions *************************************************/
#define LIS2DSH_STATUS_REG_ZYXOR_bm       (1<<7)
#define LIS2DSH_STATUS_REG_ZOR_bm         (1<<6)
#define LIS2DSH_STATUS_REG_YOR_bm         (1<<5)
#define LIS2DSH_STATUS_REG_XOR_bm         (1<<4)
#define LIS2DSH_STATUS_REG_ZYXDA_bm       (1<<3)
#define LIS2DSH_STATUS_REG_ZDA_bm         (1<<2)
#define LIS2DSH_STATUS_REG_YDA_bm         (1<<1)
#define LIS2DSH_STATUS_REG_XDA_bm         (1<<0)

/* LIS2DSH_FIFO_CTRL_REG Bit Definitions **********************************************/
#define LIS2DSH_FIFO_CTRL_REG_FM1_bm      (1<<7)
#define LIS2DSH_FIFO_CTRL_REG_FM0_bm      (1<<6)
#define LIS2DSH_FIFO_CTRL_REG_TR_bm       (1<<5)

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
 {
   OM_8_Bit_Low_Power,
   OM_10_Bit_Normal,
   OM_12_Bit_High_Resolution
 } OperatingModeSelect;

 typedef enum
 {
   ODR_OFF     = 0,
   ODR_1_Hz    =                                                                                           LIS2DSH_CTRL_REG_1_ODR_0_bm,
   ODR_10_Hz   =                                                             LIS2DSH_CTRL_REG_1_ODR_1_bm,
   ODR_25_Hz   =                                                             LIS2DSH_CTRL_REG_1_ODR_1_bm | LIS2DSH_CTRL_REG_1_ODR_0_bm,
   ODR_50_Hz   =                               LIS2DSH_CTRL_REG_1_ODR_2_bm,
   ODR_100_Hz  =                               LIS2DSH_CTRL_REG_1_ODR_2_bm |                               LIS2DSH_CTRL_REG_1_ODR_0_bm,
   ODR_200_Hz  =                               LIS2DSH_CTRL_REG_1_ODR_2_bm | LIS2DSH_CTRL_REG_1_ODR_1_bm,
   ODR_400_Hz  =                               LIS2DSH_CTRL_REG_1_ODR_2_bm | LIS2DSH_CTRL_REG_1_ODR_1_bm | LIS2DSH_CTRL_REG_1_ODR_0_bm,
   ODR_1344_Hz = LIS2DSH_CTRL_REG_1_ODR_3_bm
 } OutputDataRateSelect;

 typedef enum
 {
   FS_plus_minus_2g  = 0,
   FS_plus_minus_4g  =                             LIS2DSH_CTRL_REG_4_FS0_bm,
   FS_plus_minus_8g  = LIS2DSH_CTRL_REG_4_FS1_bm,
   FS_plus_minus_16g = LIS2DSH_CTRL_REG_4_FS1_bm | LIS2DSH_CTRL_REG_4_FS0_bm
 } FullScaleRangeSelect;

 typedef enum
 {
   FIFO_MODE_BYPASS  = 0,
   FIFO_MODE_FIFO    =                                LIS2DSH_FIFO_CTRL_REG_FM0_bm,
   FIFO_MODE_STREAM  = LIS2DSH_FIFO_CTRL_REG_FM1_bm,
   FIFO_MODE_TRIGGER = LIS2DSH_FIFO_CTRL_REG_FM1_bm | LIS2DSH_FIFO_CTRL_REG_FM0_bm
 } FIFOModeSelect;

typedef enum
{
  REG_STATUS_REG_AUX  = 0x07,

  REG_OUT_TEMP_L      = 0x0C,
  REG_OUT_TEMP_H      = 0x0D,

  REG_INT_COUNTER_REG = 0x0E,

  REG_WHO_AM_I        = 0x0F,

  REG_TEMP_CFG_REG    = 0x1F,
  REG_CTRL_REG1       = 0x20,
  REG_CTRL_REG2       = 0x21,
  REG_CTRL_REG3       = 0x22,
  REG_CTRL_REG4       = 0x23,
  REG_CTRL_REG5       = 0x24,
  REG_CTRL_REG6       = 0x25,

  REG_STATUS_REG      = 0x27,

  REG_OUT_X_L         = 0x28,
  REG_OUT_X_H         = 0x29,
  REG_OUT_Y_L         = 0x2A,
  REG_OUT_Y_H         = 0x2B,
  REG_OUT_Z_L         = 0x2C,
  REG_OUT_Z_H         = 0x2D,

  REG_FIFO_CTRL_REG   = 0x2E,
  REG_FIFO_SRC_REG    = 0x2F,

  REG_INT1_CFG        = 0x30,
  REG_INT1_SOURCE     = 0x31,
  REG_INT1_THS        = 0x32,
  REG_INT1_DURATION   = 0x33,

  REG_INT2_CFG        = 0x34,
  REG_INT2_SOURCE     = 0x35,
  REG_INT2_THS        = 0x36,
  REG_INT2_DURATION   = 0x37,

  REG_CLICK_CFG       = 0x38,
  REG_CLICK_SRC       = 0x39,
  REG_CLICK_THS       = 0x3A,

  REG_TIME_LIMIT      = 0x3B,
  REG_TIME_LATENCY    = 0x3C,
  REG_TIME_WINDOW     = 0x3D,

  REG_ACT_THS         = 0x3E,
  REG_ACT_DUR         = 0x3F
} RegisterSelect;


/**************************************************************************************
 * CLASS DECLARATION Interface
 **************************************************************************************/

class Interface
{

public:

           Interface() { }
  virtual ~Interface() { }


  virtual bool checkIfNewDataIsAvailable_XYZ        (bool * is_new_data_available_xyz ) = 0;
  virtual bool checkIfNewDataIsAvailable_X          (bool * is_new_data_available_x   ) = 0;
  virtual bool checkIfNewDataIsAvailable_Y          (bool * is_new_data_available_y   ) = 0;
  virtual bool checkIfNewDataIsAvailable_Z          (bool * is_new_data_available_z   ) = 0;
  virtual bool checkIfNewDataIsAvailable_Temperature(bool * is_new_data_available_temp) = 0;

  virtual bool checkIfDataOverrun_XYZ               (bool * is_data_overrun_xyz       ) = 0;
  virtual bool checkIfDataOverrun_X                 (bool * is_data_overrun_x         ) = 0;
  virtual bool checkIfDataOverrun_Y                 (bool * is_data_overrun_y         ) = 0;
  virtual bool checkIfDataOverrun_Z                 (bool * is_data_overrun_z         ) = 0;
  virtual bool checkIfDataOverrun_Temperature       (bool * is_data_overrun_temp      ) = 0;

  virtual bool readXYZAxis                          (int16_t * raw_x, int16_t * raw_y, int16_t * raw_z) = 0;
  virtual bool readXAxis                            (int16_t * raw_x                                  ) = 0;
  virtual bool readYAxis                            (int16_t * raw_y                                  ) = 0;
  virtual bool readZAxis                            (int16_t * raw_z                                  ) = 0;
  virtual bool readTemperature                      (int16_t * raw_temp                               ) = 0;

};

/**************************************************************************************
 * CLASS DECLARATION ConfigurationInterface
 **************************************************************************************/

class ConfigurationInterface
{

public:

           ConfigurationInterface() { }
  virtual ~ConfigurationInterface() { }


  virtual bool setOperatingMode       (OperatingModeSelect  const sel) = 0;
  virtual bool setOutputDataRate      (OutputDataRateSelect const sel) = 0;
  virtual bool setFullScaleRange      (FullScaleRangeSelect const sel) = 0;
  virtual bool setFIFOMode            (FIFOModeSelect       const sel) = 0;

  virtual bool enableFIFO             () = 0;
  virtual bool disableFIFO            () = 0;
  virtual bool enableBlockDataUpdate  () = 0;
  virtual bool enableTemperatureSensor() = 0;

  virtual bool enableXYZAxis          () = 0;
  virtual bool enableXAxis            () = 0;
  virtual bool enableYAxis            () = 0;
  virtual bool enableZAxis            () = 0;

};

/**************************************************************************************
 * CLASS DECLARATION LIS2DSH
 **************************************************************************************/

class LIS2DSH : public Interface,
                public ConfigurationInterface
{

public:

           LIS2DSH(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master);
  virtual ~LIS2DSH();


  /* LIS2DSH Interface */

  virtual bool checkIfNewDataIsAvailable_XYZ        (bool * is_new_data_available_xyz ) override;
  virtual bool checkIfNewDataIsAvailable_X          (bool * is_new_data_available_x   ) override;
  virtual bool checkIfNewDataIsAvailable_Y          (bool * is_new_data_available_y   ) override;
  virtual bool checkIfNewDataIsAvailable_Z          (bool * is_new_data_available_z   ) override;
  virtual bool checkIfNewDataIsAvailable_Temperature(bool * is_new_data_available_temp) override;

  virtual bool checkIfDataOverrun_XYZ               (bool * is_data_overrun_xyz       ) override;
  virtual bool checkIfDataOverrun_X                 (bool * is_data_overrun_x         ) override;
  virtual bool checkIfDataOverrun_Y                 (bool * is_data_overrun_y         ) override;
  virtual bool checkIfDataOverrun_Z                 (bool * is_data_overrun_z         ) override;
  virtual bool checkIfDataOverrun_Temperature       (bool * is_data_overrun_temp      ) override;

  virtual bool readXYZAxis                          (int16_t * raw_x, int16_t * raw_y, int16_t * raw_z) override;
  virtual bool readXAxis                            (int16_t * raw_x                                  ) override;
  virtual bool readYAxis                            (int16_t * raw_y                                  ) override;
  virtual bool readZAxis                            (int16_t * raw_z                                  ) override;
  virtual bool readTemperature                      (int16_t * raw_temp                               ) override;


  /* LIS2DSH Configuration Interface */

  virtual bool setOperatingMode       (OperatingModeSelect  const sel) override;
  virtual bool setOutputDataRate      (OutputDataRateSelect const sel) override;
  virtual bool setFullScaleRange      (FullScaleRangeSelect const sel) override;
  virtual bool setFIFOMode            (FIFOModeSelect       const sel) override;

  virtual bool enableFIFO             () override;
  virtual bool disableFIFO            () override;
  virtual bool enableBlockDataUpdate  () override;
  virtual bool enableTemperatureSensor() override;

  virtual bool enableXYZAxis          () override;
  virtual bool enableXAxis            () override;
  virtual bool enableYAxis            () override;
  virtual bool enableZAxis            () override;


          void debug_dumpAllRegs      (debug::interface::Debug & debug_interface);

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

} /* LIS2DSH */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_LIS2DSH_H_ */
