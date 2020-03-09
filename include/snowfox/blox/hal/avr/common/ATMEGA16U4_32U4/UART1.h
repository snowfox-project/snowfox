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

#ifndef INCLUDE_SNOWFOX_BLOX_HAL_AVR_COMMON_ATMEGA16U4_32U4_UART1_H_
#define INCLUDE_SNOWFOX_BLOX_HAL_AVR_COMMON_ATMEGA16U4_32U4_UART1_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/blox/hal/avr/common/ATxxxx/UART1.hpp>

#include <snowfox/hal/avr/common/ATMEGA16U4_32U4/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace blox
{

namespace ATMEGA16U4_32U4
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef ATxxxx::UART1<hal::ATMEGA16U4_32U4::toIntNum(hal::ATMEGA16U4_32U4::Interrupt::USART1_UART_DATA_REGISTER_EMPTY),
                      hal::ATMEGA16U4_32U4::toIntNum(hal::ATMEGA16U4_32U4::Interrupt::USART1_RECEIVE_COMPLETE        )> UART1;

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA16U4_32U4 */

} /* blox */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_BLOX_HAL_AVR_COMMON_ATMEGA16U4_32U4_UART1_H_ */
