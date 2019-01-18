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

#ifndef INCLUDE_SNOWFOX_BLOX_HAL_AVR_COMMON_ATXXXX_UART1_HPP_
#define INCLUDE_SNOWFOX_BLOX_HAL_AVR_COMMON_ATXXXX_UART1_HPP_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/avr/common/ATxxxx/UART1.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
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

  hal::ATxxxx::UART1 & operator () () { return _uart1; }

private:

  hal::ATxxxx::UART1                               _uart1;
  hal::ATxxxx::UART1_TransmitRegisterEmptyCallback _uart1_uart_data_register_empty_callback;
  hal::ATxxxx::UART1_ReceiveCompleteCallback       _uart1_receive_complete_callback;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* blox */

} /* snowfox */

/**************************************************************************************
 * TEMPLATE CODE IMPLEMENTATION
 **************************************************************************************/

#include "UART1.ipp"

#endif /* INCLUDE_SNOWFOX_BLOX_HAL_AVR_COMMON_ATXXXX_UART1_HPP_ */
