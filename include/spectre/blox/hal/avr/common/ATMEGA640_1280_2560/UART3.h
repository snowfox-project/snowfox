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

#ifndef INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATMEGA640_1280_2560_UART3_H_
#define INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATMEGA640_1280_2560_UART3_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/ATxxxx/UART3.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

namespace ATMEGA640_1280_2560
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

class UART3
{

public:

  UART3(volatile uint8_t                          * udr3,
        volatile uint8_t                          * ucsr3a,
        volatile uint8_t                          * ucsr3b,
        volatile uint8_t                          * ucsr3c,
        volatile uint16_t                         * ubrr3,
        hal::interface::InterruptController       & int_ctrl,
        uint32_t                            const   f_cpu);

  hal::ATxxxx::UART3 & operator () () { return _uart3; }

private:

  hal::ATxxxx::UART3                               _uart3;
  hal::ATxxxx::UART3_TransmitRegisterEmptyCallback _uart3_uart_data_register_empty_callback;
  hal::ATxxxx::UART3_ReceiveCompleteCallback       _uart3_receive_complete_callback;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA640_1280_2560 */

} /* blox */

} /* spectre */

#endif /* INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATMEGA640_1280_2560_UART3_H_ */
