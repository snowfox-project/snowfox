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

#include <snowfox/driver/glcd/RA6963/RA6963.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace glcd
{

namespace RA6963
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint16_t const GFX_HOME_ADDRESS = 0x0000;

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RA6963::RA6963(interface::RA6963_Control & ctrl)
: _ctrl(ctrl)
{

}

RA6963::~RA6963()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool RA6963::open()
{
  _ctrl.setGfxHomeAddress(GFX_HOME_ADDRESS);
  return true;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
ssize_t RA6963::read(uint8_t * buffer, ssize_t const num_bytes)
{
  return -1;
}
#pragma GCC diagnostic pop

ssize_t RA6963::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  _ctrl.setAddressPointer(GFX_HOME_ADDRESS );
  _ctrl.write            (buffer, num_bytes);
  return num_bytes;
}

bool RA6963::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* IOCTL_SET_GFX_AREA ***************************************************************/
  case IOCTL_SET_GFX_AREA:
  {
    uint16_t const * arg_ptr = static_cast<uint16_t *>(arg);
    _ctrl.setGfxArea(*arg_ptr);
  }
  break;
  }

  return true;
}

void RA6963::close()
{

}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RA6963 */

} /* glcd */

} /* driver */

} /* snowfox */
