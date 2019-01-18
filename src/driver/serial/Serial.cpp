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

#include <snowfox/driver/serial/Serial.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace serial
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Serial::Serial(interface::SerialConfiguration & config, interface::SerialControl & control)
: _config (config ),
  _control(control)
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
  return true;
}

ssize_t Serial::read(uint8_t * buffer, ssize_t const num_bytes)
{
  return _control.receive(buffer, num_bytes);
}

ssize_t Serial::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  return _control.transmit(buffer, num_bytes);
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
    _config.setBaudRate(baud_rate);
    return true;
  }
  break;
  /* SET_PARITY ***********************************************************************/
  case IOCTL_SET_PARITY:
  {
    uint8_t                 const * arg_ptr = static_cast<uint8_t *>              (arg     );
    interface::SerialParity const   parity  = static_cast<interface::SerialParity>(*arg_ptr);
    _config.setParity(parity);
    return true;
  }
  break;
  /* SET_STOPBIT **********************************************************************/
  case IOCTL_SET_STOPBIT:
  {
    uint8_t                  const * arg_ptr  = static_cast<uint8_t *>               (arg     );
    interface::SerialStopBit const   stop_bit = static_cast<interface::SerialStopBit>(*arg_ptr);
    _config.setStopBit(stop_bit);
    return true;
  }
  break;
  }

  return false;
}

void Serial::close()
{

}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* serial */

} /* driver */

} /* snowfox */
