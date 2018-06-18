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

#ifndef INCLUDE_SPECTRE_HAL_AVR_AT90CAN64_EINT7_H_
#define INCLUDE_SPECTRE_HAL_AVR_AT90CAN64_EINT7_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/AT90CAN32_64_128/EINT7.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace AT90CAN64
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class EINT7 : public AT90CAN32_64_128::EINT7
{

public:

          EINT7(volatile uint8_t * eicrb, interface::InterruptController & int_ctrl) : AT90CAN32_64_128::EINT7(eicrb, int_ctrl) { }
  virtual EINT7() { }

};

/**************************************************************************************/

class EINT7_ExternalInterruptEventCallback : public AT90CAN32_64_128::EINT7_ExternalInterruptEventCallback
{

public:

           EINT7_ExternalInterruptEventCallback(EINT7 & eint7) : AT90CAN32_64_128::EINT7_ExternalInterruptEventCallback(eint7) { }
  virtual ~EINT7_ExternalInterruptEventCallback() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN64 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_AT90CAN64_EINT7_H_ */
