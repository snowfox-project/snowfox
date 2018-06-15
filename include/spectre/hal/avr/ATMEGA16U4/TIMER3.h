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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATMEGA16U4_TIMER3_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATMEGA16U4_TIMER3_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/common/ATMEGA16U4_32U4/TIMER3.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA16U4
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class TIMER3 : public ATMEGA16U4_32U4::TIMER3
{

public:

           TIMER3(volatile uint16_t * tcnt3,
                  volatile uint8_t  * tccr3b,
                  volatile uint16_t * ocr3a,
                  volatile uint16_t * ocr3b,
                  volatile uint16_t * ocr3c) : ATMEGA16U4_32U4::TIMER3(tcnt3, tccr3b, ocr3a, ocr3b, ocr3c) { }
  virtual ~TIMER3() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA16U4 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATMEGA16U4_TIMER3_H_ */
