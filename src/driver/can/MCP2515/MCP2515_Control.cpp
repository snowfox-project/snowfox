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

#include <spectre/driver/can/MCP2515/MCP2515_Control.h>

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

MCP2515_Control::MCP2515_Control(interface::MCP2515_Io & io)
: _io(io)
{

}

MCP2515_Control::~MCP2515_Control()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void MCP2515_Control::getIntFlags(uint8_t * irq_flags)
{
  _io.readRegister(interface::Register::CANINTF, irq_flags);
}

void MCP2515_Control::clearIntFlag(interface::InterruptFlag const int_flag)
{
  /* The interrupt request flag can be cleared by writing
   * a '0' to the corresponding bit in the IRQ register.
   */

  uint8_t reg_cantintf_content = 0;

  _io.readRegister(interface::Register::CANINTF, &reg_cantintf_content);

  reg_cantintf_content &= ~(static_cast<uint8_t>(int_flag));

  _io.writeRegister(interface::Register::CANINTF, reg_cantintf_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */
