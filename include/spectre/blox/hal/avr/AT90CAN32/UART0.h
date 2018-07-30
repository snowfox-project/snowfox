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

#ifndef INCLUDE_SPECTRE_BLOX_HAL_AVR_AT90CAN32_UART0_H_
#define INCLUDE_SPECTRE_BLOX_HAL_AVR_AT90CAN32_UART0_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/AT90CAN32/UART0.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

namespace AT90CAN32
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

class UART0
{

public:

  UART0(volatile uint8_t                          * udr0,
        volatile uint8_t                          * ucsr0a,
        volatile uint8_t                          * ucsr0b,
        volatile uint8_t                          * ucsr0c,
        volatile uint16_t                         * ubrr0,
        hal::interface::InterruptController       & int_ctrl,
        uint32_t                            const   f_cpu);

  hal::AT90CAN32::UART0 & operator () () { return _uart0; }

private:

  hal::AT90CAN32::UART0                               _uart0;
  hal::AT90CAN32::UART0_TransmitRegisterEmptyCallback _uart0_uart_data_register_empty_callback;
  hal::AT90CAN32::UART0_ReceiveCompleteCallback       _uart0_receive_complete_callback;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN32 */

} /* blox */

} /* spectre */

#endif /* INCLUDE_SPECTRE_BLOX_HAL_AVR_AT90CAN32_UART0_H_ */
