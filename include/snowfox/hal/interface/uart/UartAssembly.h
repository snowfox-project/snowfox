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

#ifndef INTERFACE_UART_ASSEMBLY_H_
#define INTERFACE_UART_ASSEMBLY_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/interface/uart/events/UART_onRxDoneCallback.h>
#include <snowfox/hal/interface/uart/events/UART_onTxDoneCallback.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class UartAssembly
{

public:

           UartAssembly() { }
  virtual ~UartAssembly() { }


  virtual void register_onRxDoneCallback(UART_onRxDoneCallback * on_rx_done_callback) = 0;
  virtual void register_onTxDoneCallback(UART_onTxDoneCallback * on_tx_done_callback) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface*/

} /* hal */

} /* snowfox */

#endif /* INTERFACE_UART_ASSEMBLY_H_ */
