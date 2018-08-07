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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATMEGA644P_EXTERNALINTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATMEGA644P_EXTERNALINTERRUPTCONTROLLER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/ATMEGA164P_324P_644P_1284P/ExternalInterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA644P
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef ATMEGA164P_324P_644P_1284P::ExternalInterrupt                         ExternalInterrupt;
typedef ATMEGA164P_324P_644P_1284P::ExternalInterruptController               ExternalInterruptController;
typedef ATMEGA164P_324P_644P_1284P::EINT0_ExternalInterruptEventCallback      EINT0_ExternalInterruptEventCallback;
typedef ATMEGA164P_324P_644P_1284P::EINT1_ExternalInterruptEventCallback      EINT1_ExternalInterruptEventCallback;
typedef ATMEGA164P_324P_644P_1284P::EINT2_ExternalInterruptEventCallback      EINT2_ExternalInterruptEventCallback;
typedef ATMEGA164P_324P_644P_1284P::PinChange0_ExternalInterruptEventCallback PinChange0_ExternalInterruptEventCallback;
typedef ATMEGA164P_324P_644P_1284P::PinChange1_ExternalInterruptEventCallback PinChange1_ExternalInterruptEventCallback;
typedef ATMEGA164P_324P_644P_1284P::PinChange2_ExternalInterruptEventCallback PinChange2_ExternalInterruptEventCallback;
typedef ATMEGA164P_324P_644P_1284P::PinChange3_ExternalInterruptEventCallback PinChange3_ExternalInterruptEventCallback;

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA644P */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATMEGA644P_EXTERNALINTERRUPTCONTROLLER_H_ */
