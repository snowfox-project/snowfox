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

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/ATMEGA2560/TIMER5.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA2560
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* TCCR5B */
#define CS50_bm   (1<<0)
#define CS51_bm   (1<<1)
#define CS52_bm   (1<<2)

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  TIMER5_Prescaler_0     = 0,
  TIMER5_Prescaler_1     =                     CS50_bm,
  TIMER5_Prescaler_8     =           CS51_bm,
  TIMER5_Prescaler_64    =           CS51_bm | CS50_bm,
  TIMER5_Prescaler_256   = CS52_bm,
  TIMER5_Prescaler_1024  = CS52_bm |           CS50_bm
} TIMER5PrescalerSelect;

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

TIMER5::TIMER5(volatile uint16_t * TCNT5,
               volatile uint8_t  * TCCR5B,
               volatile uint16_t * OCR5A,
               volatile uint16_t * OCR5B,
               volatile uint16_t * OCR5C)
: _prescaler(0     ),
  _TCNT5    (TCNT5 ),
  _TCCR5B   (TCCR5B),
  _OCR5A    (OCR5A ),
  _OCR5B    (OCR5B ),
  _OCR5C    (OCR5C )
{

}

TIMER5::~TIMER5()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void TIMER5::start()
{
  setPrescaler_TCCR5B(_prescaler);
}

void TIMER5::stop()
{
  setPrescaler_TCCR5B(0);
}

void TIMER5::set(uint16_t const val)
{
  *_TCNT5 = val;
}

uint16_t TIMER5::get()
{
  return *_TCNT5;
}

void TIMER5::setCompareRegister(uint8_t const reg_sel, uint16_t const reg_val)
{
  switch(reg_sel)
  {
  case COMPARE_A: *_OCR5A = reg_val; break;
  case COMPARE_B: *_OCR5B = reg_val; break;
  case COMPARE_C: *_OCR5C = reg_val; break;
  }
}

void TIMER5::setPrescaler(uint32_t const prescaler)
{
  _prescaler = prescaler;
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

void TIMER5::setPrescaler_TCCR5B(uint32_t const prescaler)
{
  *_TCCR5B &= ~(CS52_bm | CS51_bm | CS50_bm);

  switch(prescaler)
  {
  case 0    : *_TCCR5B |= static_cast<uint8_t>(TIMER5_Prescaler_0   ); break;
  case 1    : *_TCCR5B |= static_cast<uint8_t>(TIMER5_Prescaler_1   ); break;
  case 8    : *_TCCR5B |= static_cast<uint8_t>(TIMER5_Prescaler_8   ); break;
  case 64   : *_TCCR5B |= static_cast<uint8_t>(TIMER5_Prescaler_64  ); break;
  case 256  : *_TCCR5B |= static_cast<uint8_t>(TIMER5_Prescaler_256 ); break;
  case 1024 : *_TCCR5B |= static_cast<uint8_t>(TIMER5_Prescaler_1024); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA2560 */

} /* hal */

} /* spectre */