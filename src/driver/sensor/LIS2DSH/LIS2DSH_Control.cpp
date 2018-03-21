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

#include <spectre/driver/sensor/LIS2DSH/LIS2DSH_Control.h>

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

LIS2DSH_Control::LIS2DSH_Control(interface::LIS2DSH_Io & io)
: _io(io)
{
  enableBlockDataUpdate  ();
  enableTemperatureSensor();
}

LIS2DSH_Control::~LIS2DSH_Control()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool LIS2DSH_Control::setOperatingMode(interface::OperatingMode const operating_mode)
{
  uint8_t ctrl_reg1_content = 0,
          ctrl_reg4_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG1, &ctrl_reg1_content)) return false;
  if(!_io.readRegister(interface::Register::CTRL_REG4, &ctrl_reg4_content)) return false;

  ctrl_reg1_content &= ~(LIS2DSH_CTRL_REG_1_LPEN_bm);
  ctrl_reg4_content &= ~(LIS2DSH_CTRL_REG_4_HR_bm);

  switch(operating_mode)
  {
  case interface::OperatingMode::OM_8_Bit_Low_Power       : ctrl_reg1_content |= LIS2DSH_CTRL_REG_1_LPEN_bm; break;
  case interface::OperatingMode::OM_10_Bit_Normal         :                                                  break;
  case interface::OperatingMode::OM_12_Bit_High_Resolution: ctrl_reg4_content |= LIS2DSH_CTRL_REG_4_HR_bm;   break;
  default                                                 :                                                  break;
  }

  if(!_io.writeRegister(interface::Register::CTRL_REG1, ctrl_reg1_content)) return false;
  if(!_io.writeRegister(interface::Register::CTRL_REG4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS2DSH_Control::setOutputDataRate(interface::OutputDataRate const output_data_rate)
{
  uint8_t ctrl_reg1_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content &=  ~(LIS2DSH_CTRL_REG_1_ODR_3_bm | LIS2DSH_CTRL_REG_1_ODR_2_bm | LIS2DSH_CTRL_REG_1_ODR_1_bm | LIS2DSH_CTRL_REG_1_ODR_0_bm);
  ctrl_reg1_content |= static_cast<uint8_t>(output_data_rate);

  if(!_io.writeRegister(interface::Register::CTRL_REG1, ctrl_reg1_content)) return false;

  return true;
}

bool LIS2DSH_Control::setFullScaleRange(interface::FullScaleRange const full_scale_range)
{
  uint8_t ctrl_reg4_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content &= ~(LIS2DSH_CTRL_REG_4_FS1_bm | LIS2DSH_CTRL_REG_4_FS0_bm);
  ctrl_reg4_content |= static_cast<uint8_t>(full_scale_range);

  if(!_io.writeRegister(interface::Register::CTRL_REG4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS2DSH_Control::setFifoMode(interface::FifoMode const fifo_mode)
{
  uint8_t fifo_ctrl_reg_content = 0;

  if(!_io.readRegister(interface::Register::FIFO_CTRL_REG, &fifo_ctrl_reg_content)) return false;

  fifo_ctrl_reg_content &= ~(LIS2DSH_FIFO_CTRL_REG_FM1_bm | LIS2DSH_FIFO_CTRL_REG_FM0_bm);
  fifo_ctrl_reg_content |= static_cast<uint8_t>(fifo_mode);

  if(!_io.writeRegister(interface::Register::FIFO_CTRL_REG, fifo_ctrl_reg_content)) return false;

  return true;
}

bool LIS2DSH_Control::enableFIFO()
{
  uint8_t ctrl_reg5_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG5, &ctrl_reg5_content)) return false;

  ctrl_reg5_content |= LIS2DSH_CTRL_REG_5_FIFO_EN_bm;

  if(!_io.writeRegister(interface::Register::CTRL_REG5, ctrl_reg5_content)) return false;

  return true;
}

bool LIS2DSH_Control::disableFIFO()
{
  uint8_t ctrl_reg5_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG5, &ctrl_reg5_content)) return false;

  ctrl_reg5_content &= ~LIS2DSH_CTRL_REG_5_FIFO_EN_bm;

  if(!_io.writeRegister(interface::Register::CTRL_REG5, ctrl_reg5_content)) return false;

  return true;
}

bool LIS2DSH_Control::enableBlockDataUpdate()
{
  uint8_t ctrl_reg4_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content |= (LIS2DSH_CTRL_REG_4_BDU_bm);

  if(!_io.writeRegister(interface::Register::CTRL_REG4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS2DSH_Control::enableTemperatureSensor()
{
  uint8_t temp_cfg_reg_content = 0;

  if(!_io.readRegister(interface::Register::TEMP_CFG_REG, &temp_cfg_reg_content)) return false;

  temp_cfg_reg_content |= (LIS2DSH_TEMP_CFG_REG_TEMP_EN_1_bm | LIS2DSH_TEMP_CFG_REG_TEMP_EN_0_bm);

  if(!_io.writeRegister(interface::Register::TEMP_CFG_REG, temp_cfg_reg_content)) return false;

  return true;
}

bool LIS2DSH_Control::enableXYZAxis()
{
  uint8_t ctrl_reg1_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content |= (LIS2DSH_CTRL_REG_1_ZEN_bm | LIS2DSH_CTRL_REG_1_YEN_bm | LIS2DSH_CTRL_REG_1_XEN_bm);

  if(!_io.writeRegister(interface::Register::CTRL_REG1, ctrl_reg1_content)) return false;

  return true;
}

bool LIS2DSH_Control::enableXAxis()
{
  uint8_t ctrl_reg1_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content |= (LIS2DSH_CTRL_REG_1_XEN_bm);

  if(!_io.writeRegister(interface::Register::CTRL_REG1, ctrl_reg1_content)) return false;

  return true;
}

bool LIS2DSH_Control::enableYAxis()
{
  uint8_t ctrl_reg1_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content |= (LIS2DSH_CTRL_REG_1_YEN_bm);

  if(!_io.writeRegister(interface::Register::CTRL_REG1, ctrl_reg1_content)) return false;

  return true;
}

bool LIS2DSH_Control::enableZAxis()
{
  uint8_t ctrl_reg1_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG1, &ctrl_reg1_content)) return false;

  ctrl_reg1_content |= (LIS2DSH_CTRL_REG_1_ZEN_bm);

  if(!_io.writeRegister(interface::Register::CTRL_REG1, ctrl_reg1_content)) return false;

  return true;
}

bool LIS2DSH_Control::checkIfNewDataIsAvailable_XYZ(bool * is_new_data_available_xyz)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_xyz = (status_reg_content & LIS2DSH_STATUS_REG_ZYXDA_bm) != 0;

  return true;
}

bool LIS2DSH_Control::checkIfNewDataIsAvailable_X(bool * is_new_data_available_x)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_x = (status_reg_content & LIS2DSH_STATUS_REG_XDA_bm) != 0;

  return true;
}

bool LIS2DSH_Control::checkIfNewDataIsAvailable_Y(bool * is_new_data_available_y)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_y = (status_reg_content & LIS2DSH_STATUS_REG_YDA_bm) != 0;

  return true;
}

bool LIS2DSH_Control::checkIfNewDataIsAvailable_Z(bool * is_new_data_available_z)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG, &status_reg_content)) return false;

  *is_new_data_available_z = (status_reg_content & LIS2DSH_STATUS_REG_ZDA_bm) != 0;

  return true;
}

bool LIS2DSH_Control::checkIfNewDataIsAvailable_Temperature(bool * is_new_data_available_temp)
{
  uint8_t status_aux_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG_AUX, &status_aux_reg_content)) return false;

  *is_new_data_available_temp = (status_aux_reg_content & LIS2DSH_STATUS_AUX_REG_TDA_bm) != 0;

  return true;
}

bool LIS2DSH_Control::checkIfDataOverrun_XYZ(bool * is_data_overrun_xyz)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_xyz = (status_reg_content & LIS2DSH_STATUS_REG_ZYXOR_bm) != 0;

  return true;
}

bool LIS2DSH_Control::checkIfDataOverrun_X(bool * is_data_overrun_x)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_x = (status_reg_content & LIS2DSH_STATUS_REG_XOR_bm) != 0;

  return true;
}

bool LIS2DSH_Control::checkIfDataOverrun_Y(bool * is_data_overrun_y)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_y = (status_reg_content & LIS2DSH_STATUS_REG_YOR_bm) != 0;

  return true;
}

bool LIS2DSH_Control::checkIfDataOverrun_Z(bool * is_data_overrun_z)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG, &status_reg_content)) return false;

  *is_data_overrun_z = (status_reg_content & LIS2DSH_STATUS_REG_ZOR_bm) != 0;

  return true;
}

bool LIS2DSH_Control::checkIfDataOverrun_Temperature(bool * is_data_overrun_temp)
{
  uint8_t status_aux_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS_REG_AUX, &status_aux_reg_content)) return false;

  *is_data_overrun_temp = (status_aux_reg_content & LIS2DSH_STATUS_AUX_REG_TOR_bm) != 0;

  return true;
}

bool LIS2DSH_Control::readXYZAxis(int16_t * raw_x, int16_t * raw_y, int16_t * raw_z)
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

bool LIS2DSH_Control::readXAxis(int16_t * raw_x)
{
  uint8_t raw_x_data[2];

  if(!_io.readRegister(interface::Register::OUT_X_L, raw_x_data, 2)) return false;

  uint8_t const x_l = raw_x_data[0];
  uint8_t const x_h = raw_x_data[1];

  *raw_x = static_cast<int16_t>((static_cast<uint16_t>(x_h) << 8) + (static_cast<uint16_t>(x_l)));

  return true;
}

bool LIS2DSH_Control::readYAxis(int16_t * raw_y)
{
  uint8_t raw_y_data[2];

  if(!_io.readRegister(interface::Register::OUT_Y_L, raw_y_data, 2)) return false;

  uint8_t const y_l = raw_y_data[0];
  uint8_t const y_h = raw_y_data[1];

  *raw_y = static_cast<int16_t>((static_cast<uint16_t>(y_h) << 8) + (static_cast<uint16_t>(y_l)));

  return true;
}

bool LIS2DSH_Control::readZAxis(int16_t * raw_z)
{
  uint8_t raw_z_data[2];

  if(!_io.readRegister(interface::Register::OUT_Z_L, raw_z_data, 2)) return false;

  uint8_t const z_l = raw_z_data[0];
  uint8_t const z_h = raw_z_data[1];

  *raw_z = static_cast<int16_t>((static_cast<uint16_t>(z_h) << 8) + (static_cast<uint16_t>(z_l)));

  return true;
}

bool LIS2DSH_Control::readTemperature(int16_t * raw_temp)
{
  uint8_t raw_temp_data[2];

  if(!_io.readRegister(interface::Register::OUT_TEMP_L, raw_temp_data, 2)) return false;

  uint8_t const temp_l = raw_temp_data[0];
  uint8_t const temp_h = raw_temp_data[1];

  *raw_temp = static_cast<int16_t>((static_cast<uint16_t>(temp_h) << 8) + (static_cast<uint16_t>(temp_l)));

  return true;
}

void LIS2DSH_Control::debug_dumpAllRegs(debug::interface::Debug & debug_interface)
{
  debug_dumpSingleReg(debug_interface, "STATUS_REG_AUX  = ", interface::Register::STATUS_REG_AUX );

  debug_dumpSingleReg(debug_interface, "OUT_TEMP_L      = ", interface::Register::OUT_TEMP_L     );
  debug_dumpSingleReg(debug_interface, "OUT_TEMP_H      = ", interface::Register::OUT_TEMP_H     );

  debug_dumpSingleReg(debug_interface, "INT_COUNTER_REG = ", interface::Register::INT_COUNTER_REG);

  debug_dumpSingleReg(debug_interface, "WHO_AM_I        = ", interface::Register::WHO_AM_I       );

  debug_dumpSingleReg(debug_interface, "TEMP_CFG_REG    = ", interface::Register::TEMP_CFG_REG   );
  debug_dumpSingleReg(debug_interface, "CTRL_REG1       = ", interface::Register::CTRL_REG1      );
  debug_dumpSingleReg(debug_interface, "CTRL_REG2       = ", interface::Register::CTRL_REG2      );
  debug_dumpSingleReg(debug_interface, "CTRL_REG3       = ", interface::Register::CTRL_REG3      );
  debug_dumpSingleReg(debug_interface, "CTRL_REG4       = ", interface::Register::CTRL_REG4      );
  debug_dumpSingleReg(debug_interface, "CTRL_REG5       = ", interface::Register::CTRL_REG5      );
  debug_dumpSingleReg(debug_interface, "CTRL_REG6       = ", interface::Register::CTRL_REG6      );

  debug_dumpSingleReg(debug_interface, "STATUS_REG      = ", interface::Register::STATUS_REG    );

  debug_dumpSingleReg(debug_interface, "OUT_X_L         = ", interface::Register::OUT_X_L        );
  debug_dumpSingleReg(debug_interface, "OUT_X_H         = ", interface::Register::OUT_X_H        );
  debug_dumpSingleReg(debug_interface, "OUT_Y_L         = ", interface::Register::OUT_Y_L        );
  debug_dumpSingleReg(debug_interface, "OUT_Y_H         = ", interface::Register::OUT_Y_H        );
  debug_dumpSingleReg(debug_interface, "OUT_Z_L         = ", interface::Register::OUT_Z_L        );
  debug_dumpSingleReg(debug_interface, "OUT_Z_H         = ", interface::Register::OUT_Z_H        );

  debug_dumpSingleReg(debug_interface, "FIFO_CTRL_REG   = ", interface::Register::FIFO_CTRL_REG  );
  debug_dumpSingleReg(debug_interface, "FIFO_SRC_REG    = ", interface::Register::FIFO_SRC_REG   );

  debug_dumpSingleReg(debug_interface, "INT1_CFG        = ", interface::Register::INT1_CFG       );
  debug_dumpSingleReg(debug_interface, "INT1_SOURCE     = ", interface::Register::INT1_SOURCE    );
  debug_dumpSingleReg(debug_interface, "INT1_THS        = ", interface::Register::INT1_THS       );
  debug_dumpSingleReg(debug_interface, "INT1_DURATION   = ", interface::Register::INT1_DURATION  );

  debug_dumpSingleReg(debug_interface, "INT2_CFG        = ", interface::Register::INT2_CFG       );
  debug_dumpSingleReg(debug_interface, "INT2_SOURCE     = ", interface::Register::INT2_SOURCE    );
  debug_dumpSingleReg(debug_interface, "INT2_THS        = ", interface::Register::INT2_THS       );
  debug_dumpSingleReg(debug_interface, "INT2_DURATION   = ", interface::Register::INT2_DURATION  );

  debug_dumpSingleReg(debug_interface, "CLICK_CFG       = ", interface::Register::CLICK_CFG      );
  debug_dumpSingleReg(debug_interface, "CLICK_SRC       = ", interface::Register::CLICK_SRC      );
  debug_dumpSingleReg(debug_interface, "CLICK_THS       = ", interface::Register::CLICK_THS      );

  debug_dumpSingleReg(debug_interface, "TIME_LIMIT      = ", interface::Register::TIME_LIMIT     );
  debug_dumpSingleReg(debug_interface, "TIME_LATENCY    = ", interface::Register::TIME_LATENCY   );
  debug_dumpSingleReg(debug_interface, "TIME_WINDOW     = ", interface::Register::TIME_WINDOW    );

  debug_dumpSingleReg(debug_interface, "ACT_THS         = ", interface::Register::ACT_THS        );
  debug_dumpSingleReg(debug_interface, "ACT_DUR         = ", interface::Register::ACT_DUR        );
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

void LIS2DSH_Control::debug_dumpSingleReg(debug::interface::Debug & debug_interface, char const * msg, interface::Register const reg)
{
  uint8_t reg_content = 0;

  _io.readRegister(reg, &reg_content);

  debug_interface.print("%s%X\n", msg, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS2DSH */

} /* sensor */

} /* driver */

} /* spectre */
