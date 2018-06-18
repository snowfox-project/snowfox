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

#ifndef INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_INTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_INTERRUPTCONTROLLER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/AT90CAN32_64_128/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace AT90CAN128
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef AT90CAN32_64_128::Interrupt               Interrupt;
typedef AT90CAN32_64_128::InterruptServiceRoutine InterruptServiceRoutine;

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class InterruptController : public AT90CAN32_64_128::InterruptController
{

public:

           InterruptController(volatile uint8_t * eimsk,
                               volatile uint8_t * timsk2,
                               volatile uint8_t * timsk1,
                               volatile uint8_t * timsk0,
                               volatile uint8_t * cangie,
                               volatile uint8_t * spcr,
                               volatile uint8_t * ucsr0b,
                               volatile uint8_t * acsr,
                               volatile uint8_t * adcsra,
                               volatile uint8_t * eecr,
                               volatile uint8_t * timsk3,
                               volatile uint8_t * ucsr1b,
                               volatile uint8_t * twcr,
                               volatile uint8_t * spmcsr) : AT90CAN32_64_128::InterruptController(eimsk, timsk2, timsk1, timsk0, cangie, spcr, ucsr0b, acsr, adcsra, eecr, timsk3, ucsr1b, twcr, spmcsr) { }
  virtual ~InterruptController() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN128 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_INTERRUPTCONTROLLER_H_ */
