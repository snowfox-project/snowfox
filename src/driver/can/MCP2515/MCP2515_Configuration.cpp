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

#include <snowfox/driver/can/MCP2515/MCP2515_Configuration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace can
{

namespace MCP2515
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

MCP2515_Configuration::MCP2515_Configuration(interface::MCP2515_Io & io, hal::interface::Delay & delay)
: _io   (io)
, _delay(delay)
{

}

MCP2515_Configuration::~MCP2515_Configuration()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool MCP2515_Configuration::setOperationMode(interface::OperationMode const op_mode)
{
  static uint8_t constexpr CANCTRL_REQOP_MASK = (MCP2515_REG_CANCTRL_REQOP2_bm | MCP2515_REG_CANCTRL_REQOP1_bm | MCP2515_REG_CANCTRL_REQOP0_bm);
  static uint8_t constexpr CANSTAT_OP_MASK    = (MCP2515_REG_CANSTAT_OPMOD2_bm | MCP2515_REG_CANSTAT_OPMOD1_bm | MCP2515_REG_CANSTAT_OPMOD0_bm);
  
  uint8_t const canctrl_op_mode_val = static_cast<uint8_t>(op_mode);

  /* Set the desired operating mode */
  _io.modifyRegister(interface::Register::CANCTRL, CANCTRL_REQOP_MASK, canctrl_op_mode_val);

  /* Wait a little */
  _delay.delay_ms(10);
  
  /* Determine wether or not the desired operating mode has been set */
  uint8_t canstat_op_mode_val = 0;
  _io.readRegister(interface::Register::CANSTAT, &canstat_op_mode_val);
  canstat_op_mode_val &= CANSTAT_OP_MASK;
  
  bool const is_op_mode_change_success = (canstat_op_mode_val == canctrl_op_mode_val);
  return is_op_mode_change_success;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* snowfox */
