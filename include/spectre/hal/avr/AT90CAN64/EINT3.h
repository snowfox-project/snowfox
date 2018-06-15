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

#ifndef INCLUDE_SPECTRE_HAL_AVR_AT90CAN64_EINT3_H_
#define INCLUDE_SPECTRE_HAL_AVR_AT90CAN64_EINT3_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/common/AT90CAN32_64_128/EINT3.h>

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

class EINT3 : public AT90CAN32_64_128::EINT3
{

public:

          EINT3(volatile uint8_t * eicra, interface::InterruptController & int_ctrl) : AT90CAN32_64_128::EINT3(eicra, int_ctrl) { }
  virtual EINT3() { }

};

/**************************************************************************************/

class EINT3_ExternalInterruptEventCallback : public AT90CAN32_64_128::EINT3_ExternalInterruptEventCallback
{

public:

           EINT3_ExternalInterruptEventCallback(EINT3 & eint3) : AT90CAN32_64_128::EINT3_ExternalInterruptEventCallback(eint3) { }
  virtual ~EINT3_ExternalInterruptEventCallback() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN64 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_AT90CAN64_EINT3_H_ */
