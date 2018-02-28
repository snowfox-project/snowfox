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

#ifndef INCLUDE_SPECTRE_DEBUG_SERIAL_DEBUGSERIAL_H_
#define INCLUDE_SPECTRE_DEBUG_SERIAL_DEBUGSERIAL_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/debug/interface/Debug.h>

#include <stdlib.h>

#include <spectre/driver/interface/Driver.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace debug
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class DebugSerial : public interface::Debug
{

public:

           DebugSerial(driver::interface::Driver & serial);
  virtual ~DebugSerial();


  virtual void print(char const * fmt, ...) override;


private:

  driver::interface::Driver & _serial;

  static size_t constexpr DEBUG_SERIAL_BUFFER_SIZE = 128;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* debug */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DEBUG_SERIAL_DEBUGSERIAL_H_ */
