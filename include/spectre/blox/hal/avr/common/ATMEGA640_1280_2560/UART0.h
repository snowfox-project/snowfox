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

#ifndef INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATMEGA640_1280_2560_UART0_H_
#define INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATMEGA640_1280_2560_UART0_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/blox/hal/avr/common/ATxxxx/UART0.hpp>

#include <spectre/hal/avr/common/ATMEGA640_1280_2560/InterruptController.h>

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
 * TYPEDEF
 **************************************************************************************/

typedef ATxxxx::UART0<hal::ATMEGA640_1280_2560::toIntNum(hal::ATMEGA640_1280_2560::Interrupt::USART0_UART_DATA_REGISTER_EMPTY),
                      hal::ATMEGA640_1280_2560::toIntNum(hal::ATMEGA640_1280_2560::Interrupt::USART0_RECEIVE_COMPLETE        )> UART0;

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA640_1280_2560 */

} /* blox */

} /* spectre */

#endif /* INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATMEGA640_1280_2560_UART0_H_ */
