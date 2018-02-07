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

Serial::Serial(interface::SerialController & serial_ctrl)
: _serial_ctrl(serial_ctrl)
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
  ssize_t bytes_read = 0;

  for(; (bytes_read < num_bytes) && !_serial_ctrl.isRxBufferEmpty(); bytes_read++)
  {
    buffer[bytes_read] = _serial_ctrl.getRxBufferData();
  }

  return bytes_read;
}

ssize_t Serial::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  ssize_t bytes_written = 0;

  for(; (bytes_written < num_bytes) && !_serial_ctrl.isTxBufferFull(); bytes_written++)
  {
    _serial_ctrl.putDataTxBuffer(buffer[bytes_written]);
  }

  return bytes_written;
}

bool Serial::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* SET_BAUDRATE *********************************************************************/
  case IOCTL_SET_BAUDRATE:
  {
    /* TODO */
  }
  break;
  /* SET_PARITY ***********************************************************************/
  case IOCTL_SET_PARITY:
  {
    /* TODO */
  }
  break;
  /* SET_STOPPBIT *********************************************************************/
  case IOCTL_SET_STOPPBIT:
  {
    /* TODO */
  }
  break;
  }
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
