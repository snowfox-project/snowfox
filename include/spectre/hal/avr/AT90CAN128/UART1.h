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

#ifndef INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_UART1_H_
#define INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_UART1_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/common/AT90CAN32_64_128/UART1.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace AT90CAN128
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class UART1 : public AT90CAN32_64_128::UART1
{

public:


           UART1(volatile uint8_t                     * udr1,
                 volatile uint8_t                     * ucsr1a,
                 volatile uint8_t                     * ucsr1b,
                 volatile uint8_t                     * ucsr1c,
                 volatile uint16_t                    * ubrr1,
                 interface::InterruptController       & int_ctrl,
                 uint32_t                       const   f_cpu)  : AT90CAN32_64_128::UART1(udr1, ucsr1a, ucsr1b, ucsr1c, ubrr1, int_ctrl, f_cpu) { }
  virtual ~UART1() { }

};

/**************************************************************************************/

class UART1_TransmitRegisterEmptyCallback : public AT90CAN32_64_128::UART1_TransmitRegisterEmptyCallback
{

public:

           UART1_TransmitRegisterEmptyCallback(UART1 & uart1) : AT90CAN32_64_128::UART1_TransmitRegisterEmptyCallback(uart1) { }
  virtual ~UART1_TransmitRegisterEmptyCallback() { }

};

/**************************************************************************************/

class UART1_ReceiveCompleteCallback : public AT90CAN32_64_128::UART1_ReceiveCompleteCallback
{

public:

           UART1_ReceiveCompleteCallback(UART1 & uart1) : AT90CAN32_64_128::UART1_ReceiveCompleteCallback(uart1) { }
  virtual ~UART1_ReceiveCompleteCallback() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN128 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_UART1_H_ */
