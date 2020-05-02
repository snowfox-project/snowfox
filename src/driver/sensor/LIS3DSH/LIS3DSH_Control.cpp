/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#include <snowfox/driver/sensor/LIS3DSH/LIS3DSH_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensorLIS3DSH
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

LIS3DSH_Control::LIS3DSH_Control(interface::LIS3DSH_Io & io)
: _io(io)
{
  enableBlockDataUpdate();
}

LIS3DSH_Control::~LIS3DSH_Control()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool LIS3DSH_Control::setOutputDataRate(interface::OutputDataRate const output_data_rate)
{
  uint8_t ctrl_reg4_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG_4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content &= ~(LIS3DSH_CTRL_REG_4_ODR_3_bm | LIS3DSH_CTRL_REG_4_ODR_2_bm | LIS3DSH_CTRL_REG_4_ODR_1_bm | LIS3DSH_CTRL_REG_4_ODR_0_bm);
  ctrl_reg4_content |= static_cast<uint8_t>(output_data_rate);

  if(!_io.writeRegister(interface::Register::CTRL_REG_4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS3DSH_Control::setFullScaleRange(interface::FullScaleRange const full_scale_range)
{
  uint8_t ctrl_reg5_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG_5, &ctrl_reg5_content)) return false;

  ctrl_reg5_content &= ~(LIS3DSH_CTRL_REG_5_FSCALE_2_bm | LIS3DSH_CTRL_REG_5_FSCALE_1_bm | LIS3DSH_CTRL_REG_5_FSCALE_0_bm);
  ctrl_reg5_content |= static_cast<uint8_t>(full_scale_range);

  if(!_io.writeRegister(interface::Register::CTRL_REG_5, ctrl_reg5_content)) return false;

  return true;
}

bool LIS3DSH_Control::setFilterBandwidth(interface::FilterBandwidth const filter_bandwidth)
{
  uint8_t ctrl_reg5_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG_5, &ctrl_reg5_content)) return false;

  ctrl_reg5_content &= ~(LIS3DSH_CTRL_REG_5_BW_2_bm | LIS3DSH_CTRL_REG_5_BW_1_bm);
  ctrl_reg5_content |= static_cast<uint8_t>(filter_bandwidth);

  if(!_io.writeRegister(interface::Register::CTRL_REG_5, ctrl_reg5_content)) return false;

  return true;
}

bool LIS3DSH_Control::enableFIFO()
{
  uint8_t ctrl_reg6_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG_6, &ctrl_reg6_content)) return false;

  ctrl_reg6_content |= LIS3DSH_CTRL_REG_6_FIFO_EN_bm;

  if(!_io.writeRegister(interface::Register::CTRL_REG_6, ctrl_reg6_content)) return false;

  return true;
}

bool LIS3DSH_Control::disableFIFO()
{
  uint8_t ctrl_reg6_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG_6, &ctrl_reg6_content)) return false;

  ctrl_reg6_content &= ~LIS3DSH_CTRL_REG_6_FIFO_EN_bm;

  if(!_io.writeRegister(interface::Register::CTRL_REG_6, ctrl_reg6_content)) return false;

  return true;
}

bool LIS3DSH_Control::enableBlockDataUpdate()
{
  uint8_t ctrl_reg4_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG_4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content |= LIS3DSH_CTRL_REG_4_BDU_bm;

  if(!_io.writeRegister(interface::Register::CTRL_REG_4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS3DSH_Control::enableXYZAxis()
{
  uint8_t ctrl_reg4_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG_4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content |= (LIS3DSH_CTRL_REG_4_ZEN_bm | LIS3DSH_CTRL_REG_4_YEN_bm | LIS3DSH_CTRL_REG_4_XEN_bm);

  if(!_io.writeRegister(interface::Register::CTRL_REG_4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS3DSH_Control::enableXAxis()
{
  uint8_t ctrl_reg4_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG_4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content |= (LIS3DSH_CTRL_REG_4_XEN_bm);

  if(!_io.writeRegister(interface::Register::CTRL_REG_4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS3DSH_Control::enableYAxis()
{
  uint8_t ctrl_reg4_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG_4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content |= (LIS3DSH_CTRL_REG_4_YEN_bm);

  if(!_io.writeRegister(interface::Register::CTRL_REG_4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS3DSH_Control::enableZAxis()
{
  uint8_t ctrl_reg4_content = 0;

  if(!_io.readRegister(interface::Register::CTRL_REG_4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content |= (LIS3DSH_CTRL_REG_4_ZEN_bm);

  if(!_io.writeRegister(interface::Register::CTRL_REG_4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS3DSH_Control::checkIfNewDataIsAvailable_XYZ(bool * is_new_data_available_xyz)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS, &status_reg_content)) return false;

  *is_new_data_available_xyz = (status_reg_content & LIS3DSH_STATUS_REG_ZYXDA_bm) != 0;

  return true;
}

bool LIS3DSH_Control::checkIfNewDataIsAvailable_X(bool * is_new_data_available_x)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS, &status_reg_content)) return false;

  *is_new_data_available_x = (status_reg_content & LIS3DSH_STATUS_REG_XDA_bm) != 0;

  return true;
}

bool LIS3DSH_Control::checkIfNewDataIsAvailable_Y(bool * is_new_data_available_y)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS, &status_reg_content)) return false;

  *is_new_data_available_y = (status_reg_content & LIS3DSH_STATUS_REG_YDA_bm) != 0;

  return true;
}

bool LIS3DSH_Control::checkIfNewDataIsAvailable_Z(bool * is_new_data_available_z)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS, &status_reg_content)) return false;

  *is_new_data_available_z = (status_reg_content & LIS3DSH_STATUS_REG_ZDA_bm) != 0;

  return true;
}

bool LIS3DSH_Control::checkIfDataOverrun_XYZ(bool * is_data_overrun_xyz)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS, &status_reg_content)) return false;

  *is_data_overrun_xyz = (status_reg_content & LIS3DSH_STATUS_REG_ZYXOR_bm) != 0;

  return true;
}

bool LIS3DSH_Control::checkIfDataOverrun_X(bool * is_data_overrun_x)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS, &status_reg_content)) return false;

  *is_data_overrun_x = (status_reg_content & LIS3DSH_STATUS_REG_XOR_bm) != 0;

  return true;
}

bool LIS3DSH_Control::checkIfDataOverrun_Y(bool * is_data_overrun_y)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS, &status_reg_content)) return false;

  *is_data_overrun_y = (status_reg_content & LIS3DSH_STATUS_REG_YOR_bm) != 0;

  return true;
}

bool LIS3DSH_Control::checkIfDataOverrun_Z(bool * is_data_overrun_z)
{
  uint8_t status_reg_content  = 0;

  if(!_io.readRegister(interface::Register::STATUS, &status_reg_content)) return false;

  *is_data_overrun_z = (status_reg_content & LIS3DSH_STATUS_REG_ZOR_bm) != 0;

  return true;
}

bool LIS3DSH_Control::readXYZAxis(int16_t * raw_x, int16_t * raw_y, int16_t * raw_z)
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

bool LIS3DSH_Control::readXAxis(int16_t * raw_x)
{
  uint8_t raw_x_data[2];

  if(!_io.readRegister(interface::Register::OUT_X_L, raw_x_data, 2)) return false;

  uint8_t const x_l = raw_x_data[0];
  uint8_t const x_h = raw_x_data[1];

  *raw_x = static_cast<int16_t>((static_cast<uint16_t>(x_h) << 8) + (static_cast<uint16_t>(x_l)));

  return true;
}

bool LIS3DSH_Control::readYAxis(int16_t * raw_y)
{
  uint8_t raw_y_data[2];

  if(!_io.readRegister(interface::Register::OUT_Y_L, raw_y_data, 2)) return false;

  uint8_t const y_l = raw_y_data[0];
  uint8_t const y_h = raw_y_data[1];

  *raw_y = static_cast<int16_t>((static_cast<uint16_t>(y_h) << 8) + (static_cast<uint16_t>(y_l)));

  return true;
}

bool LIS3DSH_Control::readZAxis(int16_t * raw_z)
{
  uint8_t raw_z_data[2];

  if(!_io.readRegister(interface::Register::OUT_Z_L, raw_z_data, 2)) return false;

  uint8_t const z_l = raw_z_data[0];
  uint8_t const z_h = raw_z_data[1];

  *raw_z = static_cast<int16_t>((static_cast<uint16_t>(z_h) << 8) + (static_cast<uint16_t>(z_l)));

  return true;
}

bool LIS3DSH_Control::readTemperature(int8_t * raw_temp)
{
  uint8_t temp_reg_content = 0;

  if(!_io.readRegister(interface::Register::OUT_T, &temp_reg_content)) return false;

  *raw_temp = static_cast<int8_t>(temp_reg_content);

  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensorLIS3DSH */
