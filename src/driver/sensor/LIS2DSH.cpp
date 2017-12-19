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

#include <spectre/driver/sensor/LIS2DSH.h>

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
 * CTOR/DTOR
 **************************************************************************************/

LIS2DSH::LIS2DSH(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master)
: _i2c_address(i2c_address),
  _i2c_master (_i2c_master)
{
  enableBlockDataUpdate  ();
  enableTemperatureSensor();
}

LIS2DSH::~LIS2DSH()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool LIS2DSH::setOperatingMode(OperatingModeSelect const sel)
{
  uint8_t ctrl_reg1_content = 0,
          ctrl_reg4_content = 0;

  if(!readSingleRegister(REG_CTRL_REG1, &ctrl_reg1_content)) return false;
  if(!readSingleRegister(REG_CTRL_REG4, &ctrl_reg4_content)) return false;

  ctrl_reg1_content &= ~(LIS2DSH_CTRL_REG_1_LPEN_bm);
  ctrl_reg4_content &= ~(LIS2DSH_CTRL_REG_4_HR_bm);

  switch(sel)
  {
  case OM_8_Bit_Low_Power:
  {
    ctrl_reg1_content |= LIS2DSH_CTRL_REG_1_LPEN_bm;
  }
  break;
  case OM_10_Bit_Normal:
  {

  }
  break;
  case OM_12_Bit_High_Resolution:
  {
    ctrl_reg4_content |= LIS2DSH_CTRL_REG_4_HR_bm;
  }
  break;
  default: break;
  }

  if(!writeSingleRegister(REG_CTRL_REG1, ctrl_reg1_content)) return false;
  if(!writeSingleRegister(REG_CTRL_REG4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS2DSH::setOutputDataRate(OutputDataRateSelect const sel)
{
  uint8_t ctrl_reg1_content = 0;

  if(!readSingleRegister(REG_CTRL_REG1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content &=  ~(LIS2DSH_CTRL_REG_1_ODR_3_bm | LIS2DSH_CTRL_REG_1_ODR_2_bm | LIS2DSH_CTRL_REG_1_ODR_1_bm | LIS2DSH_CTRL_REG_1_ODR_0_bm);
  ctrl_reg1_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CTRL_REG1, ctrl_reg1_content)) return false;

  return true;
}

bool LIS2DSH::setFullScaleRange(FullScaleRangeSelect const sel)
{
  uint8_t ctrl_reg4_content = 0;

  if(!readSingleRegister(REG_CTRL_REG4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content &= ~(LIS2DSH_CTRL_REG_4_FS1_bm | LIS2DSH_CTRL_REG_4_FS0_bm);
  ctrl_reg4_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CTRL_REG4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS2DSH::setFIFOMode(FIFOModeSelect const sel)
{
  uint8_t fifo_ctrl_reg_content = 0;

  if(!readSingleRegister(REG_FIFO_CTRL_REG, &fifo_ctrl_reg_content)) return false;

  fifo_ctrl_reg_content &= ~(LIS2DSH_FIFO_CTRL_REG_FM1_bm | LIS2DSH_FIFO_CTRL_REG_FM0_bm);
  fifo_ctrl_reg_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_FIFO_CTRL_REG, fifo_ctrl_reg_content)) return false;

  return true;
}

bool LIS2DSH::enableFIFO()
{
  uint8_t ctrl_reg5_content = 0;

  if(!readSingleRegister(REG_CTRL_REG5, &ctrl_reg5_content)) return false;

  ctrl_reg5_content |= LIS2DSH_CTRL_REG_5_FIFO_EN_bm;

  if(!writeSingleRegister(REG_CTRL_REG5, ctrl_reg5_content)) return false;

  return true;
}

bool LIS2DSH::disableFIFO()
{
  uint8_t ctrl_reg5_content = 0;

  if(!readSingleRegister(REG_CTRL_REG5, &ctrl_reg5_content)) return false;

  ctrl_reg5_content &= ~LIS2DSH_CTRL_REG_5_FIFO_EN_bm;

  if(!writeSingleRegister(REG_CTRL_REG5, ctrl_reg5_content)) return false;

  return true;
}

bool LIS2DSH::enableBlockDataUpdate()
{
  uint8_t ctrl_reg4_content = 0;

  if(!readSingleRegister(REG_CTRL_REG4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content |= (LIS2DSH_CTRL_REG_4_BDU_bm);

  if(!writeSingleRegister(REG_CTRL_REG4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS2DSH::enableTemperatureSensor()
{
  uint8_t temp_cfg_reg_content = 0;

  if(!readSingleRegister(REG_TEMP_CFG_REG, &temp_cfg_reg_content)) return false;

  temp_cfg_reg_content |= (LIS2DSH_TEMP_CFG_REG_TEMP_EN_1_bm | LIS2DSH_TEMP_CFG_REG_TEMP_EN_0_bm);

  if(!writeSingleRegister(REG_TEMP_CFG_REG, temp_cfg_reg_content)) return false;

  return true;
}

bool LIS2DSH::enableXYZAxis()
{
  uint8_t ctrl_reg1_content = 0;

  if(!readSingleRegister(REG_CTRL_REG1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content |= (LIS2DSH_CTRL_REG_1_ZEN_bm | LIS2DSH_CTRL_REG_1_YEN_bm | LIS2DSH_CTRL_REG_1_XEN_bm);

  if(!writeSingleRegister(REG_CTRL_REG1, ctrl_reg1_content)) return false;

  return true;
}

bool LIS2DSH::enableXAxis()
{
  uint8_t ctrl_reg1_content = 0;

  if(!readSingleRegister(REG_CTRL_REG1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content |= (LIS2DSH_CTRL_REG_1_XEN_bm);

  if(!writeSingleRegister(REG_CTRL_REG1, ctrl_reg1_content)) return false;

  return true;
}

bool LIS2DSH::enableYAxis()
{
  uint8_t ctrl_reg1_content = 0;

  if(!readSingleRegister(REG_CTRL_REG1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content |= (LIS2DSH_CTRL_REG_1_YEN_bm);

  if(!writeSingleRegister(REG_CTRL_REG1, ctrl_reg1_content)) return false;

  return true;
}

bool LIS2DSH::enableZAxis()
{
  uint8_t ctrl_reg1_content = 0;

  if(!readSingleRegister(REG_CTRL_REG1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content |= (LIS2DSH_CTRL_REG_1_ZEN_bm);

  if(!writeSingleRegister(REG_CTRL_REG1, ctrl_reg1_content)) return false;

  return true;
}

bool LIS2DSH::checkIfNewDataIsAvailable_XYZ(bool * is_new_data_available_xyz)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_xyz = (status_reg_content & LIS2DSH_STATUS_REG_ZYXDA_bm) != 0;

  return true;
}

bool LIS2DSH::checkIfNewDataIsAvailable_X(bool * is_new_data_available_x)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_x = (status_reg_content & LIS2DSH_STATUS_REG_XDA_bm) != 0;

  return true;
}

bool LIS2DSH::checkIfNewDataIsAvailable_Y(bool * is_new_data_available_y)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_y = (status_reg_content & LIS2DSH_STATUS_REG_YDA_bm) != 0;

  return true;
}

bool LIS2DSH::checkIfNewDataIsAvailable_Z(bool * is_new_data_available_z)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_z = (status_reg_content & LIS2DSH_STATUS_REG_ZDA_bm) != 0;

  return true;
}

bool LIS2DSH::checkIfNewDataIsAvailable_Temperature(bool * is_new_data_available_temp)
{
  uint8_t status_aux_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG_AUX, &status_aux_reg_content)) return false;

  *is_new_data_available_temp = (status_aux_reg_content & LIS2DSH_STATUS_AUX_REG_TDA_bm) != 0;

  return true;
}

bool LIS2DSH::checkIfDataOverrun_XYZ(bool * is_data_overrun_xyz)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_xyz = (status_reg_content & LIS2DSH_STATUS_REG_ZYXOR_bm) != 0;

  return true;
}

bool LIS2DSH::checkIfDataOverrun_X(bool * is_data_overrun_x)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_x = (status_reg_content & LIS2DSH_STATUS_REG_XOR_bm) != 0;

  return true;
}

bool LIS2DSH::checkIfDataOverrun_Y(bool * is_data_overrun_y)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_y = (status_reg_content & LIS2DSH_STATUS_REG_YOR_bm) != 0;

  return true;
}

bool LIS2DSH::checkIfDataOverrun_Z(bool * is_data_overrun_z)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_z = (status_reg_content & LIS2DSH_STATUS_REG_ZOR_bm) != 0;

  return true;
}

bool LIS2DSH::checkIfDataOverrun_Temperature(bool * is_data_overrun_temp)
{
  uint8_t status_aux_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS_REG_AUX, &status_aux_reg_content)) return false;

  *is_data_overrun_temp = (status_aux_reg_content & LIS2DSH_STATUS_AUX_REG_TOR_bm) != 0;

  return true;
}

bool LIS2DSH::readXYZAxis(int16_t * raw_x, int16_t * raw_y, int16_t * raw_z)
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

bool LIS2DSH::readXAxis(int16_t * raw_x)
{
  uint8_t raw_x_data[2];

  if(!readMultipleRegister(0x80 | REG_OUT_X_L, raw_x_data, 2)) return false;

  uint8_t const x_l = raw_x_data[0];
  uint8_t const x_h = raw_x_data[1];

  *raw_x = static_cast<int16_t>((static_cast<uint16_t>(x_h) << 8) + (static_cast<uint16_t>(x_l)));

  return true;
}

bool LIS2DSH::readYAxis(int16_t * raw_y)
{
  uint8_t raw_y_data[2];

  if(!readMultipleRegister(0x80 | REG_OUT_Y_L, raw_y_data, 2)) return false;

  uint8_t const y_l = raw_y_data[0];
  uint8_t const y_h = raw_y_data[1];

  *raw_y = static_cast<int16_t>((static_cast<uint16_t>(y_h) << 8) + (static_cast<uint16_t>(y_l)));

  return true;
}

bool LIS2DSH::readZAxis(int16_t * raw_z)
{
  uint8_t raw_z_data[2];

  if(!readMultipleRegister(0x80 | REG_OUT_Z_L, raw_z_data, 2)) return false;

  uint8_t const z_l = raw_z_data[0];
  uint8_t const z_h = raw_z_data[1];

  *raw_z = static_cast<int16_t>((static_cast<uint16_t>(z_h) << 8) + (static_cast<uint16_t>(z_l)));

  return true;
}

bool LIS2DSH::readTemperature(int16_t * raw_temp)
{
  uint8_t raw_temp_data[2];

  if(!readMultipleRegister(0x80 | REG_OUT_TEMP_L, raw_temp_data, 2)) return false;

  uint8_t const temp_l = raw_temp_data[0];
  uint8_t const temp_h = raw_temp_data[1];

  *raw_temp = static_cast<int16_t>((static_cast<uint16_t>(temp_h) << 8) + (static_cast<uint16_t>(temp_l)));

  return true;
}

void LIS2DSH::debug_dumpAllRegs(debug::interface::Debug & debug_interface)
{
  debug_dumpSingleReg(debug_interface, "REG_STATUS_REG_AUX  = ", REG_STATUS_REG_AUX );

  debug_dumpSingleReg(debug_interface, "REG_OUT_TEMP_L      = ", REG_OUT_TEMP_L     );
  debug_dumpSingleReg(debug_interface, "REG_OUT_TEMP_H      = ", REG_OUT_TEMP_H     );

  debug_dumpSingleReg(debug_interface, "REG_INT_COUNTER_REG = ", REG_INT_COUNTER_REG);

  debug_dumpSingleReg(debug_interface, "REG_WHO_AM_I        = ", REG_WHO_AM_I       );

  debug_dumpSingleReg(debug_interface, "REG_TEMP_CFG_REG    = ", REG_TEMP_CFG_REG   );
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG1       = ", REG_CTRL_REG1      );
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG2       = ", REG_CTRL_REG2      );
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG3       = ", REG_CTRL_REG3      );
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG4       = ", REG_CTRL_REG4      );
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG5       = ", REG_CTRL_REG5      );
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG6       = ", REG_CTRL_REG6      );

  debug_dumpSingleReg(debug_interface, "REG_STATUS_REG      = ", REG_STATUS_REG    );

  debug_dumpSingleReg(debug_interface, "REG_OUT_X_L         = ", REG_OUT_X_L        );
  debug_dumpSingleReg(debug_interface, "REG_OUT_X_H         = ", REG_OUT_X_H        );
  debug_dumpSingleReg(debug_interface, "REG_OUT_Y_L         = ", REG_OUT_Y_L        );
  debug_dumpSingleReg(debug_interface, "REG_OUT_Y_H         = ", REG_OUT_Y_H        );
  debug_dumpSingleReg(debug_interface, "REG_OUT_Z_L         = ", REG_OUT_Z_L        );
  debug_dumpSingleReg(debug_interface, "REG_OUT_Z_H         = ", REG_OUT_Z_H        );

  debug_dumpSingleReg(debug_interface, "REG_FIFO_CTRL_REG   = ", REG_FIFO_CTRL_REG  );
  debug_dumpSingleReg(debug_interface, "REG_FIFO_SRC_REG    = ", REG_FIFO_SRC_REG   );

  debug_dumpSingleReg(debug_interface, "REG_INT1_CFG        = ", REG_INT1_CFG       );
  debug_dumpSingleReg(debug_interface, "REG_INT1_SOURCE     = ", REG_INT1_SOURCE    );
  debug_dumpSingleReg(debug_interface, "REG_INT1_THS        = ", REG_INT1_THS       );
  debug_dumpSingleReg(debug_interface, "REG_INT1_DURATION   = ", REG_INT1_DURATION  );

  debug_dumpSingleReg(debug_interface, "REG_INT2_CFG        = ", REG_INT2_CFG       );
  debug_dumpSingleReg(debug_interface, "REG_INT2_SOURCE     = ", REG_INT2_SOURCE    );
  debug_dumpSingleReg(debug_interface, "REG_INT2_THS        = ", REG_INT2_THS       );
  debug_dumpSingleReg(debug_interface, "REG_INT2_DURATION   = ", REG_INT2_DURATION  );

  debug_dumpSingleReg(debug_interface, "REG_CLICK_CFG       = ", REG_CLICK_CFG      );
  debug_dumpSingleReg(debug_interface, "REG_CLICK_SRC       = ", REG_CLICK_SRC      );
  debug_dumpSingleReg(debug_interface, "REG_CLICK_THS       = ", REG_CLICK_THS      );

  debug_dumpSingleReg(debug_interface, "REG_TIME_LIMIT      = ", REG_TIME_LIMIT     );
  debug_dumpSingleReg(debug_interface, "REG_TIME_LATENCY    = ", REG_TIME_LATENCY   );
  debug_dumpSingleReg(debug_interface, "REG_TIME_WINDOW     = ", REG_TIME_WINDOW    );

  debug_dumpSingleReg(debug_interface, "REG_ACT_THS         = ", REG_ACT_THS        );
  debug_dumpSingleReg(debug_interface, "REG_ACT_DUR         = ", REG_ACT_DUR        );
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

bool LIS2DSH::readSingleRegister(uint8_t const reg_addr, uint8_t * data)
{
  return readMultipleRegister(reg_addr, data, 1);
}

bool LIS2DSH::writeSingleRegister(uint8_t const reg_addr, uint8_t const data)
{
  if(!_i2c_master.begin(_i2c_address, false)) return false;
  if(!_i2c_master.write(reg_addr           )) return false;
  if(!_i2c_master.write(data               )) return false;
      _i2c_master.end  (                   );

  return true;
}

bool LIS2DSH::readMultipleRegister(uint8_t const reg_addr, uint8_t * data, uint16_t const num_bytes)
{
  if(!_i2c_master.begin      (_i2c_address, false          )) return false;
  if(!_i2c_master.write      (reg_addr                     )) return false;
  if(!_i2c_master.requestFrom(_i2c_address, data, num_bytes)) return false;

  return true;
}

void LIS2DSH::debug_dumpSingleReg(debug::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel)
{
  uint8_t reg_content = 0;

  readSingleRegister(reg_sel, &reg_content);

  debug_interface.print("%s%X\n", msg, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS2DSH */

} /* sensor */

} /* driver */

} /* spectre */
