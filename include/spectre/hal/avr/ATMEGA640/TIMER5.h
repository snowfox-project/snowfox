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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATMEGA640_TIMER5_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATMEGA640_TIMER5_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/common/ATMEGA640_1280_2560/TIMER5.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA640
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class TIMER5 : public ATMEGA640_1280_2560::TIMER5
{

public:

           TIMER5(volatile uint16_t * tcnt5,
                  volatile uint8_t  * tccr5b,
                  volatile uint16_t * ocr5a,
                  volatile uint16_t * ocr5b,
                  volatile uint16_t * ocr5c) : ATMEGA640_1280_2560::TIMER5(tcnt5, tccr5b, ocr5a, ocr5b, ocr5c) { }
  virtual ~TIMER5() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA640 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATMEGA640_TIMER5_H_ */
