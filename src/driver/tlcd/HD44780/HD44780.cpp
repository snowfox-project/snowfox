/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#include <spectre/driver/tlcd/HD44780/HD44780.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace tlcd
{

namespace HD44780
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

HD44780::HD44780(interface::HD44780_Control & ctrl)
: _ctrl(ctrl)
{

}

HD44780::~HD44780()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool HD44780::open()
{
  /* TODO */ return false;
}

ssize_t HD44780::read(uint8_t * buffer, ssize_t const num_bytes)
{
  /* TODO */ return -1;
}

ssize_t HD44780::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  /* TODO */ return -1;
}

bool HD44780::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* IOCTL_CLEAR_DISPLAY **************************************************************/
  case IOCTL_CLEAR_DISPLAY:
  {
    _ctrl.clear();
    return true;
  }
  break;
  /* IOCTL_RETURN_HOME ****************************************************************/
  case IOCTL_RETURN_HOME:
  {
    _ctrl.home();
    return true;
  }
  break;
  }

  return false;
}

void HD44780::close()
{
  /* TODO */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* HD44780 */

} /* tlcd */

} /* driver */

} /* spectre */
