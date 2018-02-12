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

#include <spectre/driver/can/MCP2515/MCP2515_CanController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
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

MCP2515_CanController::MCP2515_CanController(interface::MCP2515_Control & mcp2515_ctrl, uint8_t const f_mcp2515_MHz)
: _mcp2515_ctrl (mcp2515_ctrl ),
  _f_mcp2515_MHz(f_mcp2515_MHz)
{

}

MCP2515_CanController::~MCP2515_CanController()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void MCP2515_CanController::setCanBitRate(can::interface::CanBitRate const can_bit_rate)
{
  switch(can_bit_rate)
  {
  case can::interface::CanBitRate::BR_125kBPS: _mcp2515_ctrl.setCanBitRate(interface::CanBitRate::BR_125kBPS, _f_mcp2515_MHz); break;
  case can::interface::CanBitRate::BR_250kBPS: _mcp2515_ctrl.setCanBitRate(interface::CanBitRate::BR_250kBPS, _f_mcp2515_MHz); break;
  case can::interface::CanBitRate::BR_500kBPS: _mcp2515_ctrl.setCanBitRate(interface::CanBitRate::BR_500kBPS, _f_mcp2515_MHz); break;
  case can::interface::CanBitRate::BR_1MBPS  : _mcp2515_ctrl.setCanBitRate(interface::CanBitRate::BR_1MBPS  , _f_mcp2515_MHz); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */
