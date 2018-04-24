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

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/sensor/BMG160/BMG160_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace BMG160
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

FLASH_DECLARE(static char const CHIP_ID       [] = "CHIP_ID       = ");
FLASH_DECLARE(static char const RATE_X_LSB    [] = "RATE_X_LSB    = ");
FLASH_DECLARE(static char const RATE_X_MSB    [] = "RATE_X_MSB    = ");
FLASH_DECLARE(static char const RATE_Y_LSB    [] = "RATE_Y_LSB    = ");
FLASH_DECLARE(static char const RATE_Y_MSB    [] = "RATE_Y_MSB    = ");
FLASH_DECLARE(static char const RATE_Z_LSB    [] = "RATE_Z_LSB    = ");
FLASH_DECLARE(static char const RATE_Z_MSB    [] = "RATE_Z_MSB    = ");
FLASH_DECLARE(static char const INT_STATUS_0  [] = "INT_STATUS_0  = ");
FLASH_DECLARE(static char const INT_STATUS_1  [] = "INT_STATUS_1  = ");
FLASH_DECLARE(static char const INT_STATUS_2  [] = "INT_STATUS_2  = ");
FLASH_DECLARE(static char const INT_STATUS_3  [] = "INT_STATUS_3  = ");
FLASH_DECLARE(static char const FIFO_STATUS   [] = "FIFO_STATUS   = ");
FLASH_DECLARE(static char const RANGE         [] = "RANGE         = ");
FLASH_DECLARE(static char const BW            [] = "BW            = ");
FLASH_DECLARE(static char const LPM1          [] = "LPM1          = ");
FLASH_DECLARE(static char const LPM2          [] = "LPM2          = ");
FLASH_DECLARE(static char const RATE_HBW      [] = "RATE_HBW      = ");
FLASH_DECLARE(static char const BGW_SOFTRESET [] = "BGW_SOFTRESET = ");
FLASH_DECLARE(static char const INT_EN_0      [] = "INT_EN_0      = ");
FLASH_DECLARE(static char const INT_EN_1      [] = "INT_EN_1      = ");
FLASH_DECLARE(static char const INT_MAP_0     [] = "INT_MAP_0     = ");
FLASH_DECLARE(static char const INT_MAP_1     [] = "INT_MAP_1     = ");
FLASH_DECLARE(static char const INT_MAP_2     [] = "INT_MAP_2     = ");
FLASH_DECLARE(static char const INT_ZERO      [] = "INT_ZERO      = ");
FLASH_DECLARE(static char const INT_ONE       [] = "INT_ONE       = ");
FLASH_DECLARE(static char const INT_TWO       [] = "INT_TWO       = ");
FLASH_DECLARE(static char const INT_FOUR      [] = "INT_FOUR      = ");
FLASH_DECLARE(static char const INT_RST_LATCH [] = "INT_RST_LATCH = ");
FLASH_DECLARE(static char const HIGH_TH_X     [] = "HIGH_TH_X     = ");
FLASH_DECLARE(static char const HIGH_DUR_X    [] = "HIGH_DUR_X    = ");
FLASH_DECLARE(static char const HIGH_TH_Y     [] = "HIGH_TH_Y     = ");
FLASH_DECLARE(static char const HIGH_DUR_Y    [] = "HIGH_DUR_Y    = ");
FLASH_DECLARE(static char const HIGH_TH_Z     [] = "HIGH_TH_Z     = ");
FLASH_DECLARE(static char const HIGH_DUR_Z    [] = "HIGH_DUR_Z    = ");
FLASH_DECLARE(static char const SOC           [] = "SOC           = ");
FLASH_DECLARE(static char const FOC           [] = "FOC           = ");
FLASH_DECLARE(static char const TRIM_NVM_CTRL [] = "TRIM_NVM_CTRL = ");
FLASH_DECLARE(static char const BGW_SPI3_WDT  [] = "BGW_SPI3_WDT  = ");
FLASH_DECLARE(static char const OFC1          [] = "OFC1          = ");
FLASH_DECLARE(static char const OFC2          [] = "OFC2          = ");
FLASH_DECLARE(static char const OFC3          [] = "OFC3          = ");
FLASH_DECLARE(static char const OFC4          [] = "OFC4          = ");
FLASH_DECLARE(static char const TRIM_GP0      [] = "TRIM_GP0      = ");
FLASH_DECLARE(static char const TRIM_GP1      [] = "TRIM_GP1      = ");
FLASH_DECLARE(static char const BIST          [] = "BIST          = ");
FLASH_DECLARE(static char const FIFO_CONFIG_0 [] = "FIFO_CONFIG_0 = ");
FLASH_DECLARE(static char const FIFO_CONFIG_1 [] = "FIFO_CONFIG_1 = ");
FLASH_DECLARE(static char const FIFO_DATA     [] = "FIFO_DATA     = ");

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

BMG160_Control::BMG160_Control(interface::BMG160_Io & io)
: _io(io)
{

}

BMG160_Control::~BMG160_Control()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool BMG160_Control::setOutputDataRateAndBandwith(interface::OutputDataRateAndBandwith const output_data_rate_and_bandwidth)
{
  uint8_t bw_reg_content = 0;

  if(!_io.readRegister(interface::Register::BW, &bw_reg_content)) return false;

  bw_reg_content &= ~(BMG160_BW_REG_ODR_2_bm | BMG160_BW_REG_ODR_1_bm | BMG160_BW_REG_ODR_0_bm);
  bw_reg_content |= static_cast<uint8_t>(output_data_rate_and_bandwidth);

  if(!_io.writeRegister(interface::Register::BW, bw_reg_content)) return false;

  return true;
}

bool BMG160_Control::setFullScaleRange(interface::FullScaleRange const full_scale_range)
{
  uint8_t range_content = 0;

  if(!_io.readRegister(interface::Register::RANGE, &range_content)) return false;

  range_content &= ~(BMG160_RANGE_REG_FSR_2_bm | BMG160_RANGE_REG_FSR_1_bm | BMG160_RANGE_REG_FSR_0_bm);
  range_content |= static_cast<uint8_t>(full_scale_range);

  if(!_io.writeRegister(interface::Register::RANGE, range_content)) return false;

  return true;
}

bool BMG160_Control::readXYZAxis(int16_t * raw_x, int16_t * raw_y, int16_t * raw_z)
{
  uint8_t raw_xyz_data[6];

  if(!_io.readRegister(interface::Register::RATE_X_LSB, raw_xyz_data, 6)) return false;

  uint8_t const x_l = raw_xyz_data[0];
  uint8_t const x_h = raw_xyz_data[1];
  uint8_t const y_l = raw_xyz_data[2];
  uint8_t const y_h = raw_xyz_data[3];
  uint8_t const z_l = raw_xyz_data[4];
  uint8_t const z_h = raw_xyz_data[5];

  *raw_x = static_cast<int16_t>((static_cast<uint16_t>(x_h) << 8) + (static_cast<uint16_t>(x_l)));
  *raw_y = static_cast<int16_t>((static_cast<uint16_t>(y_h) << 8) + (static_cast<uint16_t>(y_l)));
  *raw_z = static_cast<int16_t>((static_cast<uint16_t>(z_h) << 8) + (static_cast<uint16_t>(z_l)));

  return true;
}

bool BMG160_Control::readXAxis(int16_t * raw_x)
{
  uint8_t raw_x_data[2];

  if(!_io.readRegister(interface::Register::RATE_X_LSB, raw_x_data, 2)) return false;

  uint8_t const x_l = raw_x_data[0];
  uint8_t const x_h = raw_x_data[1];

  *raw_x = static_cast<int16_t>((static_cast<uint16_t>(x_h) << 8) + (static_cast<uint16_t>(x_l)));

  return true;
}

bool BMG160_Control::readYAxis(int16_t * raw_y)
{
  uint8_t raw_y_data[2];

  if(!_io.readRegister(interface::Register::RATE_Y_LSB, raw_y_data, 2)) return false;

  uint8_t const y_l = raw_y_data[0];
  uint8_t const y_h = raw_y_data[1];

  *raw_y = static_cast<int16_t>((static_cast<uint16_t>(y_h) << 8) + (static_cast<uint16_t>(y_l)));

  return true;
}

bool BMG160_Control::readZAxis(int16_t * raw_z)
{
  uint8_t raw_z_data[2];

  if(!_io.readRegister(interface::Register::RATE_Z_LSB, raw_z_data, 2)) return false;

  uint8_t const z_l = raw_z_data[0];
  uint8_t const z_h = raw_z_data[1];

  *raw_z = static_cast<int16_t>((static_cast<uint16_t>(z_h) << 8) + (static_cast<uint16_t>(z_l)));

  return true;
}

bool BMG160_Control::readTemperature(int8_t  * raw_temp)
{
  uint8_t temp_reg_content = 0;

  if(!_io.readRegister(interface::Register::TEMP, &temp_reg_content)) return false;

  *raw_temp = static_cast<int8_t>(temp_reg_content);

  return true;
}

void BMG160_Control::debug_dumpAllRegs(debug::interface::Debug & debug_interface, hal::interface::Flash & flash)
{
  debug_dumpSingleReg(debug_interface, flash, CHIP_ID      , interface::Register::CHIP_ID      );

  debug_dumpSingleReg(debug_interface, flash, RATE_X_LSB   , interface::Register::RATE_X_LSB   );
  debug_dumpSingleReg(debug_interface, flash, RATE_X_MSB   , interface::Register::RATE_X_MSB   );
  debug_dumpSingleReg(debug_interface, flash, RATE_Y_LSB   , interface::Register::RATE_Y_LSB   );
  debug_dumpSingleReg(debug_interface, flash, RATE_Y_MSB   , interface::Register::RATE_Y_MSB   );
  debug_dumpSingleReg(debug_interface, flash, RATE_Z_LSB   , interface::Register::RATE_Z_LSB   );
  debug_dumpSingleReg(debug_interface, flash, RATE_Z_MSB   , interface::Register::RATE_Z_MSB   );

  debug_dumpSingleReg(debug_interface, flash, INT_STATUS_0 , interface::Register::INT_STATUS_0 );
  debug_dumpSingleReg(debug_interface, flash, INT_STATUS_1 , interface::Register::INT_STATUS_1 );
  debug_dumpSingleReg(debug_interface, flash, INT_STATUS_2 , interface::Register::INT_STATUS_2 );
  debug_dumpSingleReg(debug_interface, flash, INT_STATUS_3 , interface::Register::INT_STATUS_3 );
  debug_dumpSingleReg(debug_interface, flash, FIFO_STATUS  , interface::Register::FIFO_STATUS  );

  debug_dumpSingleReg(debug_interface, flash, RANGE        , interface::Register::RANGE        );
  debug_dumpSingleReg(debug_interface, flash, BW           , interface::Register::BW           );
  debug_dumpSingleReg(debug_interface, flash, LPM1         , interface::Register::LPM1         );
  debug_dumpSingleReg(debug_interface, flash, LPM2         , interface::Register::LPM2         );
  debug_dumpSingleReg(debug_interface, flash, RATE_HBW     , interface::Register::RATE_HBW     );
  debug_dumpSingleReg(debug_interface, flash, BGW_SOFTRESET, interface::Register::BGW_SOFTRESET);

  debug_dumpSingleReg(debug_interface, flash, INT_EN_0     , interface::Register::INT_EN_0     );
  debug_dumpSingleReg(debug_interface, flash, INT_EN_1     , interface::Register::INT_EN_1     );
  debug_dumpSingleReg(debug_interface, flash, INT_MAP_0    , interface::Register::INT_MAP_0    );
  debug_dumpSingleReg(debug_interface, flash, INT_MAP_1    , interface::Register::INT_MAP_1    );
  debug_dumpSingleReg(debug_interface, flash, INT_MAP_2    , interface::Register::INT_MAP_2    );
  debug_dumpSingleReg(debug_interface, flash, INT_ZERO     , interface::Register::INT_ZERO     );
  debug_dumpSingleReg(debug_interface, flash, INT_ONE      , interface::Register::INT_ONE      );
  debug_dumpSingleReg(debug_interface, flash, INT_TWO      , interface::Register::INT_TWO      );
  debug_dumpSingleReg(debug_interface, flash, INT_FOUR     , interface::Register::INT_FOUR     );
  debug_dumpSingleReg(debug_interface, flash, INT_RST_LATCH, interface::Register::INT_RST_LATCH);

  debug_dumpSingleReg(debug_interface, flash, HIGH_TH_X    , interface::Register::HIGH_TH_X    );
  debug_dumpSingleReg(debug_interface, flash, HIGH_DUR_X   , interface::Register::HIGH_DUR_X   );
  debug_dumpSingleReg(debug_interface, flash, HIGH_TH_Y    , interface::Register::HIGH_TH_Y    );
  debug_dumpSingleReg(debug_interface, flash, HIGH_DUR_Y   , interface::Register::HIGH_DUR_Y   );
  debug_dumpSingleReg(debug_interface, flash, HIGH_TH_Z    , interface::Register::HIGH_TH_Z    );
  debug_dumpSingleReg(debug_interface, flash, HIGH_DUR_Z   , interface::Register::HIGH_DUR_Z   );

  debug_dumpSingleReg(debug_interface, flash, SOC          , interface::Register::SOC          );
  debug_dumpSingleReg(debug_interface, flash, FOC          , interface::Register::FOC          );

  debug_dumpSingleReg(debug_interface, flash, TRIM_NVM_CTRL, interface::Register::TRIM_NVM_CTRL);

  debug_dumpSingleReg(debug_interface, flash, BGW_SPI3_WDT , interface::Register::BGW_SPI3_WDT );

  debug_dumpSingleReg(debug_interface, flash, OFC1         , interface::Register::OFC1         );
  debug_dumpSingleReg(debug_interface, flash, OFC2         , interface::Register::OFC2         );
  debug_dumpSingleReg(debug_interface, flash, OFC3         , interface::Register::OFC3         );
  debug_dumpSingleReg(debug_interface, flash, OFC4         , interface::Register::OFC4         );
  debug_dumpSingleReg(debug_interface, flash, TRIM_GP0     , interface::Register::TRIM_GP0     );
  debug_dumpSingleReg(debug_interface, flash, TRIM_GP1     , interface::Register::TRIM_GP1     );

  debug_dumpSingleReg(debug_interface, flash, BIST         , interface::Register::BIST         );

  debug_dumpSingleReg(debug_interface, flash, FIFO_CONFIG_0, interface::Register::FIFO_CONFIG_0);
  debug_dumpSingleReg(debug_interface, flash, FIFO_CONFIG_1, interface::Register::FIFO_CONFIG_1);
  debug_dumpSingleReg(debug_interface, flash, FIFO_DATA    , interface::Register::FIFO_DATA    );
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

void BMG160_Control::debug_dumpSingleReg(debug::interface::Debug & debug_interface, hal::interface::Flash & flash, char const * msg, interface::Register const reg)
{
  char    msg_ram[32];
  uint8_t reg_content = 0;

  flash.readStringFromFlash(msg_ram, msg);
  _io.readRegister(reg, &reg_content);

  debug_interface.print("%s%02X\n\r", msg_ram, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* BMG160 */

} /* sensor */

} /* driver */

} /* spectre */
