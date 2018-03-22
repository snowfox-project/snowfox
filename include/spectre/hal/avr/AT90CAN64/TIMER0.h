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

#ifndef INCLUDE_SPECTRE_HAL_AVR_AT90CAN64_TIMER0_H_
#define INCLUDE_SPECTRE_HAL_AVR_AT90CAN64_TIMER0_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/AT90CANxxxx/TIMER0.h>

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

class TIMER0 : public AT90CANxxxx::TIMER0

{

public:

           TIMER0(volatile uint8_t * TCNT0, volatile uint8_t * TCCR0A, volatile uint8_t * OCR0A) : AT90CANxxxx::TIMER0(TCNT0, TCCR0A, OCR0A) { }
  virtual ~TIMER0() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN64 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_AT90CAN64_TIMER0_H_ */
