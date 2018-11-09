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

#include <spectre/debug/serial/DebugSerial.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace debug
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

DebugSerial::DebugSerial(driver::interface::Driver & serial)
: _serial  (serial)
{
  _serial.open();
}

DebugSerial::~DebugSerial()
{
  _serial.close();
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void DebugSerial::write(uint8_t const * buf, uint16_t const length)
{
  for(ssize_t bytes_written = 0; bytes_written != length; )
  {
    bytes_written += _serial.write(buf + bytes_written, length - bytes_written);
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* debug */

} /* spectre */
