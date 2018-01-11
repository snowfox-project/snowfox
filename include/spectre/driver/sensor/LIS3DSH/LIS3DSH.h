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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3DSH_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3DSH_H_
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

namespace LIS3DSH
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* LIS3DSH_CTRL_REG_4 Definitions *****************************************************/
#define LIS3DSH_CTRL_REG_4_ODR_3_bm       (1<<7)  /* Output data rate and power mode selection bit 3 */
#define LIS3DSH_CTRL_REG_4_ODR_2_bm       (1<<6)  /* Output data rate and power mode selection bit 2 */
#define LIS3DSH_CTRL_REG_4_ODR_1_bm       (1<<5)  /* Output data rate and power mode selection bit 1 */
#define LIS3DSH_CTRL_REG_4_ODR_0_bm       (1<<4)  /* Output data rate and power mode selection bit 0 */
#define LIS3DSH_CTRL_REG_4_BDU_bm         (1<<3)  /* Enable block data update for accelerating data */
#define LIS3DSH_CTRL_REG_4_ZEN_bm         (1<<2)  /* Enable Z-axis */
#define LIS3DSH_CTRL_REG_4_YEN_bm         (1<<1)  /* Enable Y-axis */
#define LIS3DSH_CTRL_REG_4_XEN_bm         (1<<0)  /* Enable X-axis */

/* LIS3DSH_CTRL_REG_5 Definitions *****************************************************/
#define LIS3DSH_CTRL_REG_5_BW_2_bm        (1<<7)  /* Anti-aliasing filter bandwidth bit 2 */
#define LIS3DSH_CTRL_REG_5_BW_1_bm        (1<<6)  /* Anti-aliasing filter bandwidth bit 1 */
#define LIS3DSH_CTRL_REG_5_FSCALE_2_bm    (1<<5)  /* Full-scale selection bit 2 */
#define LIS3DSH_CTRL_REG_5_FSCALE_1_bm    (1<<4)  /* Full-scale selection bit 1 */
#define LIS3DSH_CTRL_REG_5_FSCALE_0_bm    (1<<3)  /* Full-scale selection bit 0 */
#define LIS3DSH_CTRL_REG_5_ST_2_bm        (1<<2)  /* Enable self-test bit 2 */
#define LIS3DSH_CTRL_REG_5_ST_1_bm        (1<<1)  /* Enable self-test bit 1 */
#define LIS3DSH_CTRL_REG_5_SIM_bm         (1<<0)  /* Enable SPI 4-wire interface */

/* LIS3DSH_CTRL_REG_6 Definitions *****************************************************/
#define LIS3DSH_CTRL_REG_6_FIFO_EN_bm     (1<<6)

/* LIS3DSH_STATUS_REG Bit Definitions *************************************************/
#define LIS3DSH_STATUS_REG_ZYXOR_bm       (1<<7)
#define LIS3DSH_STATUS_REG_ZOR_bm         (1<<6)
#define LIS3DSH_STATUS_REG_YOR_bm         (1<<5)
#define LIS3DSH_STATUS_REG_XOR_bm         (1<<4)
#define LIS3DSH_STATUS_REG_ZYXDA_bm       (1<<3)
#define LIS3DSH_STATUS_REG_ZDA_bm         (1<<2)
#define LIS3DSH_STATUS_REG_YDA_bm         (1<<1)
#define LIS3DSH_STATUS_REG_XDA_bm         (1<<0)

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  ODR_OFF       = 0,
  ODR_3_125_Hz  =                                                                                           LIS3DSH_CTRL_REG_4_ODR_0_bm,
  ODR_6_25_Hz   =                                                             LIS3DSH_CTRL_REG_4_ODR_1_bm,
  ODR_12_5_Hz   =                                                             LIS3DSH_CTRL_REG_4_ODR_1_bm | LIS3DSH_CTRL_REG_4_ODR_0_bm,
  ODR_25_Hz     =                               LIS3DSH_CTRL_REG_4_ODR_2_bm,
  ODR_50_Hz     =                               LIS3DSH_CTRL_REG_4_ODR_2_bm |                               LIS3DSH_CTRL_REG_4_ODR_0_bm,
  ODR_100_Hz    =                               LIS3DSH_CTRL_REG_4_ODR_2_bm | LIS3DSH_CTRL_REG_4_ODR_1_bm,
  ODR_400_Hz    =                               LIS3DSH_CTRL_REG_4_ODR_2_bm | LIS3DSH_CTRL_REG_4_ODR_1_bm | LIS3DSH_CTRL_REG_4_ODR_0_bm,
  ODR_800_Hz    = LIS3DSH_CTRL_REG_4_ODR_3_bm,
  ODR_1600_Hz   = LIS3DSH_CTRL_REG_4_ODR_3_bm |                                                             LIS3DSH_CTRL_REG_4_ODR_0_bm
} OutputDataRateSelect;

typedef enum
{
  FS_plus_minus_2g  = 0,
  FS_plus_minus_4g  =                                                                   LIS3DSH_CTRL_REG_5_FSCALE_0_bm,
  FS_plus_minus_6g  =                                  LIS3DSH_CTRL_REG_5_FSCALE_1_bm,
  FS_plus_minus_8g  =                                  LIS3DSH_CTRL_REG_5_FSCALE_1_bm | LIS3DSH_CTRL_REG_5_FSCALE_0_bm,
  FS_plus_minus_16g = LIS3DSH_CTRL_REG_5_FSCALE_2_bm
} FullScaleRangeSelect;

typedef enum
{
  BW_800_Hz = 0,
  BW_200_Hz =                              LIS3DSH_CTRL_REG_5_BW_1_bm,
  BW_400_Hz = LIS3DSH_CTRL_REG_5_BW_2_bm,
  BW_50_Hz  = LIS3DSH_CTRL_REG_5_BW_2_bm | LIS3DSH_CTRL_REG_5_BW_1_bm
} FilterBandwidth;

typedef enum
{
  REG_INFO_1      = 0x0D,
  REG_INFO_2      = 0x0E,
  REG_WHO_AM_I    = 0x0F,
  REG_CTRL_REG_1  = 0x21,
  REG_CTRL_REG_2  = 0x22,
  REG_CTRL_REG_3  = 0x23,
  REG_CTRL_REG_4  = 0x20,
  REG_CTRL_REG_5  = 0x24,
  REG_CTRL_REG_6  = 0x25,
  REG_STATUS      = 0x27,
  REG_OUT_T       = 0x0C,
  REG_OFF_X       = 0x10,
  REG_OFF_Y       = 0x11,
  REG_OFF_Z       = 0x12,
  REG_CS_X        = 0x13,
  REG_CS_Y        = 0x14,
  REG_CS_Z        = 0x15,
  REG_LC_L        = 0x16,
  REG_LC_H        = 0x17,
  REG_STAT        = 0x18,
  REG_PEAK1       = 0x19,
  REG_PEAK2       = 0x1A,
  REG_VFC_1       = 0x1B,
  REG_VFC_2       = 0x1C,
  REG_VFC_3       = 0x1D,
  REG_VFC_4       = 0x1E,
  REG_THRS3       = 0x1F,
  REG_OUT_X_L     = 0x28,
  REG_OUT_X_H     = 0x29,
  REG_OUT_Y_L     = 0x2A,
  REG_OUT_Y_H     = 0x2B,
  REG_OUT_Z_L     = 0x2C,
  REG_OUT_Z_H     = 0x2D,
  REG_FIFO_CTRL   = 0x2E,
  REG_FIFO_SRC    = 0x2F,
  REG_ST1_1       = 0x40,
  REG_ST1_2       = 0x41,
  REG_ST1_3       = 0x42,
  REG_ST1_4       = 0x43,
  REG_ST1_5       = 0x44,
  REG_ST1_6       = 0x45,
  REG_ST1_7       = 0x46,
  REG_ST1_8       = 0x47,
  REG_ST1_9       = 0x48,
  REG_ST1_10      = 0x49,
  REG_ST1_11      = 0x4A,
  REG_ST1_12      = 0x4B,
  REG_ST1_13      = 0x4C,
  REG_ST1_14      = 0x4D,
  REG_ST1_15      = 0x4E,
  REG_ST1_16      = 0x4F,
  REG_TIM4_1      = 0x50,
  REG_TIM3_1      = 0x51,
  REG_TIM2_1_1    = 0x52,
  REG_TIM2_1_2    = 0x53,
  REG_TIM1_1_1    = 0x54,
  REG_TIM1_1_5    = 0x55,
  REG_THRS2_1     = 0x56,
  REG_THRS1_1     = 0x57,
  REG_MASK1_B     = 0x59,
  REG_MASK1_A     = 0x5A,
  REG_SETT1       = 0x5B,
  REG_PR1         = 0x5C,
  REG_TC1_1       = 0x5D,
  REG_TC1_2       = 0x5E,
  REG_OUTS1       = 0x5F,
  REG_ST2_1       = 0x60,
  REG_ST2_2       = 0x61,
  REG_ST2_3       = 0x62,
  REG_ST2_4       = 0x63,
  REG_ST2_5       = 0x64,
  REG_ST2_6       = 0x65,
  REG_ST2_7       = 0x66,
  REG_ST2_8       = 0x67,
  REG_ST2_9       = 0x68,
  REG_ST2_10      = 0x69,
  REG_ST2_11      = 0x6A,
  REG_ST2_12      = 0x6B,
  REG_ST2_13      = 0x6C,
  REG_ST2_14      = 0x6D,
  REG_ST2_15      = 0x6E,
  REG_ST2_16      = 0x6F,
  REG_TIM4_2      = 0x70,
  REG_TIM3_2      = 0x71,
  REG_TIM2_2_1    = 0x72,
  REG_TIM2_2_2    = 0x73,
  REG_TIM1_2_1    = 0x74,
  REG_TIM1_2_5    = 0x75,
  REG_THRS2_2     = 0x76,
  REG_THRS1_2     = 0x77,
  REG_DES2        = 0x78,
  REG_MASK2_B     = 0x79,
  REG_MASK2_A     = 0x7A,
  REG_SETT2       = 0x7B,
  REG_PR2         = 0x7C,
  REG_TC2_1       = 0x7D,
  REG_TC2_2       = 0x7E
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
  virtual bool readTemperature              (int8_t  * raw_temp                               ) = 0;

};

/**************************************************************************************
 * CLASS DECLARATION ConfigurationInterface
 **************************************************************************************/

class ConfigurationInterface
{

public:

           ConfigurationInterface() { }
  virtual ~ConfigurationInterface() { }


  virtual bool setOutputDataRate    (OutputDataRateSelect const sel) = 0;
  virtual bool setFullScaleRange    (FullScaleRangeSelect const sel) = 0;
  virtual bool setFilterBandwidth   (FilterBandwidth      const sel) = 0;

  virtual bool enableFIFO           () = 0;
  virtual bool disableFIFO          () = 0;
  virtual bool enableBlockDataUpdate() = 0;

  virtual bool enableXYZAxis        () = 0;
  virtual bool enableXAxis          () = 0;
  virtual bool enableYAxis          () = 0;
  virtual bool enableZAxis          () = 0;

};

/**************************************************************************************
 * CLASS DECLARATION LIS3DSH
 **************************************************************************************/

class LIS3DSH : public Interface,
                public ConfigurationInterface
{

public:

           LIS3DSH(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master);
  virtual ~LIS3DSH();


  /* LIS3DSH Interface */

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
  virtual bool readTemperature              (int8_t  * raw_temp                               ) override;


  /* LIS3DSH Configuration Interface */

  virtual bool setOutputDataRate    (OutputDataRateSelect const sel) override;
  virtual bool setFullScaleRange    (FullScaleRangeSelect const sel) override;
  virtual bool setFilterBandwidth   (FilterBandwidth      const sel) override;

  virtual bool enableFIFO           () override;
  virtual bool disableFIFO          () override;
  virtual bool enableBlockDataUpdate() override;

  virtual bool enableXYZAxis        () override;
  virtual bool enableXAxis          () override;
  virtual bool enableYAxis          () override;
  virtual bool enableZAxis          () override;


          void debug_dumpAllRegs    (driver::interface::Debug & debug_interface);

private:

  uint8_t                     _i2c_address;
  hal::interface::I2CMaster & _i2c_master;

  bool readSingleRegister   (uint8_t const reg_addr, uint8_t       * data);
  bool writeSingleRegister  (uint8_t const reg_addr, uint8_t const   data);
  bool readMultipleRegister (uint8_t const reg_addr, uint8_t       * data, uint16_t const num_bytes);

  void debug_dumpSingleReg  (driver::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel);

};


/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS3DSH */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3DSH_H_ */
