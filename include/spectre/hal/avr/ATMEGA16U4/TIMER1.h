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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATMEGA16U4_TIMER1_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATMEGA16U4_TIMER1_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/common/ATMEGA16U4_32U4/TIMER1.h>

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

class TIMER1 : public ATMEGA16U4_32U4::TIMER1
{

public:

           TIMER1(volatile uint16_t * tcnt1,
                  volatile uint8_t  * tccr1b,
                  volatile uint16_t * ocr1a,
                  volatile uint16_t * ocr1b,
                  volatile uint16_t * ocr1c) : ATMEGA16U4_32U4::TIMER1(tcnt1, tccr1b, ocr1a, ocr1b, ocr1c) { }
  virtual ~TIMER1() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA16U4 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATMEGA16U4_TIMER1_H_ */
