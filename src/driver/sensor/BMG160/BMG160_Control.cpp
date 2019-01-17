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

#include <snowfox/driver/sensor/BMG160/BMG160_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
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

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* BMG160 */

} /* sensor */

} /* driver */

} /* snowfox */
