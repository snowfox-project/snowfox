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

#include <spectre/driver/lora/RFM9x/RFM9x_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace lora
{

namespace RFM9x
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RFM9x_Control::RFM9x_Control(interface::RFM9x_Io & io, uint32_t const fxosc_Hz)
: _io      (io      ),
  _fxosc_Hz(fxosc_Hz)
{

}

RFM9x_Control::~RFM9x_Control()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_Control::setOperatingMode(interface::OperatingMode const op_mode)
{
  uint8_t reg_op_mode_content = 0;

  _io.readRegister(interface::Register::OP_MODE, &reg_op_mode_content);

  reg_op_mode_content &= ~(RFM9x_REG_OP_MODE_MODE_2_bm | RFM9x_REG_OP_MODE_MODE_1_bm | RFM9x_REG_OP_MODE_MODE_0_bm);
  reg_op_mode_content |= static_cast<uint8_t>(op_mode);

  _io.writeRegister(interface::Register::OP_MODE, reg_op_mode_content);
}

void RFM9x_Control::setLoRaMode(interface::LoRaMode const lora_mode)
{
  uint8_t reg_op_mode_content = 0;

  _io.readRegister(interface::Register::OP_MODE, &reg_op_mode_content);

  reg_op_mode_content &= ~(RFM9x_REG_OP_MODE_LONG_RANGE_MODE_bm);
  reg_op_mode_content |= static_cast<uint8_t>(lora_mode);

  _io.writeRegister(interface::Register::OP_MODE, reg_op_mode_content);
}

void RFM9x_Control::setModulationType(interface::ModulationType const modulation_type)
{
  uint8_t reg_op_mode_content = 0;

  _io.readRegister(interface::Register::OP_MODE, &reg_op_mode_content);

  reg_op_mode_content &= ~(RFM9x_REG_OP_MODE_MODULATION_TYPE_1_bm | RFM9x_REG_OP_MODE_MODULATION_TYPE_0_bm);
  reg_op_mode_content |= static_cast<uint8_t>(modulation_type);

  _io.writeRegister(interface::Register::OP_MODE, reg_op_mode_content);
}

void RFM9x_Control::setFrequency(uint32_t const f_rf_Hz)
{
  float    const f_step_Hz = static_cast<float>(_fxosc_Hz) / 524288.0;
  uint32_t const f_rf      = static_cast<uint32_t>(f_step_Hz / static_cast<float>(f_rf_Hz));

  uint8_t const f_rf_msb = static_cast<uint8_t>((f_rf & 0x00FF0000) >> 16);
  uint8_t const f_rf_mid = static_cast<uint8_t>((f_rf & 0x0000FF00) >>  8);
  uint8_t const f_rf_lsb = static_cast<uint8_t>((f_rf & 0x000000FF) >>  0);

  _io.writeRegister(interface::Register::FRF_MSB, f_rf_msb);
  _io.writeRegister(interface::Register::FRF_MID, f_rf_mid);
  _io.writeRegister(interface::Register::FRF_LSB, f_rf_lsb);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
