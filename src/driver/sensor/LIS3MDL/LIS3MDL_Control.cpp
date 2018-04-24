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

#include <spectre/driver/sensor/LIS3MDL/LIS3MDL_Control.h>

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
 * CONSTANTS
 **************************************************************************************/

FLASH_DECLARE(static char const WHO_AM_I  [] = "WHO_AM_I   = ");
FLASH_DECLARE(static char const CTRL_REG_1[] = "CTRL_REG_1 = ");
FLASH_DECLARE(static char const CTRL_REG_2[] = "CTRL_REG_2 = ");
FLASH_DECLARE(static char const CTRL_REG_3[] = "CTRL_REG_3 = ");
FLASH_DECLARE(static char const CTRL_REG_4[] = "CTRL_REG_4 = ");
FLASH_DECLARE(static char const CTRL_REG_5[] = "CTRL_REG_5 = ");
FLASH_DECLARE(static char const STATUS_REG[] = "STATUS_REG = ");
FLASH_DECLARE(static char const OUT_X_L   [] = "OUT_X_L    = ");
FLASH_DECLARE(static char const OUT_X_H   [] = "OUT_X_H    = ");
FLASH_DECLARE(static char const OUT_Y_L   [] = "OUT_Y_L    = ");
FLASH_DECLARE(static char const OUT_Y_H   [] = "OUT_Y_H    = ");
FLASH_DECLARE(static char const OUT_Z_L   [] = "OUT_Z_L    = ");
FLASH_DECLARE(static char const OUT_Z_H   [] = "OUT_Z_H    = ");
FLASH_DECLARE(static char const TEMP_OUT_L[] = "TEMP_OUT_L = ");
FLASH_DECLARE(static char const TEMP_OUT_H[] = "TEMP_OUT_H = ");
FLASH_DECLARE(static char const INT_CFG   [] = "INT_CFG    = ");
FLASH_DECLARE(static char const INT_SRC   [] = "INT_SRC    = ");
FLASH_DECLARE(static char const INT_THS_L [] = "INT_THS_L  = ");
FLASH_DECLARE(static char const INT_THS_H [] = "INT_THS_H  = ");

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

LIS3MDL_Control::LIS3MDL_Control(interface::LIS3MDL_Io & io)
: _io(io)
{
  enableTemperatureSensor();
  enableBlockDataUpdate  ();
}

LIS3MDL_Control::~LIS3MDL_Control()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool LIS3MDL_Control::checkIfNewDataIsAvailable_XYZ(bool * is_new_data_available_xyz)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_xyz = (status_reg_content & LIS3MDL_STATUS_REG_ZYXDA_bm) != 0;

  return true;
}

bool LIS3MDL_Control::checkIfNewDataIsAvailable_X(bool * is_new_data_available_x)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_x = (status_reg_content & LIS3MDL_STATUS_REG_XDA_bm) != 0;

  return true;
}

bool LIS3MDL_Control::checkIfNewDataIsAvailable_Y(bool * is_new_data_available_y)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_y = (status_reg_content & LIS3MDL_STATUS_REG_YDA_bm) != 0;

  return true;
}

bool LIS3MDL_Control::checkIfNewDataIsAvailable_Z(bool * is_new_data_available_z)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_z = (status_reg_content & LIS3MDL_STATUS_REG_ZDA_bm) != 0;

  return true;
}

bool LIS3MDL_Control::checkIfDataOverrun_XYZ(bool * is_data_overrun_xyz)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_xyz = (status_reg_content & LIS3MDL_STATUS_REG_ZYXOR_bm) != 0;

  return true;
}

bool LIS3MDL_Control::checkIfDataOverrun_X(bool * is_data_overrun_x)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_x = (status_reg_content & LIS3MDL_STATUS_REG_XOR_bm) != 0;

  return true;
}

bool LIS3MDL_Control::checkIfDataOverrun_Y(bool * is_data_overrun_y)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_y = (status_reg_content & LIS3MDL_STATUS_REG_YOR_bm) != 0;

  return true;
}

bool LIS3MDL_Control::checkIfDataOverrun_Z(bool * is_data_overrun_z)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_z = (status_reg_content & LIS3MDL_STATUS_REG_ZOR_bm) != 0;

  return true;
}

bool LIS3MDL_Control::readXYZAxis(int16_t * raw_x, int16_t * raw_y, int16_t * raw_z)
{
  uint8_t raw_xyz_data[6];

  if(!_io.readRegister(interface::Register::OUT_X_L, raw_xyz_data, 6)) return false;

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

bool LIS3MDL_Control::readXAxis(int16_t * raw_x)
{
  uint8_t raw_x_data[2];

  if(!_io.readRegister(interface::Register::OUT_X_L, raw_x_data, 2)) return false;

  uint8_t const x_l = raw_x_data[0];
  uint8_t const x_h = raw_x_data[1];

  *raw_x = static_cast<int16_t>((static_cast<uint16_t>(x_h) << 8) + (static_cast<uint16_t>(x_l)));

  return true;
}

bool LIS3MDL_Control::readYAxis(int16_t * raw_y)
{
  uint8_t raw_y_data[2];

  if(!_io.readRegister(interface::Register::OUT_Y_L, raw_y_data, 2)) return false;

  uint8_t const y_l = raw_y_data[0];
  uint8_t const y_h = raw_y_data[1];

  *raw_y = static_cast<int16_t>((static_cast<uint16_t>(y_h) << 8) + (static_cast<uint16_t>(y_l)));

  return true;
}

bool LIS3MDL_Control::readZAxis(int16_t * raw_z)
{
  uint8_t raw_z_data[2];

  if(!_io.readRegister(interface::Register::OUT_Z_L, raw_z_data, 2)) return false;

  uint8_t const z_l = raw_z_data[0];
  uint8_t const z_h = raw_z_data[1];

  *raw_z = static_cast<int16_t>((static_cast<uint16_t>(z_h) << 8) + (static_cast<uint16_t>(z_l)));

  return true;
}

bool LIS3MDL_Control::readTemperature(int16_t * raw_temp)
{
  uint8_t raw_temp_data[2];

  if(!_io.readRegister(interface::Register::TEMP_OUT_L, raw_temp_data, 2)) return false;

  uint8_t const temp_l = raw_temp_data[0];
  uint8_t const temp_h = raw_temp_data[1];

  *raw_temp = static_cast<int16_t>((static_cast<uint16_t>(temp_h) << 8) + (static_cast<uint16_t>(temp_l)));

  return true;
}

bool LIS3MDL_Control::setOperationMode_XY(interface::OperationMode_XY const operation_mode_xy)
{
  uint8_t ctrl_reg1_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG_1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content &= ~(LIS3MDL_CTRL_REG_1_OM_1_bm | LIS3MDL_CTRL_REG_1_OM_0_bm);
  ctrl_reg1_content |= static_cast<uint8_t>(operation_mode_xy);

  if(!_io.writeRegister(interface::Register::CTRL_REG_1, ctrl_reg1_content)) return false;

  return true;
}

bool LIS3MDL_Control::setOperationMode_Z(interface::OperationMode_Z const operation_mode_z)
{
  uint8_t ctrl_reg4_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG_4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content &= ~(LIS3MDL_CTRL_REG_4_OMZ_1_bm | LIS3MDL_CTRL_REG_4_OMZ_0_bm);
  ctrl_reg4_content |= static_cast<uint8_t>(operation_mode_z);

  if(!_io.writeRegister(interface::Register::CTRL_REG_4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS3MDL_Control::setOutputDataRate(interface::OutputDataRate const output_data_rate)
{
  uint8_t ctrl_reg1_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG_1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content &= ~(LIS3MDL_CTRL_REG_1_DO2_bm | LIS3MDL_CTRL_REG_1_DO1_bm | LIS3MDL_CTRL_REG_1_DO0_bm | LIS3MDL_CTRL_REG_1_FAST_ODR_bm);
  ctrl_reg1_content |= static_cast<uint8_t>(output_data_rate);

  if(!_io.writeRegister(interface::Register::CTRL_REG_1, ctrl_reg1_content)) return false;

  return true;
}

bool LIS3MDL_Control::setFullScaleRange(interface::FullScaleRange const full_scale_range)
{
  uint8_t ctrl_reg2_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG_2, &ctrl_reg2_content)) return false;

  ctrl_reg2_content &= ~(LIS3MDL_CTRL_REG_2_FS_1_bm | LIS3MDL_CTRL_REG_2_FS_0_bm);
  ctrl_reg2_content |= static_cast<uint8_t>(full_scale_range);

  if(!_io.writeRegister(interface::Register::CTRL_REG_2, ctrl_reg2_content)) return false;

  return true;
}

bool LIS3MDL_Control::setConversionMode(interface::ConversionMode const conversion_mode)
{
  uint8_t ctrl_reg3_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG_3, &ctrl_reg3_content)) return false;

  ctrl_reg3_content &= ~(LIS3MDL_CTRL_REG_3_MD_1_bm | LIS3MDL_CTRL_REG_3_MD_0_bm);
  ctrl_reg3_content |= static_cast<uint8_t>(conversion_mode);

  if(!_io.writeRegister(interface::Register::CTRL_REG_3, ctrl_reg3_content)) return false;

  return true;
}

bool LIS3MDL_Control::enableTemperatureSensor()
{
  uint8_t ctrl_reg1_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG_1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content |= LIS3MDL_CTRL_REG_1_TEMP_EN_bm;

  if(!_io.writeRegister(interface::Register::CTRL_REG_1, ctrl_reg1_content)) return false;

  return true;
}

bool LIS3MDL_Control::enableBlockDataUpdate()
{
  uint8_t ctrl_reg5_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG_5, &ctrl_reg5_content)) return false;

  ctrl_reg5_content |= LIS3MDL_CTRL_REG_5_BDU_bm;

  if(!_io.writeRegister(interface::Register::CTRL_REG_5, ctrl_reg5_content)) return false;

  return true;
}

void LIS3MDL_Control::debug_dumpAllRegs(debug::interface::Debug & debug_interface, hal::interface::Flash & flash)
{
  debug_dumpSingleReg(debug_interface, flash, WHO_AM_I  , interface::Register::WHO_AM_I  );
  debug_dumpSingleReg(debug_interface, flash, CTRL_REG_1, interface::Register::CTRL_REG_1);
  debug_dumpSingleReg(debug_interface, flash, CTRL_REG_2, interface::Register::CTRL_REG_2);
  debug_dumpSingleReg(debug_interface, flash, CTRL_REG_3, interface::Register::CTRL_REG_3);
  debug_dumpSingleReg(debug_interface, flash, CTRL_REG_4, interface::Register::CTRL_REG_4);
  debug_dumpSingleReg(debug_interface, flash, CTRL_REG_5, interface::Register::CTRL_REG_5);
  debug_dumpSingleReg(debug_interface, flash, STATUS_REG, interface::Register::STATUS_REG);
  debug_dumpSingleReg(debug_interface, flash, OUT_X_L   , interface::Register::OUT_X_L   );
  debug_dumpSingleReg(debug_interface, flash, OUT_X_H   , interface::Register::OUT_X_H   );
  debug_dumpSingleReg(debug_interface, flash, OUT_Y_L   , interface::Register::OUT_Y_L   );
  debug_dumpSingleReg(debug_interface, flash, OUT_Y_H   , interface::Register::OUT_Y_H   );
  debug_dumpSingleReg(debug_interface, flash, OUT_Z_L   , interface::Register::OUT_Z_L   );
  debug_dumpSingleReg(debug_interface, flash, OUT_Z_H   , interface::Register::OUT_Z_H   );
  debug_dumpSingleReg(debug_interface, flash, TEMP_OUT_L, interface::Register::TEMP_OUT_L);
  debug_dumpSingleReg(debug_interface, flash, TEMP_OUT_H, interface::Register::TEMP_OUT_H);
  debug_dumpSingleReg(debug_interface, flash, INT_CFG   , interface::Register::INT_CFG   );
  debug_dumpSingleReg(debug_interface, flash, INT_SRC   , interface::Register::INT_SRC   );
  debug_dumpSingleReg(debug_interface, flash, INT_THS_L , interface::Register::INT_THS_L );
  debug_dumpSingleReg(debug_interface, flash, INT_THS_H , interface::Register::INT_THS_H );
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

void LIS3MDL_Control::debug_dumpSingleReg(debug::interface::Debug & debug_interface, hal::interface::Flash & flash, char const * msg, interface::Register const reg)
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

} /* LIS3MDL */

} /* sensor */

} /* driver */

} /* spectre */
