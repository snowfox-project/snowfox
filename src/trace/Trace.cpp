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

#include <snowfox/trace/Trace.h>

#include <stdio.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace trace
{

/**************************************************************************************
 * PRIVATE PROTOTYPES
 **************************************************************************************/

bool operator <= (Level const lhs, Level const rhs);

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Trace::Trace(interface::TraceOutput & trace_out, Level const trace_level, uint16_t const trace_buf_size)
: _trace_out     (trace_out                   ),
  _trace_level   (trace_level                 ),
  _trace_buf_size(trace_buf_size              ),
  _trace_buf     (new uint8_t[_trace_buf_size])
{

}

Trace::~Trace()
{
  delete[] _trace_buf; _trace_buf = 0;
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void Trace::print(Level const trace_level, char const * fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vprint(trace_level, fmt, args);
  va_end(args);
}

void Trace::println(Level const trace_level, char const * fmt, ...)
{
  /* Print the debug message */
  va_list args;
  va_start(args, fmt);
  vprint(trace_level, fmt, args);
  va_end(args);

  /* Print the character for new line */
  println(trace_level);
}

void Trace::println(Level const trace_level)
{
  static uint8_t const NEW_LINE_BUF[2] = {'\r', '\n'};

  if(trace_level <= _trace_level) {
    /* Print the character for new line */
    _trace_out.write(reinterpret_cast<uint8_t const *>(NEW_LINE_BUF), sizeof(NEW_LINE_BUF));
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void Trace::vprint(Level const trace_level, char const * fmt, va_list args)
{
  if(trace_level <= _trace_level)
  {
    uint16_t const length = vsnprintf(reinterpret_cast<char *>(_trace_buf), _trace_buf_size, fmt, args);
    _trace_out.write(_trace_buf, length);
  }
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

bool operator <= (Level const lhs, Level const rhs)
{
  return static_cast<uint8_t>(lhs) <= static_cast<uint8_t>(rhs);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* trace */

} /* snowfox */
