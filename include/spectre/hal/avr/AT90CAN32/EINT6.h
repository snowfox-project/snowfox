/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SPECTRE_HAL_AVR_AT90CAN32_EINT6_H_
#define INCLUDE_SPECTRE_HAL_AVR_AT90CAN32_EINT6_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/AT90CAN32_64_128/EINT6.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace AT90CAN32
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class EINT6 : public AT90CAN32_64_128::EINT6
{

public:

          EINT6(volatile uint8_t * eicrb, interface::InterruptController & int_ctrl) : AT90CAN32_64_128::EINT6(eicrb, int_ctrl) { }
  virtual EINT6() { }

};

/**************************************************************************************/

class EINT6_ExternalInterruptEventCallback : public AT90CAN32_64_128::EINT6_ExternalInterruptEventCallback
{

public:

           EINT6_ExternalInterruptEventCallback(EINT6 & eint6) : AT90CAN32_64_128::EINT6_ExternalInterruptEventCallback(eint6) { }
  virtual ~EINT6_ExternalInterruptEventCallback() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN32 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_AT90CAN32_EINT6_H_ */
