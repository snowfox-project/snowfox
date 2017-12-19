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

#include <spectre/driver/sensor/LIS3MDL.h>

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
 * CTOR/DTOR
 **************************************************************************************/

LIS3MDL::LIS3MDL(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master)
: _i2c_address(i2c_address),
  _i2c_master (_i2c_master)
{
  enableTemperatureSensor();
  enableBlockDataUpdate  ();
}

LIS3MDL::~LIS3MDL()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool LIS3MDL::checkIfNewDataIsAvailable_XYZ(bool * is_new_data_available_xyz)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_xyz = (status_reg_content & LIS3MDL_STATUS_REG_ZYXDA_bm) != 0;

  return true;
}

bool LIS3MDL::checkIfNewDataIsAvailable_X(bool * is_new_data_available_x)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_x = (status_reg_content & LIS3MDL_STATUS_REG_XDA_bm) != 0;

  return true;
}

bool LIS3MDL::checkIfNewDataIsAvailable_Y(bool * is_new_data_available_y)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_y = (status_reg_content & LIS3MDL_STATUS_REG_YDA_bm) != 0;

  return true;
}

bool LIS3MDL::checkIfNewDataIsAvailable_Z(bool * is_new_data_available_z)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_z = (status_reg_content & LIS3MDL_STATUS_REG_ZDA_bm) != 0;

  return true;
}

bool LIS3MDL::checkIfDataOverrun_XYZ(bool * is_data_overrun_xyz)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_xyz = (status_reg_content & LIS3MDL_STATUS_REG_ZYXOR_bm) != 0;

  return true;
}

bool LIS3MDL::checkIfDataOverrun_X(bool * is_data_overrun_x)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_x = (status_reg_content & LIS3MDL_STATUS_REG_XOR_bm) != 0;

  return true;
}

bool LIS3MDL::checkIfDataOverrun_Y(bool * is_data_overrun_y)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_y = (status_reg_content & LIS3MDL_STATUS_REG_YOR_bm) != 0;

  return true;
}

bool LIS3MDL::checkIfDataOverrun_Z(bool * is_data_overrun_z)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_z = (status_reg_content & LIS3MDL_STATUS_REG_ZOR_bm) != 0;

  return true;
}

bool LIS3MDL::readXYZAxis(int16_t * raw_x, int16_t * raw_y, int16_t * raw_z)
{
  uint8_t raw_xyz_data[6];

  if(!readMultipleRegister(0x80 | REG_OUT_X_L, raw_xyz_data, 6)) return false;

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

bool LIS3MDL::readXAxis(int16_t * raw_x)
{
  uint8_t raw_x_data[2];

  if(!readMultipleRegister(0x80 | REG_OUT_X_L, raw_x_data, 2)) return false;

  uint8_t const x_l = raw_x_data[0];
  uint8_t const x_h = raw_x_data[1];

  *raw_x = static_cast<int16_t>((static_cast<uint16_t>(x_h) << 8) + (static_cast<uint16_t>(x_l)));

  return true;
}

bool LIS3MDL::readYAxis(int16_t * raw_y)
{
  uint8_t raw_y_data[2];

  if(!readMultipleRegister(0x80 | REG_OUT_Y_L, raw_y_data, 2)) return false;

  uint8_t const y_l = raw_y_data[0];
  uint8_t const y_h = raw_y_data[1];

  *raw_y = static_cast<int16_t>((static_cast<uint16_t>(y_h) << 8) + (static_cast<uint16_t>(y_l)));

  return true;
}

bool LIS3MDL::readZAxis(int16_t * raw_z)
{
  uint8_t raw_z_data[2];

  if(!readMultipleRegister(0x80 | REG_OUT_Z_L, raw_z_data, 2)) return false;

  uint8_t const z_l = raw_z_data[0];
  uint8_t const z_h = raw_z_data[1];

  *raw_z = static_cast<int16_t>((static_cast<uint16_t>(z_h) << 8) + (static_cast<uint16_t>(z_l)));

  return true;
}

bool LIS3MDL::readTemperature(int16_t * raw_temp)
{
  uint8_t raw_temp_data[2];

  if(!readMultipleRegister(0x80 | REG_TEMP_OUT_L, raw_temp_data, 2)) return false;

  uint8_t const temp_l = raw_temp_data[0];
  uint8_t const temp_h = raw_temp_data[1];

  *raw_temp = static_cast<int16_t>((static_cast<uint16_t>(temp_h) << 8) + (static_cast<uint16_t>(temp_l)));

  return true;
}

bool LIS3MDL::setOperativeMode_XY(OperativeMode_XY const sel)
{
  uint8_t ctrl_reg1_content = 0;

  if(!readSingleRegister(REG_CTRL_REG_1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content &= ~(LIS3MDL_CTRL_REG_1_OM_1_bm | LIS3MDL_CTRL_REG_1_OM_0_bm);
  ctrl_reg1_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CTRL_REG_1, ctrl_reg1_content)) return false;

  return true;
}

bool LIS3MDL::setOperativeMode_Z(OperativeMode_Z const sel)
{
  uint8_t ctrl_reg4_content = 0;

  if(!readSingleRegister(REG_CTRL_REG_4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content &= ~(LIS3MDL_CTRL_REG_4_OMZ_1_bm | LIS3MDL_CTRL_REG_4_OMZ_0_bm);
  ctrl_reg4_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CTRL_REG_4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS3MDL::setOutputDataRate(OutputDataRateSelection const sel)
{
  uint8_t ctrl_reg1_content = 0;

  if(!readSingleRegister(REG_CTRL_REG_1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content &= ~(LIS3MDL_CTRL_REG_1_DO2_bm | LIS3MDL_CTRL_REG_1_DO1_bm | LIS3MDL_CTRL_REG_1_DO0_bm | LIS3MDL_CTRL_REG_1_FAST_ODR_bm);
  ctrl_reg1_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CTRL_REG_1, ctrl_reg1_content)) return false;

  return true;
}

bool LIS3MDL::setFullScale(FullScaleRangeSelect const sel)
{
  uint8_t ctrl_reg2_content = 0;

  if(!readSingleRegister(REG_CTRL_REG_2, &ctrl_reg2_content)) return false;

  ctrl_reg2_content &= ~(LIS3MDL_CTRL_REG_2_FS_1_bm | LIS3MDL_CTRL_REG_2_FS_0_bm);
  ctrl_reg2_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CTRL_REG_2, ctrl_reg2_content)) return false;

  return true;
}

bool LIS3MDL::setConversionMode(ConversionMode const sel)
{
  uint8_t ctrl_reg3_content = 0;

  if(!readSingleRegister(REG_CTRL_REG_3, &ctrl_reg3_content)) return false;

  ctrl_reg3_content &= ~(LIS3MDL_CTRL_REG_3_MD_1_bm | LIS3MDL_CTRL_REG_3_MD_0_bm);
  ctrl_reg3_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CTRL_REG_3, ctrl_reg3_content)) return false;

  return true;
}

bool LIS3MDL::enableTemperatureSensor()
{
  uint8_t ctrl_reg1_content = 0;

  if(!readSingleRegister(REG_CTRL_REG_1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content |= LIS3MDL_CTRL_REG_1_TEMP_EN_bm;

  if(!writeSingleRegister(REG_CTRL_REG_1, ctrl_reg1_content)) return false;

  return true;
}

bool LIS3MDL::enableBlockDataUpdate()
{
  uint8_t ctrl_reg5_content = 0;

  if(!readSingleRegister(REG_CTRL_REG_5, &ctrl_reg5_content)) return false;

  ctrl_reg5_content |= LIS3MDL_CTRL_REG_5_BDU_bm;

  if(!writeSingleRegister(REG_CTRL_REG_5, ctrl_reg5_content)) return false;

  return true;
}

void LIS3MDL::debug_dumpAllRegs(debug::interface::Debug & debug_interface)
{
  debug_dumpSingleReg(debug_interface, "REG_WHO_AM_I   = ", REG_WHO_AM_I  );
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG_1 = ", REG_CTRL_REG_1);
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG_2 = ", REG_CTRL_REG_2);
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG_3 = ", REG_CTRL_REG_3);
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG_4 = ", REG_CTRL_REG_4);
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG_5 = ", REG_CTRL_REG_5);
  debug_dumpSingleReg(debug_interface, "REG_STATUS_REG = ", REG_STATUS_REG);
  debug_dumpSingleReg(debug_interface, "REG_OUT_X_L    = ", REG_OUT_X_L   );
  debug_dumpSingleReg(debug_interface, "REG_OUT_X_H    = ", REG_OUT_X_H   );
  debug_dumpSingleReg(debug_interface, "REG_OUT_Y_L    = ", REG_OUT_Y_L   );
  debug_dumpSingleReg(debug_interface, "REG_OUT_Y_H    = ", REG_OUT_Y_H   );
  debug_dumpSingleReg(debug_interface, "REG_OUT_Z_L    = ", REG_OUT_Z_L   );
  debug_dumpSingleReg(debug_interface, "REG_OUT_Z_H    = ", REG_OUT_Z_H   );
  debug_dumpSingleReg(debug_interface, "REG_TEMP_OUT_L = ", REG_TEMP_OUT_L);
  debug_dumpSingleReg(debug_interface, "REG_TEMP_OUT_H = ", REG_TEMP_OUT_H);
  debug_dumpSingleReg(debug_interface, "REG_INT_CFG    = ", REG_INT_CFG   );
  debug_dumpSingleReg(debug_interface, "REG_INT_SRC    = ", REG_INT_SRC   );
  debug_dumpSingleReg(debug_interface, "REG_INT_THS_L  = ", REG_INT_THS_L );
  debug_dumpSingleReg(debug_interface, "REG_INT_THS_H  = ", REG_INT_THS_H );
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

bool LIS3MDL::readSingleRegister(uint8_t const reg_addr, uint8_t * data)
{
  return readMultipleRegister(reg_addr, data, 1);
}

bool LIS3MDL::writeSingleRegister(uint8_t const reg_addr, uint8_t const data)
{
  if(!_i2c_master.begin(_i2c_address, false)) return false;
  if(!_i2c_master.write(reg_addr           )) return false;
  if(!_i2c_master.write(data               )) return false;
      _i2c_master.end  (                   );

  return true;
}

bool LIS3MDL::readMultipleRegister(uint8_t const reg_addr, uint8_t * data, uint16_t const num_bytes)
{
  if(!_i2c_master.begin      (_i2c_address, false          )) return false;
  if(!_i2c_master.write      (reg_addr                     )) return false;
  if(!_i2c_master.requestFrom(_i2c_address, data, num_bytes)) return false;

  return true;
}

void LIS3MDL::debug_dumpSingleReg(debug::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel)
{
  uint8_t reg_content = 0;

  readSingleRegister(reg_sel, &reg_content);

  debug_interface.print("%s%X\n", msg, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS3MDL */

} /* sensor */

} /* driver */

} /* spectre */
