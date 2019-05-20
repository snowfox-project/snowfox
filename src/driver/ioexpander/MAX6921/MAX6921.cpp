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

#include <snowfox/driver/ioexpander/MAX6921/MAX6921.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace ioexpander
{

namespace MAX6921
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

MAX6921::MAX6921(interface::MAX6921_Control & control)
: _control(control)
{

}

MAX6921::~MAX6921()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool MAX6921::open()
{
  return ioctl(IOCTL_BLANK, 0);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
ssize_t MAX6921::read(uint8_t * buffer, ssize_t const num_bytes)
{
  /* Not supported */
  return -1;
}

ssize_t MAX6921::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  /* Not supported */
  return -1;
}
#pragma GCC diagnostic pop

bool MAX6921::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* IOCTL_SET_SEGMENT ****************************************************************/
  case IOCTL_SET_SEGMENT:
  {
    uint8_t const * seg_num = static_cast<uint8_t *>(arg);
    _control.setSegment(*seg_num);
    return true;
  }
  break;
  /* IOCTL_CLR_SEGMENT ****************************************************************/
  case IOCTL_CLR_SEGMENT:
  {
    uint8_t const * seg_num = static_cast<uint8_t *>(arg);
    _control.clrSegment(*seg_num);
    return true;
  }
  break;
  /* IOCTL_WRITE **********************************************************************/
  case IOCTL_WRITE:
  {
    _control.write();
    return true;
  }
  break;
  /* IOCTL_LOAD ***********************************************************************/
  case IOCTL_LOAD:
  {
    _control.load();
    return true;
  }
  break;
  /* IOCTL_BLANK **********************************************************************/
  case IOCTL_BLANK:
  {
    _control.blank();
    return true;
  }
  break;
  /* IOCTL_NO_BLANK *******************************************************************/
  case IOCTL_NO_BLANK:
  {
    _control.noBlank();
    return true;
  }
  break;
  }

  return false;
}

void MAX6921::close()
{
  /* Nothing to do */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MAX6921 */

} /* ioexpander */

} /* driver */

} /* snowfox */
