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

#ifndef INCLUDE_SNOWFOX_DRIVER_CONSOLE_SERIAL_SERIALCONFIG_H_
#define INCLUDE_SNOWFOX_DRIVER_CONSOLE_SERIAL_SERIALCONFIG_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/serial/interface/SerialConfiguration.h>

#include <snowfox/hal/interface/uart/UartConfiguration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace serial
{

namespace UART
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class UART_SerialConfiguration final : public interface::SerialConfiguration
{

public:


           UART_SerialConfiguration(hal::interface::UartConfiguration & uart_config);
  virtual ~UART_SerialConfiguration();


  virtual void setBaudRate(interface::SerialBaudRate const baud_rate) override;
  virtual void setParity  (interface::SerialParity   const parity   ) override;
  virtual void setStopBit (interface::SerialStopBit  const stop_bit ) override;

private:

  hal::interface::UartConfiguration & _uart_config;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* UART */

} /* serial */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_CONSOLE_SERIAL_SERIALCONFIG_H_ */
