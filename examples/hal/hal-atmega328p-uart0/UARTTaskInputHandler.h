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

#ifndef EXAMPLES_HAL_ATMEGA328P_UART0_UARTTASKINPUTHANDLER_H_
#define EXAMPLES_HAL_ATMEGA328P_UART0_UARTTASKINPUTHANDLER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/uart/UARTCallback.h>

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class UARTTaskInputHandler : public spectre::hal::interface::UARTCallback
{

public:

           UARTTaskInputHandler();
  virtual ~UARTTaskInputHandler();


  virtual void onTransmitRegisterEmptyCallback() override;
  virtual void onReceiveCompleteCallback      () override;

};

#endif /* EXAMPLES_HAL_ATMEGA328P_UART0_UARTTASKINPUTHANDLER_H_ */
