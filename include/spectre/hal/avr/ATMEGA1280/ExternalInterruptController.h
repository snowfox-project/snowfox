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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATMEGA1280_EXTERNALINTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATMEGA1280_EXTERNALINTERRUPTCONTROLLER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/ATMEGA640_1280_2560/ExternalInterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA1280
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef ATMEGA640_1280_2560::ExternalInterrupt                         ExternalInterrupt;
typedef ATMEGA640_1280_2560::ExternalInterruptController               ExternalInterruptController;
typedef ATMEGA640_1280_2560::EINT0_ExternalInterruptEventCallback      EINT0_ExternalInterruptEventCallback;
typedef ATMEGA640_1280_2560::EINT1_ExternalInterruptEventCallback      EINT1_ExternalInterruptEventCallback;
typedef ATMEGA640_1280_2560::EINT2_ExternalInterruptEventCallback      EINT2_ExternalInterruptEventCallback;
typedef ATMEGA640_1280_2560::EINT3_ExternalInterruptEventCallback      EINT3_ExternalInterruptEventCallback;
typedef ATMEGA640_1280_2560::EINT4_ExternalInterruptEventCallback      EINT4_ExternalInterruptEventCallback;
typedef ATMEGA640_1280_2560::EINT5_ExternalInterruptEventCallback      EINT5_ExternalInterruptEventCallback;
typedef ATMEGA640_1280_2560::EINT6_ExternalInterruptEventCallback      EINT6_ExternalInterruptEventCallback;
typedef ATMEGA640_1280_2560::EINT7_ExternalInterruptEventCallback      EINT7_ExternalInterruptEventCallback;
typedef ATMEGA640_1280_2560::PinChange0_ExternalInterruptEventCallback PinChange0_ExternalInterruptEventCallback;
typedef ATMEGA640_1280_2560::PinChange1_ExternalInterruptEventCallback PinChange1_ExternalInterruptEventCallback;
typedef ATMEGA640_1280_2560::PinChange2_ExternalInterruptEventCallback PinChange2_ExternalInterruptEventCallback;

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA1280 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATMEGA1280_EXTERNALINTERRUPTCONTROLLER_H_ */
