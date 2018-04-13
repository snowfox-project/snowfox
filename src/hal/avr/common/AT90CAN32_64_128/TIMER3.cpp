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

#include <spectre/hal/avr/common/AT90CAN32_64_128/TIMER3.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace AT90CAN32_64_128
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* TCCR3B */
#define CS30_bm   (1<<0)
#define CS31_bm   (1<<1)
#define CS32_bm   (1<<2)

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  TIMER3_Prescaler_0     = 0,
  TIMER3_Prescaler_1     =                     CS30_bm,
  TIMER3_Prescaler_8     =           CS31_bm,
  TIMER3_Prescaler_64    =           CS31_bm | CS30_bm,
  TIMER3_Prescaler_256   = CS32_bm,
  TIMER3_Prescaler_1024  = CS32_bm |           CS30_bm
} TIMER3PrescalerSelect;

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

TIMER3::TIMER3(volatile uint16_t * TCNT3,
               volatile uint8_t  * TCCR3B,
               volatile uint16_t * OCR3A,
               volatile uint16_t * OCR3B,
               volatile uint16_t * OCR3C)
: _prescaler(0     ),
  _TCNT3    (TCNT3 ),
  _TCCR3B   (TCCR3B),
  _OCR3A    (OCR3A ),
  _OCR3B    (OCR3B ),
  _OCR3C    (OCR3C )
{

}

TIMER3::~TIMER3()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void TIMER3::start()
{
  setPrescaler_TCCR3B(_prescaler);
}

void TIMER3::stop()
{
  setPrescaler_TCCR3B(0);
}

void TIMER3::set(uint16_t const val)
{
  *_TCNT3 = val;
}

uint16_t TIMER3::get()
{
  return *_TCNT3;
}

void TIMER3::setCompareRegister(uint8_t const reg_sel, uint16_t const reg_val)
{
  switch(reg_sel)
  {
  case COMPARE_A: *_OCR3A = reg_val; break;
  case COMPARE_B: *_OCR3B = reg_val; break;
  case COMPARE_C: *_OCR3C = reg_val; break;
  }
}

void TIMER3::setPrescaler(uint32_t const prescaler)
{
  _prescaler = prescaler;
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

void TIMER3::setPrescaler_TCCR3B(uint32_t const prescaler)
{
  *_TCCR3B &= ~(CS32_bm | CS31_bm | CS30_bm);

  switch(prescaler)
  {
  case 0    : *_TCCR3B |= static_cast<uint8_t>(TIMER3_Prescaler_0   ); break;
  case 1    : *_TCCR3B |= static_cast<uint8_t>(TIMER3_Prescaler_1   ); break;
  case 8    : *_TCCR3B |= static_cast<uint8_t>(TIMER3_Prescaler_8   ); break;
  case 64   : *_TCCR3B |= static_cast<uint8_t>(TIMER3_Prescaler_64  ); break;
  case 256  : *_TCCR3B |= static_cast<uint8_t>(TIMER3_Prescaler_256 ); break;
  case 1024 : *_TCCR3B |= static_cast<uint8_t>(TIMER3_Prescaler_1024); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN32_64_128 */

} /* hal */

} /* spectre */
