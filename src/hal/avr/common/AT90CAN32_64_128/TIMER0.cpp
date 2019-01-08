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

#include <spectre/hal/avr/common/AT90CAN32_64_128/TIMER0.h>

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

/* TCCR0A */
#define CS00_bm   (1<<0)
#define CS01_bm   (1<<1)
#define CS02_bm   (1<<2)

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

TIMER0::TIMER0(volatile uint8_t * TCNT0,
               volatile uint8_t * TCCR0A,
               volatile uint8_t * OCR0A)
: _prescaler(0     ),
  _TCNT0    (TCNT0 ),
  _TCCR0A   (TCCR0A),
  _OCR0A    (OCR0A )
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
  setPrescaler_TCCR0A(_prescaler);
}

void TIMER0::stop()
{
  setPrescaler_TCCR0A(0);
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
  }
}

void TIMER0::setPrescaler(uint32_t const prescaler)
{
  _prescaler = prescaler;
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

void TIMER0::setPrescaler_TCCR0A(uint32_t const prescaler)
{
  *_TCCR0A &= ~(CS02_bm | CS01_bm | CS00_bm);

  switch(prescaler)
  {
  case 0    : *_TCCR0A |= static_cast<uint8_t>(Timer0Prescaler::P_0   ); break;
  case 1    : *_TCCR0A |= static_cast<uint8_t>(Timer0Prescaler::P_1   ); break;
  case 8    : *_TCCR0A |= static_cast<uint8_t>(Timer0Prescaler::P_8   ); break;
  case 64   : *_TCCR0A |= static_cast<uint8_t>(Timer0Prescaler::P_64  ); break;
  case 256  : *_TCCR0A |= static_cast<uint8_t>(Timer0Prescaler::P_256 ); break;
  case 1024 : *_TCCR0A |= static_cast<uint8_t>(Timer0Prescaler::P_1024); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN32_64_128 */

} /* hal */

} /* spectre */
