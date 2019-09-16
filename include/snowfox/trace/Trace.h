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

#ifndef INCLUDE_SNOWFOX_TRACE_TRACE_H_
#define INCLUDE_SNOWFOX_TRACE_TRACE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdarg.h>

#include <snowfox/trace/interface/TraceOutput.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace trace
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Level : uint8_t
{
  None  = 0,
  Error = 1,
  Warn  = 2,
  Info  = 3,
  Debug = 4
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class Trace
{

public:

   Trace(interface::TraceOutput       & trace_out,
         Level                  const   trace_level,
         uint16_t               const   trace_buf_size = DEFAULT_TRACE_BUFFER_SIZE);
  ~Trace();


  void print  (Level const trace_level, char const * fmt, ...);
  void println(Level const trace_level, char const * fmt, ...);
  void println(Level const trace_level);


  static uint16_t const DEFAULT_TRACE_BUFFER_SIZE = 128;


private:

  interface::TraceOutput        & _trace_out;
  Level                           _trace_level;
  uint16_t                const   _trace_buf_size;
  uint8_t                       * _trace_buf;

  void vprint(Level const trace_level, char const * fmt, va_list args);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* trace */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_TRACE_TRACE_H_ */
