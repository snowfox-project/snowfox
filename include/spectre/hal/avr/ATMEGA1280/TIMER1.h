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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATMEGA1280_TIMER1_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATMEGA1280_TIMER1_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/common/ATMEGA640_1280_2560/TIMER1.h>

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
 * CLASS DECLARATION
 **************************************************************************************/

class TIMER1 : ATMEGA640_1280_2560::TIMER1
{

public:

           TIMER1(volatile uint16_t * tcnt1,
                  volatile uint8_t  * tccr1b,
                  volatile uint16_t * ocr1a,
                  volatile uint16_t * ocr1b,
                  volatile uint16_t * ocr1c) : ATMEGA640_1280_2560::TIMER1(tcnt1, tccr1b, ocr1a, ocr1b, ocr1c) { }
  virtual ~TIMER1() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA1280 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATMEGA1280_TIMER1_H_ */