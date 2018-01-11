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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3MDL_LIS3MDL_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3MDL_LIS3MDL_H_

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

namespace LIS3MDL
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* LIS3MDL_CTRL_REG_1 Bit Definitions *************************************************/
#define LIS3MDL_CTRL_REG_1_TEMP_EN_bm      (1<<7)   /* Enable the temperature sensor                   */
#define LIS3MDL_CTRL_REG_1_OM_1_bm         (1<<6)   /* Select the operating mode of X and Y axis bit 1 */
#define LIS3MDL_CTRL_REG_1_OM_0_bm         (1<<5)   /* Select the operating mode of X and Y axis bit 0 */
#define LIS3MDL_CTRL_REG_1_DO2_bm          (1<<4)   /* Output data rate selection bit 2                */
#define LIS3MDL_CTRL_REG_1_DO1_bm          (1<<3)   /* Output data rate selection bit 1                */
#define LIS3MDL_CTRL_REG_1_DO0_bm          (1<<2)   /* Output data rate selection bit 2                */
#define LIS3MDL_CTRL_REG_1_FAST_ODR_bm     (1<<1)   /* Enable higher output data rates                 */

/* LIS3MDL_CTRL_REG_2 Bit Definitions *************************************************/
#define LIS3MDL_CTRL_REG_2_FS_1_bm         (1<<6)   /* Full scale selection bit 1 */
#define LIS3MDL_CTRL_REG_2_FS_0_bm         (1<<5)   /* Full scale selection bit 0 */
#define LIS3MDL_CTRL_REG_2_REBOOT_bm       (1<<3)   /* Reboot Memory Content      */
#define LIS3MDL_CTRL_REG_2_SOFT_RST_bm     (1<<2)   /* Soft Reset                 */

/* LIS3MDL_CTRL_REG_3 Bit Definitions *************************************************/
#define LIS3MDL_CTRL_REG_3_MD_1_bm         (1<<1)   /* Mode selection bit 1 */
#define LIS3MDL_CTRL_REG_3_MD_0_bm         (1<<0)   /* Mode selection bit 0 */

/* LIS3MDL_CTRL_REG_4 Bit Definitions *************************************************/
#define LIS3MDL_CTRL_REG_4_OMZ_1_bm        (1<<3)   /* Select the operating mode of Z axis bit 1 */
#define LIS3MDL_CTRL_REG_4_OMZ_0_bm        (1<<2)   /* Select the operating mode of Z axis bit 0 */

/* LIS3MDL_CTRL_REG_5 Bit Definitions *************************************************/
#define LIS3MDL_CTRL_REG_5_BDU_bm          (1<<6)   /* Enable block data update for magnetic data (prevent race conditions while reading) */

/* LIS3MDL_STATUS_REG Bit Definitions *************************************************/
#define LIS3MDL_STATUS_REG_ZYXOR_bm       (1<<7)
#define LIS3MDL_STATUS_REG_ZOR_bm         (1<<6)
#define LIS3MDL_STATUS_REG_YOR_bm         (1<<5)
#define LIS3MDL_STATUS_REG_XOR_bm         (1<<4)
#define LIS3MDL_STATUS_REG_ZYXDA_bm       (1<<3)
#define LIS3MDL_STATUS_REG_ZDA_bm         (1<<2)
#define LIS3MDL_STATUS_REG_YDA_bm         (1<<1)
#define LIS3MDL_STATUS_REG_XDA_bm         (1<<0)

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  XY_LP   = 0,
  XY_MP   =                              LIS3MDL_CTRL_REG_1_OM_0_bm,
  XY_HP   = LIS3MDL_CTRL_REG_1_OM_1_bm,
  XY_UHP  = LIS3MDL_CTRL_REG_1_OM_1_bm | LIS3MDL_CTRL_REG_1_OM_0_bm
} OperativeMode_XY;

typedef enum
{
  Z_LP    = 0,
  Z_MP    =                              LIS3MDL_CTRL_REG_4_OMZ_0_bm,
  Z_HP    = LIS3MDL_CTRL_REG_4_OMZ_1_bm,
  Z_UHP   = LIS3MDL_CTRL_REG_4_OMZ_1_bm | LIS3MDL_CTRL_REG_4_OMZ_0_bm
} OperativeMode_Z;

typedef enum
{
  ODR_0_625_Hz  = 0,
  ODR_1_25_Hz   =                                                         LIS3MDL_CTRL_REG_1_DO0_bm,
  ODR_2_5_Hz    =                             LIS3MDL_CTRL_REG_1_DO1_bm,
  ODR_5_Hz      =                             LIS3MDL_CTRL_REG_1_DO1_bm | LIS3MDL_CTRL_REG_1_DO0_bm,
  ODR_10_Hz     = LIS3MDL_CTRL_REG_1_DO2_bm,
  ODR_20_Hz     = LIS3MDL_CTRL_REG_1_DO2_bm |                             LIS3MDL_CTRL_REG_1_DO0_bm,
  ODR_40_Hz     = LIS3MDL_CTRL_REG_1_DO2_bm | LIS3MDL_CTRL_REG_1_DO1_bm,
  ODR_80_Hz     = LIS3MDL_CTRL_REG_1_DO2_bm | LIS3MDL_CTRL_REG_1_DO1_bm | LIS3MDL_CTRL_REG_1_DO0_bm
} OutputDataRateSelection;

typedef enum
{
  FS_plus_minus_4_Gauss   = 0,
  FS_plus_minus_8_Gauss   =                              LIS3MDL_CTRL_REG_2_FS_0_bm,
  FS_plus_minus_12_Gauss  = LIS3MDL_CTRL_REG_2_FS_1_bm,
  FS_plus_minus_16_Gauss  = LIS3MDL_CTRL_REG_2_FS_1_bm | LIS3MDL_CTRL_REG_2_FS_0_bm
} FullScaleRangeSelect;

typedef enum
{
  MODE_CONTINOUS = 0,
  MODE_SINGLE    = LIS3MDL_CTRL_REG_3_MD_0_bm
} ConversionMode;

typedef enum
{
  REG_WHO_AM_I    = 0x0F,
  REG_CTRL_REG_1  = 0x20,
  REG_CTRL_REG_2  = 0x21,
  REG_CTRL_REG_3  = 0x22,
  REG_CTRL_REG_4  = 0x23,
  REG_CTRL_REG_5  = 0x24,
  REG_STATUS_REG  = 0x27,
  REG_OUT_X_L     = 0x28,
  REG_OUT_X_H     = 0x29,
  REG_OUT_Y_L     = 0x2A,
  REG_OUT_Y_H     = 0x2B,
  REG_OUT_Z_L     = 0x2C,
  REG_OUT_Z_H     = 0x2D,
  REG_TEMP_OUT_L  = 0x2E,
  REG_TEMP_OUT_H  = 0x2F,
  REG_INT_CFG     = 0x30,
  REG_INT_SRC     = 0x31,
  REG_INT_THS_L   = 0x32,
  REG_INT_THS_H   = 0x33
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
  virtual bool readTemperature              (int16_t * raw_temp                               ) = 0;

};

/**************************************************************************************
 * CLASS DECLARATION ConfigurationInterface
 **************************************************************************************/

class ConfigurationInterface
{

public:

           ConfigurationInterface() { }
  virtual ~ConfigurationInterface() { }


  virtual bool setOperativeMode_XY    (OperativeMode_XY        const sel) = 0;
  virtual bool setOperativeMode_Z     (OperativeMode_Z         const sel) = 0;
  virtual bool setOutputDataRate      (OutputDataRateSelection const sel) = 0;
  virtual bool setFullScale           (FullScaleRangeSelect    const sel) = 0;
  virtual bool setConversionMode      (ConversionMode          const sel) = 0;
  virtual bool enableTemperatureSensor(                                 ) = 0;
  virtual bool enableBlockDataUpdate  (                                 ) = 0;


};

/**************************************************************************************
 * CLASS DECLARATION LIS3MDL
 **************************************************************************************/

class LIS3MDL : public Interface,
                public ConfigurationInterface
{

public:

           LIS3MDL(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master);
  virtual ~LIS3MDL();


  /* LIS3MDL Interface */

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
  virtual bool readTemperature              (int16_t * raw_temp                               ) override;


  /* LIS3MDL Configuration Interface */

  virtual bool setOperativeMode_XY          (OperativeMode_XY        const sel) override;
  virtual bool setOperativeMode_Z           (OperativeMode_Z         const sel) override;
  virtual bool setOutputDataRate            (OutputDataRateSelection const sel) override;
  virtual bool setFullScale                 (FullScaleRangeSelect    const sel) override;
  virtual bool setConversionMode            (ConversionMode          const sel) override;
  virtual bool enableTemperatureSensor      (                                 ) override;
  virtual bool enableBlockDataUpdate        (                                 ) override;


          void debug_dumpAllRegs            (driver::interface::Debug & debug_interface);

private:

  uint8_t                     _i2c_address;
  hal::interface::I2CMaster & _i2c_master;

  bool readSingleRegister   (uint8_t const reg_addr, uint8_t       * data);
  bool writeSingleRegister  (uint8_t const reg_addr, uint8_t const   data);
  bool readMultipleRegister (uint8_t const reg_addr, uint8_t       * data, uint16_t const num_bytes);

  void debug_dumpSingleReg  (driver::interface::Debug & debug_interface, char const *msg, RegisterSelect const reg_sel);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS3MDL */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3MDL_LIS3MDL_H_ */
