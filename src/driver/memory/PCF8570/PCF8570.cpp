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

PCF8570::PCF8570(interface::PCF8570_Control & ctrl)
: _ctrl(ctrl)
{

}

PCF8570::~PCF8570()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool PCF8570::open()
{
  return true;
}

ssize_t PCF8570::read(uint8_t * buffer, ssize_t const num_bytes)
{
  return read(buffer[0], buffer + 1, num_bytes - 1);
}

ssize_t PCF8570::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  return write(buffer[0], buffer + 1, num_bytes - 1);
}

bool PCF8570::ioctl(uint32_t const cmd, void * arg)
{
  return false;
}

void PCF8570::close()
{

}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

bool PCF8570::read(uint8_t const address, uint8_t * buffer, uint32_t const num_bytes)
{
  for(uint32_t b = 0; b < num_bytes; b++)
  {
    if(!_ctrl.read(address, buffer + b)) return false;
  }
  return true;
}

bool PCF8570::write(uint8_t const address, uint8_t const * buffer, uint32_t const num_bytes)
{
  for(uint32_t b = 0; b < num_bytes; b++)
  {
    if(!_ctrl.write(address, buffer[b])) return false;
  }
  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* PCF8570 */

} /* memory */

} /* driver */

} /* spectre */
