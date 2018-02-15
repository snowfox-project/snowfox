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

#include <spectre/driver/serial/Serial.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace serial
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Serial::Serial(interface::SerialController & serial_ctrl, interface::SerialTransmitBuffer & serial_tx_buf, interface::SerialReceiveBuffer & serial_rx_buf)
: _serial_ctrl  (serial_ctrl  ),
  _serial_tx_buf(serial_tx_buf),
  _serial_rx_buf(serial_rx_buf)
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
  _serial_ctrl.enable();
  return true;
}

ssize_t Serial::read(uint8_t * buffer, ssize_t const num_bytes)
{
  ssize_t bytes_read = 0;

  for(; (bytes_read < num_bytes) && !_serial_rx_buf.isEmpty(); bytes_read++)
  {
    _serial_rx_buf.getData(buffer + bytes_read);
  }

  return bytes_read;
}

ssize_t Serial::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  ssize_t bytes_written = 0;

  for(; (bytes_written < num_bytes) && !_serial_tx_buf.isFull(); bytes_written++)
  {
    _serial_tx_buf.putData(buffer[bytes_written]);
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
    uint8_t                   const * arg_ptr   = static_cast<uint8_t *>                (arg     );
    interface::SerialBaudRate const   baud_rate = static_cast<interface::SerialBaudRate>(*arg_ptr);
    _serial_ctrl.setBaudRate(baud_rate);
    return true;
  }
  break;
  /* SET_PARITY ***********************************************************************/
  case IOCTL_SET_PARITY:
  {
    uint8_t                 const * arg_ptr = static_cast<uint8_t *>              (arg     );
    interface::SerialParity const   parity  = static_cast<interface::SerialParity>(*arg_ptr);
    _serial_ctrl.setParity(parity);
    return true;
  }
  break;
  /* SET_STOPBIT **********************************************************************/
  case IOCTL_SET_STOPBIT:
  {
    uint8_t                  const * arg_ptr  = static_cast<uint8_t *>               (arg     );
    interface::SerialStopBit const   stop_bit = static_cast<interface::SerialStopBit>(*arg_ptr);
    _serial_ctrl.setStopBit(stop_bit);
    return true;
  }
  break;
  }

  return false;
}

void Serial::close()
{
  _serial_ctrl.disable();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* serial */

} /* driver */

} /* spectre */
