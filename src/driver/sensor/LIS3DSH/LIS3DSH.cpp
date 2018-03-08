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

#include <spectre/driver/sensor/LIS3DSH/LIS3DSH.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace LIS3DSH
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

LIS3DSH::LIS3DSH(interface::LIS3DSH_Control & ctrl)
: _ctrl(ctrl)
{

}

LIS3DSH::~LIS3DSH()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool LIS3DSH::open()
{
  /* TODO */
  return false;
}

ssize_t LIS3DSH::read(uint8_t * buffer, ssize_t const num_bytes)
{
  /* TODO */
  return -1;
}

ssize_t LIS3DSH::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  /* TODO */
  return -1;
}

bool LIS3DSH::ioctl(uint32_t const cmd, void * arg)
{
  /* TODO */
  return false;
}

void LIS3DSH::close()
{
  /* TODO */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS3DSH */

} /* sensor */

} /* driver */

} /* spectre */
