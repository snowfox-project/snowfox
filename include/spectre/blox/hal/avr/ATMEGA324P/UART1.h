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

#ifndef INCLUDE_SPECTRE_BLOX_HAL_AVR_ATMEGA324P_UART1_H_
#define INCLUDE_SPECTRE_BLOX_HAL_AVR_ATMEGA324P_UART1_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/ATMEGA324P/UART1.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

namespace ATMEGA324P
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

class UART1
{

public:

  UART1(volatile uint8_t                                  * udr1,
        volatile uint8_t                                  * ucsr1a,
        volatile uint8_t                                  * ucsr1b,
        volatile uint8_t                                  * ucsr1c,
        volatile uint16_t                                 * ubrr1,
        hal::interface::InterruptController               & int_ctrl,
        uint32_t                                    const   f_cpu);

  hal::ATMEGA324P::UART1 & operator () () { return _uart1; }

private:

  hal::ATMEGA324P::UART1                                _uart1;
  hal::ATMEGA324P::UART1_TransmitRegisterEmptyCallback  _uart1_uart_data_register_empty_callback;
  hal::ATMEGA324P::UART1_ReceiveCompleteCallback        _uart1_receive_complete_callback;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA324P */

} /* blox */

} /* spectre */

#endif /* INCLUDE_SPECTRE_BLOX_HAL_AVR_ATMEGA324P_UART1_H_ */
