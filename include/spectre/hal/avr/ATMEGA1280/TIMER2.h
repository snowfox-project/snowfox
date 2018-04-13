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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATMEGA1280_TIMER2_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATMEGA1280_TIMER2_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/common/ATMEGA640_1280_2560/TIMER2.h>

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

class TIMER2 : public ATMEGA640_1280_2560::TIMER2
{

public:

           TIMER2(volatile uint8_t * tcnt2,
                  volatile uint8_t * tccr2a,
                  volatile uint8_t * ocr2a,
                  volatile uint8_t * ocr2b) : ATMEGA640_1280_2560::TIMER2(tcnt2, tccr2a, ocr2a, ocr2b) { }
  virtual ~TIMER2() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA1280 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATMEGA1280_TIMER2_H_ */
