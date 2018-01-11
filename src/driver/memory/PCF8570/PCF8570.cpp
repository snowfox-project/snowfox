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

#include <spectre/driver/memory/PCF8570/PCF8570.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace memory
{

namespace PCF8570
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

PCF8570::PCF8570(PCF8570_IO_Interface & io)
: _io(io)
{

}

PCF8570::~PCF8570()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool PCF8570::write(uint8_t const address, uint8_t const data)
{
  return _io.writeByte(address, data);
}

bool PCF8570::read(uint8_t const address, uint8_t * data)
{
  return _io.readByte(address, data);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* PCF8570 */

} /* memory */

} /* driver */

} /* spectre */
