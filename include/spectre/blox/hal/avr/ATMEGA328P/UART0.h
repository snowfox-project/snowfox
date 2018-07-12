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

#ifndef INCLUDE_SPECTRE_BLOX_HAL_AVR_ATMEGA328P_UART0_H_
#define INCLUDE_SPECTRE_BLOX_HAL_AVR_ATMEGA328P_UART0_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/ATMEGA328P/UART0.h>

#include <spectre/hal/interface/interrupt/InterruptControllerAssembly.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

namespace ATMEGA328P
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

class UART0
{

public:

  UART0(volatile uint8_t                                  * udr0,
        volatile uint8_t                                  * ucsr0a,
        volatile uint8_t                                  * ucsr0b,
        volatile uint8_t                                  * ucsr0c,
        volatile uint16_t                                 * ubrr0,
        hal::interface::InterruptController               & int_ctrl,
        hal::interface::InterruptControllerAssembly       & int_ctrl_assembly,
        uint32_t                                    const   f_cpu);

  hal::ATMEGA328P::UART0 & operator () () { return _uart0; }

private:

  hal::ATMEGA328P::UART0                                _uart0;
  hal::ATMEGA328P::UART0_TransmitRegisterEmptyCallback  _uart0_uart_data_register_empty_callback;
  hal::ATMEGA328P::UART0_ReceiveCompleteCallback        _uart0_receive_complete_callback;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* blox */

} /* spectre */

#endif /* INCLUDE_SPECTRE_BLOX_HAL_AVR_ATMEGA328P_UART0_H_ */
