/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SNOWFOX_BLOX_HAL_AVR_COMMON_AT90CAN32_64_128_UART0_H_
#define INCLUDE_SNOWFOX_BLOX_HAL_AVR_COMMON_AT90CAN32_64_128_UART0_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/blox/hal/avr/common/ATxxxx/UART0.hpp>

#include <snowfox/hal/avr/common/AT90CAN32_64_128/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::blox::AT90CAN32_64_128
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef ATxxxx::UART0<hal::AT90CAN32_64_128::toIntNum(hal::AT90CAN32_64_128::Interrupt::USART0_UART_DATA_REGISTER_EMPTY),
                      hal::AT90CAN32_64_128::toIntNum(hal::AT90CAN32_64_128::Interrupt::USART0_RECEIVE_COMPLETE        )> UART0;

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::blox::AT90CAN32_64_128 */

#endif /* INCLUDE_SNOWFOX_BLOX_HAL_AVR_COMMON_AT90CAN32_64_128_UART0_H_ */
