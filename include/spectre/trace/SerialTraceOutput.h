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

#ifndef INCLUDE_SPECTRE_DEBUG_SERIAL_SERIALTRACEOUTPUT_H_
#define INCLUDE_SPECTRE_DEBUG_SERIAL_SERIALTRACEOUTPUT_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/trace/interface/TraceOutput.h>

#include <stdlib.h>

#include <spectre/driver/interface/Driver.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace trace
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class SerialTraceOutput : public interface::TraceOutput
{

public:

           SerialTraceOutput(driver::interface::Driver & serial);
  virtual ~SerialTraceOutput();


  virtual void write(uint8_t const * buf, uint16_t const length) override;


private:

  driver::interface::Driver & _serial;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* trace */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DEBUG_SERIAL_SERIALTRACEOUTPUT_H_ */
