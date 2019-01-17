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

#ifndef INCLUDE_SNOWFOX_BLOX_HAL_AVR_COMMON_ATMEGA640_1280_2560_UART2_H_
#define INCLUDE_SNOWFOX_BLOX_HAL_AVR_COMMON_ATMEGA640_1280_2560_UART2_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/blox/hal/avr/common/ATxxxx/UART2.hpp>

#include <snowfox/hal/avr/common/ATMEGA640_1280_2560/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace blox
{

namespace ATMEGA640_1280_2560
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef ATxxxx::UART2<hal::ATMEGA640_1280_2560::toIntNum(hal::ATMEGA640_1280_2560::Interrupt::USART2_UART_DATA_REGISTER_EMPTY),
                      hal::ATMEGA640_1280_2560::toIntNum(hal::ATMEGA640_1280_2560::Interrupt::USART2_RECEIVE_COMPLETE        )> UART2;

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA640_1280_2560 */

} /* blox */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_BLOX_HAL_AVR_COMMON_ATMEGA640_1280_2560_UART2_H_ */
