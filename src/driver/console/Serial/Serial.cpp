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

#include <spectre/driver/console/Serial/Serial.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace console
{

namespace serial
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Serial::Serial()
{

}

Serial::~Serial()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool Serial::open()
{
  /* TODO */
  return false;
}

ssize_t Serial::read(uint8_t * buffer, ssize_t const num_bytes)
{
  /* TODO */
  return false;
}

ssize_t Serial::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  /* TODO */
  return false;
}

bool Serial::ioctl(uint32_t const cmd, void * arg)
{
  /* TODO */
  return false;
}

void Serial::close()
{
  /* TODO */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* serial */

} /* console */

} /* driver */

} /* spectre */
