/**
 * Spectre is a modular RTOS with extensive IO support.
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

#ifndef INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATXXXX_UART2_HPP_
#define INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATXXXX_UART2_HPP_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/ATxxxx/UART2.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

namespace ATxxxx
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

template <uint8_t UART_DATA_REGISTER_EMPTY_INTERRUPT_NUMBER,
          uint8_t UART_RECEIVE_COMPLETE_INTERRUPT_NUMBER>
class UART2
{

public:

  UART2(volatile uint8_t                                  * udr2,
        volatile uint8_t                                  * ucsr2a,
        volatile uint8_t                                  * ucsr2b,
        volatile uint8_t                                  * ucsr2c,
        volatile uint16_t                                 * ubrr2,
        hal::interface::InterruptController               & int_ctrl,
        uint32_t                                    const   f_cpu);

  hal::ATxxxx::UART2 & operator () () { return _uart2; }

private:

  hal::ATxxxx::UART2                               _uart2;
  hal::ATxxxx::UART2_TransmitRegisterEmptyCallback _uart2_uart_data_register_empty_callback;
  hal::ATxxxx::UART2_ReceiveCompleteCallback       _uart2_receive_complete_callback;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* blox */

} /* spectre */

/**************************************************************************************
 * TEMPLATE CODE IMPLEMENTATION
 **************************************************************************************/

#include "UART2.ipp"

#endif /* INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATXXXX_UART2_HPP_ */
