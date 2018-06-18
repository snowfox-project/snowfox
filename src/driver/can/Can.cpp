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

#include <spectre/driver/can/Can.h>

#include <string.h>

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

Can::Can(interface::CanConfiguration & config, interface::CanControl & control)
: _config    (config    ),
  _control   (control   )
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
  ssize_t const num_frames = num_bytes / sizeof(hal::interface::CanFrame);

  if(num_frames < 0) return -1;

  ssize_t bytes_read = 0;

  for(ssize_t f = 0;
      (f < num_frames);
      f++, bytes_read += sizeof(hal::interface::CanFrame))
  {
    hal::interface::CanFrame can_frame;

    if(!_control.receive(&can_frame)) break;

    memcpy(buffer + bytes_read, &can_frame, sizeof(hal::interface::CanFrame));
  }

  return bytes_read;
}

ssize_t Can::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  ssize_t const num_frames = num_bytes / sizeof(hal::interface::CanFrame);

  if(num_frames < 0) return -1;

  ssize_t bytes_written = 0;

  for(ssize_t f = 0;
      (f < num_frames);
      f++, bytes_written += sizeof(hal::interface::CanFrame))
  {
    hal::interface::CanFrame can_frame;
    memcpy(&can_frame, buffer + bytes_written, sizeof(hal::interface::CanFrame));

    if(!_control.transmit(can_frame)) break;
  }

  return bytes_written;
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
    _config.setCanBitRate(can_bitrate);
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
