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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/LSM6DSM/LSM6DSM_Debug.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace LSM6DSM
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

FLASH_DECLARE(static char const FUNC_CFG_ACCESS         [] = "SENSOR_SYNC_TIME_FRAME   = ");
FLASH_DECLARE(static char const SENSOR_SYNC_TIME_FRAME  [] = "SENSOR_SYNC_TIME_FRAME   = ");
FLASH_DECLARE(static char const SENSOR_SYNC_RES_RATIO   [] = "SENSOR_SYNC_RES_RATIO    = ");
FLASH_DECLARE(static char const FIFO_CTRL1              [] = "FIFO_CTRL1               = ");
FLASH_DECLARE(static char const FIFO_CTRL2              [] = "FIFO_CTRL2               = ");
FLASH_DECLARE(static char const FIFO_CTRL3              [] = "FIFO_CTRL3               = ");
FLASH_DECLARE(static char const FIFO_CTRL4              [] = "FIFO_CTRL4               = ");
FLASH_DECLARE(static char const FIFO_CTRL5              [] = "FIFO_CTRL5               = ");
FLASH_DECLARE(static char const DRDY_PULSE_CFG          [] = "DRDY_PULSE_CFG           = ");
FLASH_DECLARE(static char const INT1_CTRL               [] = "INT1_CTRL                = ");
FLASH_DECLARE(static char const INT2_CTRL               [] = "INT2_CTRL                = ");
FLASH_DECLARE(static char const WHO_AM_I                [] = "WHO_AM_I                 = ");
FLASH_DECLARE(static char const CTRL1_XL                [] = "CTRL1_XL                 = ");
FLASH_DECLARE(static char const CTRL2_G                 [] = "CTRL2_G                  = ");
FLASH_DECLARE(static char const CTRL3_C                 [] = "CTRL3_C                  = ");
FLASH_DECLARE(static char const CTRL4_C                 [] = "CTRL4_C                  = ");
FLASH_DECLARE(static char const CTRL5_C                 [] = "CTRL5_C                  = ");
FLASH_DECLARE(static char const CTRL6_C                 [] = "CTRL6_C                  = ");
FLASH_DECLARE(static char const CTRL7_G                 [] = "CTRL7_G                  = ");
FLASH_DECLARE(static char const CTRL8_XL                [] = "CTRL8_XL                 = ");
FLASH_DECLARE(static char const CTRL9_XL                [] = "CTRL9_XL                 = ");
FLASH_DECLARE(static char const CTRL10_C                [] = "CTRL10_C                 = ");
FLASH_DECLARE(static char const MASTER_CONFIG           [] = "MASTER_CONFIG            = ");
FLASH_DECLARE(static char const WAKE_UP_SRC             [] = "WAKE_UP_SRC              = ");
FLASH_DECLARE(static char const TAP_SRC                 [] = "TAP_SRC                  = ");
FLASH_DECLARE(static char const D6D_SRC                 [] = "D6D_SRC                  = ");
FLASH_DECLARE(static char const STATUS_REG              [] = "STATUS_REG               = ");
FLASH_DECLARE(static char const OUT_TEMP_L              [] = "OUT_TEMP_L               = ");
FLASH_DECLARE(static char const OUT_TEMP_H              [] = "OUT_TEMP_H               = ");
FLASH_DECLARE(static char const OUTX_L_G                [] = "OUTX_L_G                 = ");
FLASH_DECLARE(static char const OUTX_H_G                [] = "OUTX_H_G                 = ");
FLASH_DECLARE(static char const OUTY_L_G                [] = "OUTY_L_G                 = ");
FLASH_DECLARE(static char const OUTY_H_G                [] = "OUTY_H_G                 = ");
FLASH_DECLARE(static char const OUTZ_L_G                [] = "OUTZ_L_G                 = ");
FLASH_DECLARE(static char const OUTZ_H_G                [] = "OUTZ_H_G                 = ");
FLASH_DECLARE(static char const OUTX_L_XL               [] = "OUTX_L_XL                = ");
FLASH_DECLARE(static char const OUTX_H_XL               [] = "OUTX_H_XL                = ");
FLASH_DECLARE(static char const OUTY_L_XL               [] = "OUTY_L_XL                = ");
FLASH_DECLARE(static char const OUTY_H_XL               [] = "OUTY_H_XL                = ");
FLASH_DECLARE(static char const OUTZ_L_XL               [] = "OUTZ_L_XL                = ");
FLASH_DECLARE(static char const OUTZ_H_XL               [] = "OUTZ_H_XL                = ");
FLASH_DECLARE(static char const SENSORHUB1_REG          [] = "SENSORHUB1_REG           = ");
FLASH_DECLARE(static char const SENSORHUB2_REG          [] = "SENSORHUB2_REG           = ");
FLASH_DECLARE(static char const SENSORHUB3_REG          [] = "SENSORHUB3_REG           = ");
FLASH_DECLARE(static char const SENSORHUB4_REG          [] = "SENSORHUB4_REG           = ");
FLASH_DECLARE(static char const SENSORHUB5_REG          [] = "SENSORHUB5_REG           = ");
FLASH_DECLARE(static char const SENSORHUB6_REG          [] = "SENSORHUB6_REG           = ");
FLASH_DECLARE(static char const SENSORHUB7_REG          [] = "SENSORHUB7_REG           = ");
FLASH_DECLARE(static char const SENSORHUB8_REG          [] = "SENSORHUB8_REG           = ");
FLASH_DECLARE(static char const SENSORHUB9_REG          [] = "SENSORHUB9_REG           = ");
FLASH_DECLARE(static char const SENSORHUB10_REG         [] = "SENSORHUB10_REG          = ");
FLASH_DECLARE(static char const SENSORHUB11_REG         [] = "SENSORHUB11_REG          = ");
FLASH_DECLARE(static char const SENSORHUB12_REG         [] = "SENSORHUB12_REG          = ");
FLASH_DECLARE(static char const FIFO_STATUS1            [] = "FIFO_STATUS1             = ");
FLASH_DECLARE(static char const FIFO_STATUS2            [] = "FIFO_STATUS2             = ");
FLASH_DECLARE(static char const FIFO_STATUS3            [] = "FIFO_STATUS3             = ");
FLASH_DECLARE(static char const FIFO_STATUS4            [] = "FIFO_STATUS4             = ");
FLASH_DECLARE(static char const FIFO_DATA_OUT_L         [] = "FIFO_DATA_OUT_L          = ");
FLASH_DECLARE(static char const FIFO_DATA_OUT_H         [] = "FIFO_DATA_OUT_H          = ");
FLASH_DECLARE(static char const TIMESTAMP0_REG          [] = "TIMESTAMP0_REG           = ");
FLASH_DECLARE(static char const TIMESTAMP1_REG          [] = "TIMESTAMP1_REG           = ");
FLASH_DECLARE(static char const TIMESTAMP2_REG          [] = "TIMESTAMP2_REG           = ");
FLASH_DECLARE(static char const STEP_TIMESTAMP_L        [] = "STEP_TIMESTAMP_L         = ");
FLASH_DECLARE(static char const STEP_TIMESTAMP_H        [] = "STEP_TIMESTAMP_H         = ");
FLASH_DECLARE(static char const STEP_COUNTER_L          [] = "STEP_COUNTER_L           = ");
FLASH_DECLARE(static char const STEP_COUNTER_H          [] = "STEP_COUNTER_H           = ");
FLASH_DECLARE(static char const SENSORHUB13_REG         [] = "SENSORHUB13_REG          = ");
FLASH_DECLARE(static char const SENSORHUB14_REG         [] = "SENSORHUB14_REG          = ");
FLASH_DECLARE(static char const SENSORHUB15_REG         [] = "SENSORHUB15_REG          = ");
FLASH_DECLARE(static char const SENSORHUB16_REG         [] = "SENSORHUB16_REG          = ");
FLASH_DECLARE(static char const SENSORHUB17_REG         [] = "SENSORHUB17_REG          = ");
FLASH_DECLARE(static char const SENSORHUB18_REG         [] = "SENSORHUB18_REG          = ");
FLASH_DECLARE(static char const FUNC_SRC1               [] = "FUNC_SRC1                = ");
FLASH_DECLARE(static char const FUNC_SRC2               [] = "FUNC_SRC2                = ");
FLASH_DECLARE(static char const WRIST_TILT_IA           [] = "WRIST_TILT_IA            = ");
FLASH_DECLARE(static char const TAP_CFG                 [] = "TAP_CFG                  = ");
FLASH_DECLARE(static char const TAP_THS_6D              [] = "TAP_THS_6D               = ");
FLASH_DECLARE(static char const INT_DUR2                [] = "INT_DUR2                 = ");
FLASH_DECLARE(static char const WAKE_UP_THS             [] = "WAKE_UP_THS              = ");
FLASH_DECLARE(static char const WAKE_UP_DUR             [] = "WAKE_UP_DUR              = ");
FLASH_DECLARE(static char const FREE_FALL               [] = "FREE_FALL                = ");
FLASH_DECLARE(static char const MD1_CFG                 [] = "MD1_CFG                  = ");
FLASH_DECLARE(static char const MD2_CFG                 [] = "MD2_CFG                  = ");
FLASH_DECLARE(static char const MASTER_MODE_CODE        [] = "MASTER_MODE_CODE         = ");
FLASH_DECLARE(static char const SENS_SYNC_SPI_ERROR_CODE[] = "SENS_SYNC_SPI_ERROR_CODE = ");
FLASH_DECLARE(static char const OUT_MAG_RAW_X_L         [] = "OUT_MAG_RAW_X_L          = ");
FLASH_DECLARE(static char const OUT_MAG_RAW_X_H         [] = "OUT_MAG_RAW_X_H          = ");
FLASH_DECLARE(static char const OUT_MAG_RAW_Y_L         [] = "OUT_MAG_RAW_Y_L          = ");
FLASH_DECLARE(static char const OUT_MAG_RAW_Y_H         [] = "OUT_MAG_RAW_Y_H          = ");
FLASH_DECLARE(static char const OUT_MAG_RAW_Z_L         [] = "OUT_MAG_RAW_Z_L          = ");
FLASH_DECLARE(static char const OUT_MAG_RAW_Z_H         [] = "OUT_MAG_RAW_Z_H          = ");
FLASH_DECLARE(static char const INT_OIS                 [] = "INT_OIS                  = ");
FLASH_DECLARE(static char const CTRL1_OIS               [] = "CTRL1_OIS                = ");
FLASH_DECLARE(static char const CTRL2_OIS               [] = "CTRL2_OIS                = ");
FLASH_DECLARE(static char const CTRL3_OIS               [] = "CTRL3_OIS                = ");
FLASH_DECLARE(static char const X_OFS_USR               [] = "X_OFS_USR                = ");
FLASH_DECLARE(static char const Y_OFS_USR               [] = "Y_OFS_USR                = ");
FLASH_DECLARE(static char const Z_OFS_USR               [] = "Z_OFS_USR                = ");

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void LSM6DSM_Debug::debug_dumpAllRegs(trace::Trace & trace, hal::interface::Flash & flash, interface::LSM6DSM_Io & io)
{
  debug_dumpSingleReg(trace, flash, io, FUNC_CFG_ACCESS         , interface::Register::SENSOR_SYNC_TIME_FRAME   );
  debug_dumpSingleReg(trace, flash, io, SENSOR_SYNC_TIME_FRAME  , interface::Register::SENSOR_SYNC_TIME_FRAME   );
  debug_dumpSingleReg(trace, flash, io, SENSOR_SYNC_RES_RATIO   , interface::Register::SENSOR_SYNC_RES_RATIO    );
  debug_dumpSingleReg(trace, flash, io, FIFO_CTRL1              , interface::Register::FIFO_CTRL1               );
  debug_dumpSingleReg(trace, flash, io, FIFO_CTRL2              , interface::Register::FIFO_CTRL2               );
  debug_dumpSingleReg(trace, flash, io, FIFO_CTRL3              , interface::Register::FIFO_CTRL3               );
  debug_dumpSingleReg(trace, flash, io, FIFO_CTRL4              , interface::Register::FIFO_CTRL4               );
  debug_dumpSingleReg(trace, flash, io, FIFO_CTRL5              , interface::Register::FIFO_CTRL5               );
  debug_dumpSingleReg(trace, flash, io, DRDY_PULSE_CFG          , interface::Register::DRDY_PULSE_CFG           );
  debug_dumpSingleReg(trace, flash, io, INT1_CTRL               , interface::Register::INT1_CTRL                );
  debug_dumpSingleReg(trace, flash, io, INT2_CTRL               , interface::Register::INT2_CTRL                );
  debug_dumpSingleReg(trace, flash, io, WHO_AM_I                , interface::Register::WHO_AM_I                 );
  debug_dumpSingleReg(trace, flash, io, CTRL1_XL                , interface::Register::CTRL1_XL                 );
  debug_dumpSingleReg(trace, flash, io, CTRL2_G                 , interface::Register::CTRL2_G                  );
  debug_dumpSingleReg(trace, flash, io, CTRL3_C                 , interface::Register::CTRL3_C                  );
  debug_dumpSingleReg(trace, flash, io, CTRL4_C                 , interface::Register::CTRL4_C                  );
  debug_dumpSingleReg(trace, flash, io, CTRL5_C                 , interface::Register::CTRL5_C                  );
  debug_dumpSingleReg(trace, flash, io, CTRL6_C                 , interface::Register::CTRL6_C                  );
  debug_dumpSingleReg(trace, flash, io, CTRL7_G                 , interface::Register::CTRL7_G                  );
  debug_dumpSingleReg(trace, flash, io, CTRL8_XL                , interface::Register::CTRL8_XL                 );
  debug_dumpSingleReg(trace, flash, io, CTRL9_XL                , interface::Register::CTRL9_XL                 );
  debug_dumpSingleReg(trace, flash, io, CTRL10_C                , interface::Register::CTRL10_C                 );
  debug_dumpSingleReg(trace, flash, io, MASTER_CONFIG           , interface::Register::MASTER_CONFIG            );
  debug_dumpSingleReg(trace, flash, io, WAKE_UP_SRC             , interface::Register::WAKE_UP_SRC              );
  debug_dumpSingleReg(trace, flash, io, TAP_SRC                 , interface::Register::TAP_SRC                  );
  debug_dumpSingleReg(trace, flash, io, D6D_SRC                 , interface::Register::D6D_SRC                  );
  debug_dumpSingleReg(trace, flash, io, STATUS_REG              , interface::Register::STATUS_REG               );
  debug_dumpSingleReg(trace, flash, io, OUT_TEMP_L              , interface::Register::OUT_TEMP_L               );
  debug_dumpSingleReg(trace, flash, io, OUT_TEMP_H              , interface::Register::OUT_TEMP_H               );
  debug_dumpSingleReg(trace, flash, io, OUTX_L_G                , interface::Register::OUTX_L_G                 );
  debug_dumpSingleReg(trace, flash, io, OUTX_H_G                , interface::Register::OUTX_H_G                 );
  debug_dumpSingleReg(trace, flash, io, OUTY_L_G                , interface::Register::OUTY_L_G                 );
  debug_dumpSingleReg(trace, flash, io, OUTY_H_G                , interface::Register::OUTY_H_G                 );
  debug_dumpSingleReg(trace, flash, io, OUTZ_L_G                , interface::Register::OUTZ_L_G                 );
  debug_dumpSingleReg(trace, flash, io, OUTZ_H_G                , interface::Register::OUTZ_H_G                 );
  debug_dumpSingleReg(trace, flash, io, OUTX_L_XL               , interface::Register::OUTX_L_XL                );
  debug_dumpSingleReg(trace, flash, io, OUTX_H_XL               , interface::Register::OUTX_H_XL                );
  debug_dumpSingleReg(trace, flash, io, OUTY_L_XL               , interface::Register::OUTY_L_XL                );
  debug_dumpSingleReg(trace, flash, io, OUTY_H_XL               , interface::Register::OUTY_H_XL                );
  debug_dumpSingleReg(trace, flash, io, OUTZ_L_XL               , interface::Register::OUTZ_L_XL                );
  debug_dumpSingleReg(trace, flash, io, OUTZ_H_XL               , interface::Register::OUTZ_H_XL                );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB1_REG          , interface::Register::SENSORHUB1_REG           );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB2_REG          , interface::Register::SENSORHUB2_REG           );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB3_REG          , interface::Register::SENSORHUB3_REG           );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB4_REG          , interface::Register::SENSORHUB4_REG           );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB5_REG          , interface::Register::SENSORHUB5_REG           );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB6_REG          , interface::Register::SENSORHUB6_REG           );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB7_REG          , interface::Register::SENSORHUB7_REG           );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB8_REG          , interface::Register::SENSORHUB8_REG           );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB9_REG          , interface::Register::SENSORHUB9_REG           );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB10_REG         , interface::Register::SENSORHUB10_REG          );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB11_REG         , interface::Register::SENSORHUB11_REG          );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB12_REG         , interface::Register::SENSORHUB12_REG          );
  debug_dumpSingleReg(trace, flash, io, FIFO_STATUS1            , interface::Register::FIFO_STATUS1             );
  debug_dumpSingleReg(trace, flash, io, FIFO_STATUS2            , interface::Register::FIFO_STATUS2             );
  debug_dumpSingleReg(trace, flash, io, FIFO_STATUS3            , interface::Register::FIFO_STATUS3             );
  debug_dumpSingleReg(trace, flash, io, FIFO_STATUS4            , interface::Register::FIFO_STATUS4             );
  debug_dumpSingleReg(trace, flash, io, FIFO_DATA_OUT_L         , interface::Register::FIFO_DATA_OUT_L          );
  debug_dumpSingleReg(trace, flash, io, FIFO_DATA_OUT_H         , interface::Register::FIFO_DATA_OUT_H          );
  debug_dumpSingleReg(trace, flash, io, TIMESTAMP0_REG          , interface::Register::TIMESTAMP0_REG           );
  debug_dumpSingleReg(trace, flash, io, TIMESTAMP1_REG          , interface::Register::TIMESTAMP1_REG           );
  debug_dumpSingleReg(trace, flash, io, TIMESTAMP2_REG          , interface::Register::TIMESTAMP2_REG           );
  debug_dumpSingleReg(trace, flash, io, STEP_TIMESTAMP_L        , interface::Register::STEP_TIMESTAMP_L         );
  debug_dumpSingleReg(trace, flash, io, STEP_TIMESTAMP_H        , interface::Register::STEP_TIMESTAMP_H         );
  debug_dumpSingleReg(trace, flash, io, STEP_COUNTER_L          , interface::Register::STEP_COUNTER_L           );
  debug_dumpSingleReg(trace, flash, io, STEP_COUNTER_H          , interface::Register::STEP_COUNTER_H           );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB13_REG         , interface::Register::SENSORHUB13_REG          );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB14_REG         , interface::Register::SENSORHUB14_REG          );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB15_REG         , interface::Register::SENSORHUB15_REG          );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB16_REG         , interface::Register::SENSORHUB16_REG          );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB17_REG         , interface::Register::SENSORHUB17_REG          );
  debug_dumpSingleReg(trace, flash, io, SENSORHUB18_REG         , interface::Register::SENSORHUB18_REG          );
  debug_dumpSingleReg(trace, flash, io, FUNC_SRC1               , interface::Register::FUNC_SRC1                );
  debug_dumpSingleReg(trace, flash, io, FUNC_SRC2               , interface::Register::FUNC_SRC2                );
  debug_dumpSingleReg(trace, flash, io, WRIST_TILT_IA           , interface::Register::WRIST_TILT_IA            );
  debug_dumpSingleReg(trace, flash, io, TAP_CFG                 , interface::Register::TAP_CFG                  );
  debug_dumpSingleReg(trace, flash, io, TAP_THS_6D              , interface::Register::TAP_THS_6D               );
  debug_dumpSingleReg(trace, flash, io, INT_DUR2                , interface::Register::INT_DUR2                 );
  debug_dumpSingleReg(trace, flash, io, WAKE_UP_THS             , interface::Register::WAKE_UP_THS              );
  debug_dumpSingleReg(trace, flash, io, WAKE_UP_DUR             , interface::Register::WAKE_UP_DUR              );
  debug_dumpSingleReg(trace, flash, io, FREE_FALL               , interface::Register::FREE_FALL                );
  debug_dumpSingleReg(trace, flash, io, MD1_CFG                 , interface::Register::MD1_CFG                  );
  debug_dumpSingleReg(trace, flash, io, MD2_CFG                 , interface::Register::MD2_CFG                  );
  debug_dumpSingleReg(trace, flash, io, MASTER_MODE_CODE        , interface::Register::MASTER_MODE_CODE         );
  debug_dumpSingleReg(trace, flash, io, SENS_SYNC_SPI_ERROR_CODE, interface::Register::SENS_SYNC_SPI_ERROR_CODE );
  debug_dumpSingleReg(trace, flash, io, OUT_MAG_RAW_X_L         , interface::Register::OUT_MAG_RAW_X_L          );
  debug_dumpSingleReg(trace, flash, io, OUT_MAG_RAW_X_H         , interface::Register::OUT_MAG_RAW_X_H          );
  debug_dumpSingleReg(trace, flash, io, OUT_MAG_RAW_Y_L         , interface::Register::OUT_MAG_RAW_Y_L          );
  debug_dumpSingleReg(trace, flash, io, OUT_MAG_RAW_Y_H         , interface::Register::OUT_MAG_RAW_Y_H          );
  debug_dumpSingleReg(trace, flash, io, OUT_MAG_RAW_Z_L         , interface::Register::OUT_MAG_RAW_Z_L          );
  debug_dumpSingleReg(trace, flash, io, OUT_MAG_RAW_Z_H         , interface::Register::OUT_MAG_RAW_Z_H          );
  debug_dumpSingleReg(trace, flash, io, INT_OIS                 , interface::Register::INT_OIS                  );
  debug_dumpSingleReg(trace, flash, io, CTRL1_OIS               , interface::Register::CTRL1_OIS                );
  debug_dumpSingleReg(trace, flash, io, CTRL2_OIS               , interface::Register::CTRL2_OIS                );
  debug_dumpSingleReg(trace, flash, io, CTRL3_OIS               , interface::Register::CTRL3_OIS                );
  debug_dumpSingleReg(trace, flash, io, X_OFS_USR               , interface::Register::X_OFS_USR                );
  debug_dumpSingleReg(trace, flash, io, Y_OFS_USR               , interface::Register::Y_OFS_USR                );
  debug_dumpSingleReg(trace, flash, io, Z_OFS_USR               , interface::Register::Z_OFS_USR                );
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void LSM6DSM_Debug::debug_dumpSingleReg(trace::Trace & trace, hal::interface::Flash & flash, interface::LSM6DSM_Io & io, char const * msg, interface::Register const reg)
{
  char    msg_ram[32];
  uint8_t reg_content = 0;

  flash.readStringFromFlash(msg_ram, msg);
  io.readRegister(reg, &reg_content);

  trace.print(trace::Level::Debug, "%s%02X\n\r", msg_ram, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LSM6DSM */

} /* sensor */

} /* driver */

} /* snowfox */
