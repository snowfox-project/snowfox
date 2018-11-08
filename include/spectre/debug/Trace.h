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

#ifndef INCLUDE_SPECTRE_DEBUG_TRACE_H_
#define INCLUDE_SPECTRE_DEBUG_TRACE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include <spectre/debug/interface/Debug.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace debug
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class TraceLevel : uint8_t
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

  Trace(interface::Debug       & debug,
        TraceLevel       const   trace_level);


  void print(TraceLevel const trace_level, char const * fmt, ...);


private:

  interface::Debug & _debug;
  TraceLevel         _trace_level;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* debug */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DEBUG_TRACE_H_ */
