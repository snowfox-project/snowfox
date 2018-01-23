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

#ifndef TEST_INCLUDE_HAL_AVR_AT90CAN128_REGISTERRESETVALUELIST_H_
#define TEST_INCLUDE_HAL_AVR_AT90CAN128_REGISTERRESETVALUELIST_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace AT90CAN128
{

namespace test
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

/* TIMER3 */
static uint16_t const TCNT3_RESET_VALUE   = 0;
static uint8_t  const TCCR3B_RESET_VALUE  = 0b00000000;
static uint16_t const OCR3A_RESET_VALUE   = 0;
static uint16_t const OCR3B_RESET_VALUE   = 0;
static uint16_t const OCR3C_RESET_VALUE   = 0;

/* TIMER2 */
static uint8_t  const TCNT2_RESET_VALUE   = 0;
static uint8_t  const TCCR2A_RESET_VALUE  = 0b00000000;
static uint8_t  const OCR2A_RESET_VALUE   = 0;

/* TIMER1 */
static uint16_t const TCNT1_RESET_VALUE   = 0;
static uint8_t  const TCCR1B_RESET_VALUE  = 0b00000000;
static uint16_t const OCR1A_RESET_VALUE   = 0;
static uint16_t const OCR1B_RESET_VALUE   = 0;
static uint16_t const OCR1C_RESET_VALUE   = 0;

/* TIMER0 */
static uint8_t  const TCNT0_RESET_VALUE   = 0;
static uint8_t  const TCCR0A_RESET_VALUE  = 0b00000000;
static uint8_t  const OCR0A_RESET_VALUE   = 0;

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

} /* test */

} /* AT90CAN128 */

} /* hal */

} /* spectre */

#endif /* TEST_INCLUDE_HAL_AVR_AT90CAN128_REGISTERRESETVALUELIST_H_ */