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

#include <spectre/driver/sensor/BMG160.h>

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
 * CTOR/DTOR
 **************************************************************************************/

BMG160::BMG160(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master)
: _i2c_address(i2c_address),
  _i2c_master (i2c_master )
{

}

BMG160::~BMG160()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool BMG160::setOutputDataRateAndBandwith(OutputDataRateAndBandwithSelect const sel)
{
  uint8_t bw_reg_content = 0;

  if(!readSingleRegister(REG_BW, &bw_reg_content)) return false;

  bw_reg_content &= ~(BMG160_BW_REG_ODR_2_bm | BMG160_BW_REG_ODR_1_bm | BMG160_BW_REG_ODR_0_bm);
  bw_reg_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_BW, bw_reg_content)) return false;

  return true;
}

bool BMG160::setFullScale(FullScaleSelect const sel)
{
  uint8_t range_content = 0;

  if(!readSingleRegister(REG_RANGE, &range_content)) return false;

  range_content &= ~(BMG160_RANGE_REG_FSR_2_bm | BMG160_RANGE_REG_FSR_1_bm | BMG160_RANGE_REG_FSR_0_bm);
  range_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_RANGE, range_content)) return false;

  return true;
}

bool BMG160::readXYZAxis(int16_t * raw_x, int16_t * raw_y, int16_t * raw_z)
{
  uint8_t raw_xyz_data[6];

  if(!readMultipleRegister(0x80 | REG_RATE_X_LSB, raw_xyz_data, 6)) return false;

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

bool BMG160::readXAxis(int16_t * raw_x)
{
  uint8_t raw_x_data[2];

  if(!readMultipleRegister(REG_RATE_X_LSB, raw_x_data, 2)) return false;

  uint8_t const x_l = raw_x_data[0];
  uint8_t const x_h = raw_x_data[1];

  *raw_x = static_cast<int16_t>((static_cast<uint16_t>(x_h) << 8) + (static_cast<uint16_t>(x_l)));

  return true;
}

bool BMG160::readYAxis(int16_t * raw_y)
{
  uint8_t raw_y_data[2];

  if(!readMultipleRegister(0x80 | REG_RATE_Y_LSB, raw_y_data, 2)) return false;

  uint8_t const y_l = raw_y_data[0];
  uint8_t const y_h = raw_y_data[1];

  *raw_y = static_cast<int16_t>((static_cast<uint16_t>(y_h) << 8) + (static_cast<uint16_t>(y_l)));

  return true;
}

bool BMG160::readZAxis(int16_t * raw_z)
{
  uint8_t raw_z_data[2];

  if(!readMultipleRegister(0x80 | REG_RATE_Z_LSB, raw_z_data, 2)) return false;

  uint8_t const z_l = raw_z_data[0];
  uint8_t const z_h = raw_z_data[1];

  *raw_z = static_cast<int16_t>((static_cast<uint16_t>(z_h) << 8) + (static_cast<uint16_t>(z_l)));

  return true;
}

bool BMG160::readTemperature(int8_t  * raw_temp)
{
  uint8_t temp_reg_content = 0;

  if(!readSingleRegister(REG_TEMP, &temp_reg_content)) return false;

  *raw_temp = static_cast<int8_t>(temp_reg_content);

  return true;
}

void BMG160::debug_dumpAllRegs(debug::interface::Debug & debug_interface)
{
  debug_dumpSingleReg(debug_interface, "REG_CHIP_ID       = ", REG_CHIP_ID      );

  debug_dumpSingleReg(debug_interface, "REG_RATE_X_LSB    = ", REG_RATE_X_LSB   );
  debug_dumpSingleReg(debug_interface, "REG_RATE_X_MSB    = ", REG_RATE_X_MSB   );
  debug_dumpSingleReg(debug_interface, "REG_RATE_Y_LSB    = ", REG_RATE_Y_LSB   );
  debug_dumpSingleReg(debug_interface, "REG_RATE_Y_MSB    = ", REG_RATE_Y_MSB   );
  debug_dumpSingleReg(debug_interface, "REG_RATE_Z_LSB    = ", REG_RATE_Z_LSB   );
  debug_dumpSingleReg(debug_interface, "REG_RATE_Z_MSB    = ", REG_RATE_Z_MSB   );

  debug_dumpSingleReg(debug_interface, "REG_INT_STATUS_0  = ", REG_INT_STATUS_0 );
  debug_dumpSingleReg(debug_interface, "REG_INT_STATUS_1  = ", REG_INT_STATUS_1 );
  debug_dumpSingleReg(debug_interface, "REG_INT_STATUS_2  = ", REG_INT_STATUS_2 );
  debug_dumpSingleReg(debug_interface, "REG_INT_STATUS_3  = ", REG_INT_STATUS_3 );
  debug_dumpSingleReg(debug_interface, "REG_FIFO_STATUS   = ", REG_FIFO_STATUS  );

  debug_dumpSingleReg(debug_interface, "REG_RANGE         = ", REG_RANGE        );
  debug_dumpSingleReg(debug_interface, "REG_BW            = ", REG_BW           );
  debug_dumpSingleReg(debug_interface, "REG_LPM1          = ", REG_LPM1         );
  debug_dumpSingleReg(debug_interface, "REG_LPM2          = ", REG_LPM2         );
  debug_dumpSingleReg(debug_interface, "REG_RATE_HBW      = ", REG_RATE_HBW     );
  debug_dumpSingleReg(debug_interface, "REG_BGW_SOFTRESET = ", REG_BGW_SOFTRESET);

  debug_dumpSingleReg(debug_interface, "REG_INT_EN_0      = ", REG_INT_EN_0     );
  debug_dumpSingleReg(debug_interface, "REG_INT_EN_1      = ", REG_INT_EN_1     );
  debug_dumpSingleReg(debug_interface, "REG_INT_MAP_0     = ", REG_INT_MAP_0    );
  debug_dumpSingleReg(debug_interface, "REG_INT_MAP_1     = ", REG_INT_MAP_1    );
  debug_dumpSingleReg(debug_interface, "REG_INT_MAP_2     = ", REG_INT_MAP_2    );
  debug_dumpSingleReg(debug_interface, "REG_INT_ZERO      = ", REG_INT_ZERO     );
  debug_dumpSingleReg(debug_interface, "REG_INT_ONE       = ", REG_INT_ONE      );
  debug_dumpSingleReg(debug_interface, "REG_INT_TWO       = ", REG_INT_TWO      );
  debug_dumpSingleReg(debug_interface, "REG_INT_FOUR      = ", REG_INT_FOUR     );
  debug_dumpSingleReg(debug_interface, "REG_INT_RST_LATCH = ", REG_INT_RST_LATCH);

  debug_dumpSingleReg(debug_interface, "REG_HIGH_TH_X     = ", REG_HIGH_TH_X    );
  debug_dumpSingleReg(debug_interface, "REG_HIGH_DUR_X    = ", REG_HIGH_DUR_X   );
  debug_dumpSingleReg(debug_interface, "REG_HIGH_TH_Y     = ", REG_HIGH_TH_Y    );
  debug_dumpSingleReg(debug_interface, "REG_HIGH_DUR_Y    = ", REG_HIGH_DUR_Y   );
  debug_dumpSingleReg(debug_interface, "REG_HIGH_TH_Z     = ", REG_HIGH_TH_Z    );
  debug_dumpSingleReg(debug_interface, "REG_HIGH_DUR_Z    = ", REG_HIGH_DUR_Z   );

  debug_dumpSingleReg(debug_interface, "REG_SOC           = ", REG_SOC          );
  debug_dumpSingleReg(debug_interface, "REG_FOC           = ", REG_FOC          );

  debug_dumpSingleReg(debug_interface, "REG_TRIM_NVM_CTRL = ", REG_TRIM_NVM_CTRL);

  debug_dumpSingleReg(debug_interface, "REG_BGW_SPI3_WDT  = ", REG_BGW_SPI3_WDT );

  debug_dumpSingleReg(debug_interface, "REG_OFC1          = ", REG_OFC1         );
  debug_dumpSingleReg(debug_interface, "REG_OFC2          = ", REG_OFC2         );
  debug_dumpSingleReg(debug_interface, "REG_OFC3          = ", REG_OFC3         );
  debug_dumpSingleReg(debug_interface, "REG_OFC4          = ", REG_OFC4         );
  debug_dumpSingleReg(debug_interface, "REG_TRIM_GP0      = ", REG_TRIM_GP0     );
  debug_dumpSingleReg(debug_interface, "REG_TRIM_GP1      = ", REG_TRIM_GP1     );

  debug_dumpSingleReg(debug_interface, "REG_BIST          = ", REG_BIST         );

  debug_dumpSingleReg(debug_interface, "REG_FIFO_CONFIG_0 = ", REG_FIFO_CONFIG_0);
  debug_dumpSingleReg(debug_interface, "REG_FIFO_CONFIG_1 = ", REG_FIFO_CONFIG_1);
  debug_dumpSingleReg(debug_interface, "REG_FIFO_DATA      = ", REG_FIFO_DATA   );
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

bool BMG160::readSingleRegister(uint8_t const reg_addr, uint8_t * data)
{
  return readMultipleRegister(reg_addr, data, 1);
}

bool BMG160::writeSingleRegister(uint8_t const reg_addr, uint8_t const data)
{
  if(!_i2c_master.begin(_i2c_address, false)) return false;
  if(!_i2c_master.write(reg_addr           )) return false;
  if(!_i2c_master.write(data               )) return false;
      _i2c_master.end  (                   );

  return true;
}

bool BMG160::readMultipleRegister(uint8_t const reg_addr, uint8_t * data, uint16_t const num_bytes)
{
  if(!_i2c_master.begin      (_i2c_address, false          )) return false;
  if(!_i2c_master.write      (reg_addr                     )) return false;
  if(!_i2c_master.requestFrom(_i2c_address, data, num_bytes)) return false;

  return true;
}

void BMG160::debug_dumpSingleReg(debug::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel)
{
  uint8_t reg_content = 0;

  readSingleRegister(reg_sel, &reg_content);

  debug_interface.print("%s%X\n", msg, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* BMG160 */

} /* sensor */

} /* driver */

} /* spectre */
