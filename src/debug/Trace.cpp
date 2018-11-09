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

#include <spectre/debug/Trace.h>

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
 * PRIVATE PROTOTYPES
 **************************************************************************************/

bool operator <= (TraceLevel const lhs, TraceLevel const rhs);

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Trace::Trace(interface::Debug & debug, TraceLevel const trace_level, uint16_t const trace_buf_size)
: _debug         (debug                       ),
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

void Trace::print(TraceLevel const trace_level, char const * fmt, ...)
{
  if(trace_level <= _trace_level)
  {
    va_list args;

    va_start (args, fmt);
    uint16_t const length = vsnprintf (reinterpret_cast<char *>(_trace_buf), _trace_buf_size, fmt, args);
    va_end   (args);
  }
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

bool operator <= (TraceLevel const lhs, TraceLevel const rhs)
{
  return static_cast<uint8_t>(lhs) <= static_cast<uint8_t>(rhs);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* debug */

} /* spectre */
