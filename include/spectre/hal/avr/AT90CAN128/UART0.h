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

#ifndef INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_UART0_H_
#define INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_UART0_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/common/AT90CAN32_64_128/UART0.h>

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

class UART0 : public AT90CANxxxx::UART0
{

public:


           UART0(volatile uint8_t                     * udr0,
                 volatile uint8_t                     * ucsr0a,
                 volatile uint8_t                     * ucsr0b,
                 volatile uint8_t                     * ucsr0c,
                 volatile uint16_t                    * ubrr0,
                 interface::InterruptController       & int_ctrl,
                 uint32_t                       const   f_cpu) : AT90CANxxxx::UART0(udr0, ucsr0a, ucsr0b, ucsr0c, ubrr0, int_ctrl, f_cpu) { }
  virtual ~UART0() { }

};

/**************************************************************************************/

class UART0_TransmitRegisterEmptyCallback : public AT90CANxxxx::UART0_TransmitRegisterEmptyCallback
{

public:

           UART0_TransmitRegisterEmptyCallback(UART0 & uart0) : AT90CANxxxx::UART0_TransmitRegisterEmptyCallback(uart0) { }
  virtual ~UART0_TransmitRegisterEmptyCallback() { }

};

/**************************************************************************************/

class UART0_ReceiveCompleteCallback : public AT90CANxxxx::UART0_ReceiveCompleteCallback
{

public:

           UART0_ReceiveCompleteCallback(UART0 & uart0) : AT90CANxxxx::UART0_ReceiveCompleteCallback(uart0) { }
  virtual ~UART0_ReceiveCompleteCallback() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN128 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_UART0_H_ */
