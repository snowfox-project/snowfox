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

#include <spectre/driver/sensor/L3GD20.h>

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
 * CTOR/DTOR
 **************************************************************************************/

L3GD20::L3GD20(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master)
: _i2c_address(i2c_address),
  _i2c_master (_i2c_master)
{
  enablePower          ();
  disableAllAxis       ();
  enableBlockDataUpdate();
}

L3GD20::~L3GD20()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool L3GD20::setOutputDataRateAndBandwith(OutputDataRateAndBandwithSelect const sel)
{
  uint8_t ctrl_reg1_content = 0;

  if(!readSingleRegister(REG_CTRL_REG1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content &= ~(L3GD20_CTRL_REG1_DR1_bm | L3GD20_CTRL_REG1_DR0_bm | L3GD20_CTRL_REG1_BW1_bm | L3GD20_CTRL_REG1_BW0_bm);
  ctrl_reg1_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CTRL_REG1, ctrl_reg1_content)) return false;

  return true;
}

bool L3GD20::setFullScale(FullScaleSelect const sel)
{
  uint8_t ctrl_reg4_content = 0;

  if(!readSingleRegister(REG_CTRL_REG4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content &= ~(L3GD20_CTRL_REG4_FS1_bm | L3GD20_CTRL_REG4_FS0_bm);
  ctrl_reg4_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CTRL_REG4, ctrl_reg4_content)) return false;

  return true;
}

bool L3GD20::enableXYZAxis()
{
  uint8_t ctrl_reg1_content = 0;

  if(!readSingleRegister(REG_CTRL_REG1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content |= (L3GD20_CTRL_REG1_ZEN_bm | L3GD20_CTRL_REG1_YEN_bm | L3GD20_CTRL_REG1_XEN_bm);

  if(!writeSingleRegister(REG_CTRL_REG1, ctrl_reg1_content)) return false;

  return true;
}

bool L3GD20::enableXAxis()
{
  uint8_t ctrl_reg1_content = 0;

  if(!readSingleRegister(REG_CTRL_REG1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content |= (L3GD20_CTRL_REG1_XEN_bm);

  if(!writeSingleRegister(REG_CTRL_REG1, ctrl_reg1_content)) return false;

  return true;
}

bool L3GD20::enableYAxis()
{
  uint8_t ctrl_reg1_content = 0;

  if(!readSingleRegister(REG_CTRL_REG1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content |= (L3GD20_CTRL_REG1_YEN_bm);

  if(!writeSingleRegister(REG_CTRL_REG1, ctrl_reg1_content)) return false;

  return true;
}

bool L3GD20::enableZAxis()
{
  uint8_t ctrl_reg1_content = 0;

  if(!readSingleRegister(REG_CTRL_REG1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content |= (L3GD20_CTRL_REG1_ZEN_bm);

  if(!writeSingleRegister(REG_CTRL_REG1, ctrl_reg1_content)) return false;

  return true;
}

bool L3GD20::checkIfNewDataIsAvailable_XYZ(bool * is_new_data_available_xyz)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_xyz = (status_reg_content & L3GD20_STATUS_REG_ZYXDA_bm) != 0;

  return true;
}

bool L3GD20::checkIfNewDataIsAvailable_X(bool * is_new_data_available_x)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_x = (status_reg_content & L3GD20_STATUS_REG_XDA_bm) != 0;

  return true;
}

bool L3GD20::checkIfNewDataIsAvailable_Y(bool * is_new_data_available_y)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_y = (status_reg_content & L3GD20_STATUS_REG_YDA_bm) != 0;

  return true;
}

bool L3GD20::checkIfNewDataIsAvailable_Z(bool * is_new_data_available_z)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_z = (status_reg_content & L3GD20_STATUS_REG_ZDA_bm) != 0;

  return true;
}

bool L3GD20::checkIfDataOverrun_XYZ(bool * is_data_overrun_xyz)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_xyz = (status_reg_content & L3GD20_STATUS_REG_ZYXOR_bm) != 0;

  return true;
}

bool L3GD20::checkIfDataOverrun_X(bool * is_data_overrun_x)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_x = (status_reg_content & L3GD20_STATUS_REG_XOR_bm) != 0;

  return true;
}

bool L3GD20::checkIfDataOverrun_Y(bool * is_data_overrun_y)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_y = (status_reg_content & L3GD20_STATUS_REG_YOR_bm) != 0;

  return true;
}

bool L3GD20::checkIfDataOverrun_Z(bool * is_data_overrun_z)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_z = (status_reg_content & L3GD20_STATUS_REG_ZOR_bm) != 0;

  return true;
}

bool L3GD20::readXYZAxis(int16_t * raw_x, int16_t * raw_y, int16_t * raw_z)
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

bool L3GD20::readXAxis(int16_t * raw_x)
{
  uint8_t raw_x_data[2];

  if(!readMultipleRegister(REG_OUT_X_L, raw_x_data, 2)) return false;

  uint8_t const x_l = raw_x_data[0];
  uint8_t const x_h = raw_x_data[1];

  *raw_x = static_cast<int16_t>((static_cast<uint16_t>(x_h) << 8) + (static_cast<uint16_t>(x_l)));

  return true;
}

bool L3GD20::readYAxis(int16_t * raw_y)
{
  uint8_t raw_y_data[2];

  if(!readMultipleRegister(0x80 | REG_OUT_Y_L, raw_y_data, 2)) return false;

  uint8_t const y_l = raw_y_data[0];
  uint8_t const y_h = raw_y_data[1];

  *raw_y = static_cast<int16_t>((static_cast<uint16_t>(y_h) << 8) + (static_cast<uint16_t>(y_l)));

  return true;
}

bool L3GD20::readZAxis(int16_t * raw_z)
{
  uint8_t raw_z_data[2];

  if(!readMultipleRegister(0x80 | REG_OUT_Z_L, raw_z_data, 2)) return false;

  uint8_t const z_l = raw_z_data[0];
  uint8_t const z_h = raw_z_data[1];

  *raw_z = static_cast<int16_t>((static_cast<uint16_t>(z_h) << 8) + (static_cast<uint16_t>(z_l)));

  return true;
}

void L3GD20::debug_dumpAllRegs(driver::interface::Debug & debug_interface)
{
  debug_dumpSingleReg(debug_interface, "REG_WHO_AM_I      = ", REG_WHO_AM_I     );
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG1     = ", REG_CTRL_REG1    );
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG2     = ", REG_CTRL_REG2    );
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG3     = ", REG_CTRL_REG3    );
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG4     = ", REG_CTRL_REG4    );
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG5     = ", REG_CTRL_REG5    );
  debug_dumpSingleReg(debug_interface, "REG_REFERENCE     = ", REG_REFERENCE    );
  debug_dumpSingleReg(debug_interface, "REG_OUT_TEMP      = ", REG_OUT_TEMP     );
  debug_dumpSingleReg(debug_interface, "REG_STATUS_REG    = ", REG_STATUS_REG   );
  debug_dumpSingleReg(debug_interface, "REG_OUT_X_L       = ", REG_OUT_X_L      );
  debug_dumpSingleReg(debug_interface, "REG_OUT_X_H       = ", REG_OUT_X_H      );
  debug_dumpSingleReg(debug_interface, "REG_OUT_Y_L       = ", REG_OUT_Y_L      );
  debug_dumpSingleReg(debug_interface, "REG_OUT_Y_H       = ", REG_OUT_Y_H      );
  debug_dumpSingleReg(debug_interface, "REG_OUT_Z_L       = ", REG_OUT_Z_L      );
  debug_dumpSingleReg(debug_interface, "REG_OUT_Z_H       = ", REG_OUT_Z_H      );
  debug_dumpSingleReg(debug_interface, "REG_FIFO_CTRL_REG = ", REG_FIFO_CTRL_REG);
  debug_dumpSingleReg(debug_interface, "REG_FIFO_SRC_REG  = ", REG_FIFO_SRC_REG );
  debug_dumpSingleReg(debug_interface, "REG_INT1_CFG      = ", REG_INT1_CFG     );
  debug_dumpSingleReg(debug_interface, "REG_INT1_SRC      = ", REG_INT1_SRC     );
  debug_dumpSingleReg(debug_interface, "REG_TSH_XH        = ", REG_TSH_XH       );
  debug_dumpSingleReg(debug_interface, "REG_TSH_XH        = ", REG_TSH_XH       );
  debug_dumpSingleReg(debug_interface, "REG_TSH_XL        = ", REG_TSH_XL       );
  debug_dumpSingleReg(debug_interface, "REG_TSH_YH        = ", REG_TSH_YH       );
  debug_dumpSingleReg(debug_interface, "REG_TSH_YL        = ", REG_TSH_YL       );
  debug_dumpSingleReg(debug_interface, "REG_TSH_ZH        = ", REG_TSH_ZH       );
  debug_dumpSingleReg(debug_interface, "REG_TSH_ZL        = ", REG_TSH_ZL       );
  debug_dumpSingleReg(debug_interface, "REG_INT1_DURATION = ", REG_INT1_DURATION);
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

bool L3GD20::readSingleRegister(uint8_t const reg_addr, uint8_t * data)
{
  return readMultipleRegister(reg_addr, data, 1);
}

bool L3GD20::writeSingleRegister(uint8_t const reg_addr, uint8_t const data)
{
  if(!_i2c_master.begin(_i2c_address, false)) return false;
  if(!_i2c_master.write(reg_addr           )) return false;
  if(!_i2c_master.write(data               )) return false;
      _i2c_master.end  (                   );

  return true;
}

bool L3GD20::readMultipleRegister(uint8_t const reg_addr, uint8_t * data, uint16_t const num_bytes)
{
  if(!_i2c_master.begin      (_i2c_address, false          )) return false;
  if(!_i2c_master.write      (reg_addr                     )) return false;
  if(!_i2c_master.requestFrom(_i2c_address, data, num_bytes)) return false;

  return true;
}

bool L3GD20::enablePower()
{
  uint8_t ctrl_reg1_content = 0;

  if(!readSingleRegister(REG_CTRL_REG1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content |= L3GD20_CTRL_REG1_PD_bm;

  if(!writeSingleRegister(REG_CTRL_REG1, ctrl_reg1_content)) return false;

  return true;
}

bool L3GD20::disableAllAxis()
{
  uint8_t ctrl_reg1_content = 0;

  if(!readSingleRegister(REG_CTRL_REG1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content &= ~(L3GD20_STATUS_REG_ZDA_bm | L3GD20_STATUS_REG_YDA_bm | L3GD20_STATUS_REG_XDA_bm);

  if(!writeSingleRegister(REG_CTRL_REG1, ctrl_reg1_content)) return false;

  return true;
}

bool L3GD20::enableBlockDataUpdate()
{
  uint8_t ctrl_reg4_content = 0;

  if(!readSingleRegister(REG_CTRL_REG4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content |= L3GD20_CTRL_REG4_BDU_bm;

  if(!writeSingleRegister(REG_CTRL_REG4, ctrl_reg4_content)) return false;

  return true;
}

void L3GD20::debug_dumpSingleReg(driver::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel)
{
  uint8_t reg_content = 0;

  readSingleRegister(reg_sel, &reg_content);

  debug_interface.print("%s%X\n", msg, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* L3GD20 */

} /* sensor */

} /* driver */

} /* spectre */
