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

#include <spectre/debug/serial/DebugSerial.h>

#include <stdio.h>
#include <stdarg.h>

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

void DebugSerial::print(char const * fmt, ...)
{
  uint8_t buf[DEBUG_SERIAL_BUFFER_SIZE];
  va_list args;

  va_start (args, fmt);
  ssize_t const length = vsnprintf (reinterpret_cast<char *>(buf), DEBUG_SERIAL_BUFFER_SIZE, fmt, args);
  va_end   (args);

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
