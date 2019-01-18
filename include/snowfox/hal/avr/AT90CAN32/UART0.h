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

#ifndef INCLUDE_SNOWFOX_HAL_AVR_AT90CAN32_UART0_H_
#define INCLUDE_SNOWFOX_HAL_AVR_AT90CAN32_UART0_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/avr/common/ATxxxx/UART0.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace AT90CAN32
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef ATxxxx::UART0                               UART0;
typedef ATxxxx::UART0_TransmitRegisterEmptyCallback UART0_TransmitRegisterEmptyCallback;
typedef ATxxxx::UART0_ReceiveCompleteCallback       UART0_ReceiveCompleteCallback;

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN32 */

} /* hal */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_HAL_AVR_AT90CAN32_UART0_H_ */
