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

#ifndef INCLUDE_SPECTRE_HAL_AVR_AT90CAN32_TIMER3_H_
#define INCLUDE_SPECTRE_HAL_AVR_AT90CAN32_TIMER3_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/AT90CAN32_64_128/TIMER3.h>

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

class TIMER3 : public AT90CAN32_64_128::TIMER3
{

public:

           TIMER3(volatile uint16_t * TCNT3, volatile uint8_t  * TCCR3B, volatile uint16_t * OCR3A, volatile uint16_t * OCR3B, volatile uint16_t * OCR3C) : AT90CAN32_64_128::TIMER3(TCNT3, TCCR3B, OCR3A, OCR3B, OCR3C) { }
  virtual ~TIMER3() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN32 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_AT90CAN32_TIMER3_H_ */
