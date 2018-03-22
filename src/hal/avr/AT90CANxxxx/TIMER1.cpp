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

#include <spectre/hal/avr/AT90CANxxxx/TIMER1.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace AT90CANxxxx
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* TCCR1B */
#define CS10_bm   (1<<0)
#define CS11_bm   (1<<1)
#define CS12_bm   (1<<2)

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  TIMER1_Prescaler_0     = 0,
  TIMER1_Prescaler_1     =                     CS10_bm,
  TIMER1_Prescaler_8     =           CS11_bm,
  TIMER1_Prescaler_64    =           CS11_bm | CS10_bm,
  TIMER1_Prescaler_256   = CS12_bm,
  TIMER1_Prescaler_1024  = CS12_bm |           CS10_bm
} Timer1PrescalerSelect;

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

TIMER1::TIMER1(volatile uint16_t * TCNT1,
               volatile uint8_t  * TCCR1B,
               volatile uint16_t * OCR1A,
               volatile uint16_t * OCR1B,
               volatile uint16_t * OCR1C)
: _prescaler(0     ),
  _TCNT1    (TCNT1 ),
  _TCCR1B   (TCCR1B),
  _OCR1A    (OCR1A ),
  _OCR1B    (OCR1B ),
  _OCR1C    (OCR1C )
{

}

TIMER1::~TIMER1()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void TIMER1::start()
{
  setPrescaler_TCCR1B(_prescaler);
}

void TIMER1::stop()
{
  setPrescaler_TCCR1B(0);
}

void TIMER1::set(uint16_t const val)
{
  *_TCNT1 = val;
}

uint16_t TIMER1::get()
{
  return *_TCNT1;
}

void TIMER1::setCompareRegister(uint8_t const reg_sel, uint16_t const reg_val)
{
  switch(reg_sel)
  {
  case COMPARE_A: *_OCR1A = reg_val; break;
  case COMPARE_B: *_OCR1B = reg_val; break;
  case COMPARE_C: *_OCR1C = reg_val; break;
  }
}

void TIMER1::setPrescaler(uint32_t const prescaler)
{
  _prescaler = prescaler;
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

void TIMER1::setPrescaler_TCCR1B(uint32_t const prescaler)
{
  *_TCCR1B &= ~(CS12_bm | CS11_bm | CS10_bm);

  switch(prescaler)
  {
  case 0    : *_TCCR1B |= static_cast<uint8_t>(TIMER1_Prescaler_0   ); break;
  case 1    : *_TCCR1B |= static_cast<uint8_t>(TIMER1_Prescaler_1   ); break;
  case 8    : *_TCCR1B |= static_cast<uint8_t>(TIMER1_Prescaler_8   ); break;
  case 64   : *_TCCR1B |= static_cast<uint8_t>(TIMER1_Prescaler_64  ); break;
  case 256  : *_TCCR1B |= static_cast<uint8_t>(TIMER1_Prescaler_256 ); break;
  case 1024 : *_TCCR1B |= static_cast<uint8_t>(TIMER1_Prescaler_1024); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CANxxxx */

} /* hal */

} /* spectre */
