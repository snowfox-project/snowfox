/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SNOWFOX_DRIVER_SERIAL_INTERFACE_SERIALCONFIGURATION_H_
#define INCLUDE_SNOWFOX_DRIVER_SERIAL_INTERFACE_SERIALCONFIGURATION_H_

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::serial::interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class SerialBaudRate : uint8_t
{
  B115200
};

enum class SerialParity : uint8_t
{
  None,
  Even,
  Odd
};

enum class SerialStopBit : uint8_t
{
  _1,
  _2
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class SerialConfiguration
{

public:


           SerialConfiguration() { }
  virtual ~SerialConfiguration() { }


  virtual void setBaudRate       (SerialBaudRate const baud_rate) = 0;
  virtual void setParity         (SerialParity   const parity   ) = 0;
  virtual void setStopBit        (SerialStopBit  const stop_bit ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::serial::interface */

#endif /* INCLUDE_SNOWFOX_DRIVER_SERIAL_INTERFACE_SERIALCONFIGURATION_H_ */
