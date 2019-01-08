/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2019 Alexander Entinger / LXRobotics GmbH
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
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/ATMEGA16U4_32U4/TIMER0.h>

#include <spectre/cpu/avr/io/common/ATMEGA16U4_32U4.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA16U4_32U4
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Timer0Prescaler : uint8_t
{
  P_0    = 0,
  P_1    =                     CS00_bm,
  P_8    =           CS01_bm,
  P_64   =           CS01_bm | CS00_bm,
  P_256  = CS02_bm,
  P_1024 = CS02_bm |           CS00_bm
};

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

TIMER0::TIMER0(volatile uint8_t * tcnt0,
               volatile uint8_t * tccr0b,
               volatile uint8_t * ocr0a,
               volatile uint8_t * ocr0b)
: _prescaler(0     ),
  _TCNT0    (tcnt0 ),
  _TCCR0B   (tccr0b),
  _OCR0A    (ocr0a ),
  _OCR0B    (ocr0b )
{

}

TIMER0::~TIMER0()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void TIMER0::start()
{
  setPrescaler_TCCR0B(_prescaler);
}

void TIMER0::stop()
{
  setPrescaler_TCCR0B(0);
}

void TIMER0::set(uint8_t const val)
{
  *_TCNT0 = val;
}

uint8_t TIMER0::get()
{
  return *_TCNT0;
}

void TIMER0::setCompareRegister(uint8_t const reg_sel, uint8_t const reg_val)
{
  switch(reg_sel)
  {
  case COMPARE_A: *_OCR0A = reg_val; break;
  case COMPARE_B: *_OCR0B = reg_val; break;
  }
}

void TIMER0::setPrescaler(uint32_t const prescaler)
{
  _prescaler = prescaler;
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

void TIMER0::setPrescaler_TCCR0B(uint32_t const prescaler)
{
  *_TCCR0B &= ~(CS02_bm | CS01_bm | CS00_bm);

  switch(prescaler)
  {
  case 0    : *_TCCR0B |= static_cast<uint8_t>(Timer0Prescaler::P_0   ); break;
  case 1    : *_TCCR0B |= static_cast<uint8_t>(Timer0Prescaler::P_1   ); break;
  case 8    : *_TCCR0B |= static_cast<uint8_t>(Timer0Prescaler::P_8   ); break;
  case 64   : *_TCCR0B |= static_cast<uint8_t>(Timer0Prescaler::P_64  ); break;
  case 256  : *_TCCR0B |= static_cast<uint8_t>(Timer0Prescaler::P_256 ); break;
  case 1024 : *_TCCR0B |= static_cast<uint8_t>(Timer0Prescaler::P_1024); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA16U4_32U4 */

} /* hal */

} /* spectre */
