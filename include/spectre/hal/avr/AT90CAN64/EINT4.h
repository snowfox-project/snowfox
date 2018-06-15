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

#ifndef INCLUDE_SPECTRE_HAL_AVR_AT90CAN64_EINT4_H_
#define INCLUDE_SPECTRE_HAL_AVR_AT90CAN64_EINT4_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/common/AT90CAN32_64_128/EINT4.h>

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

class EINT4 : public AT90CAN32_64_128::EINT4
{

public:

          EINT4(volatile uint8_t * eicrb, interface::InterruptController & int_ctrl) : AT90CAN32_64_128::EINT4(eicrb, int_ctrl) { }
  virtual EINT4() { }

};

/**************************************************************************************/

class EINT4_ExternalInterruptEventCallback : public AT90CAN32_64_128::EINT4_ExternalInterruptEventCallback
{

public:

           EINT4_ExternalInterruptEventCallback(EINT4 & eint4) : AT90CAN32_64_128::EINT4_ExternalInterruptEventCallback(eint4) { }
  virtual ~EINT4_ExternalInterruptEventCallback() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN64 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_AT90CAN64_EINT4_H_ */
