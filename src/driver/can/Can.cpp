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

#include <spectre/driver/can/Can.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace can
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Can::Can(interface::CanController & can_ctrl)
: _can_ctrl(can_ctrl)
{

}

Can::~Can()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool Can::open()
{
  /* TODO */
  return false;
}

ssize_t Can::read(uint8_t * buffer, ssize_t const num_bytes)
{
  /* TODO */
  return -1;
}

ssize_t Can::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  /* TODO */
  return -1;
}

bool Can::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* SET_BITRATE **********************************************************************/
  case IOCTL_SET_BITRATE:
  {
    uint8_t               const * arg_ptr     = static_cast<uint8_t *>            (arg     );
    interface::CanBitRate const   can_bitrate = static_cast<interface::CanBitRate>(*arg_ptr);
    _can_ctrl.setCanBitRate(can_bitrate);
    return true;
  }
  break;
  }

  return false;
}

void Can::close()
{
  /* TODO */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* can */

} /* driver */

} /* spectre */
