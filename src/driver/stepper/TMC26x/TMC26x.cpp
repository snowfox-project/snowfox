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
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/stepper/TMC26x/TMC26x.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace stepper
{

namespace TMC26x
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

TMC26x::TMC26x()
{

}

TMC26x::~TMC26x()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool TMC26x::open()
{
  /* TODO*/
  return false;
}

ssize_t TMC26x::read(uint8_t * buffer, ssize_t const num_bytes)
{
  /* TODO*/
  return -1;
}

ssize_t TMC26x::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  /* TODO*/
  return -1;
}

bool TMC26x::ioctl(uint32_t const cmd, void * arg)
{
  /* TODO*/
  return false;
}

void TMC26x::close()
{
  /* TODO*/
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* TMC26x */

} /* stepper */

} /* driver */

} /* spectre */
