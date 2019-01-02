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

#include <spectre/hal/avr/common/ATMEGA164P_324P_644P_1284P/TIMER2.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA164P_324P_644P_1284P
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* TCCR2A */
#define CS20_bm   (1<<0)
#define CS21_bm   (1<<1)
#define CS22_bm   (1<<2)

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef enum
{
  TIMER2_Prescaler_0     = 0,
  TIMER2_Prescaler_1     =                     CS20_bm,
  TIMER2_Prescaler_8     =           CS21_bm,
  TIMER2_Prescaler_32    =           CS21_bm | CS20_bm,
  TIMER2_Prescaler_64    = CS22_bm,
  TIMER2_Prescaler_128   = CS22_bm |           CS20_bm,
  TIMER2_Prescaler_256   = CS22_bm | CS21_bm,
  TIMER2_Prescaler_1024  = CS22_bm | CS21_bm | CS20_bm
} TIMER2PrescalerSelect;

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

TIMER2::TIMER2(volatile uint8_t * tcnt2,
               volatile uint8_t * tccr2a,
               volatile uint8_t * ocr2a,
               volatile uint8_t * ocr2b)
: _prescaler(0     ),
  _TCNT2    (tcnt2 ),
  _TCCR2A   (tccr2a),
  _OCR2A    (ocr2a ),
  _OCR2B    (ocr2b )
{

}

TIMER2::~TIMER2()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void TIMER2::start()
{
  setPrescaler_TCCR2A(_prescaler);
}

void TIMER2::stop()
{
  setPrescaler_TCCR2A(0);
}

void TIMER2::set(uint8_t const val)
{
  *_TCNT2 = val;
}

uint8_t TIMER2::get()
{
  return *_TCNT2;
}

void TIMER2::setCompareRegister(uint8_t const reg_sel, uint8_t const reg_val)
{
  switch(reg_sel)
  {
  case COMPARE_A: *_OCR2A = reg_val; break;
  case COMPARE_B: *_OCR2B = reg_val; break;
  }
}

void TIMER2::setPrescaler(uint32_t const prescaler)
{
  _prescaler = prescaler;
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

void TIMER2::setPrescaler_TCCR2A(uint32_t const prescaler)
{
  *_TCCR2A &= ~(CS22_bm | CS21_bm | CS20_bm);

  switch(prescaler)
  {
  case 0    : *_TCCR2A |= static_cast<uint8_t>(TIMER2_Prescaler_0   ); break;
  case 1    : *_TCCR2A |= static_cast<uint8_t>(TIMER2_Prescaler_1   ); break;
  case 8    : *_TCCR2A |= static_cast<uint8_t>(TIMER2_Prescaler_8   ); break;
  case 32   : *_TCCR2A |= static_cast<uint8_t>(TIMER2_Prescaler_32  ); break;
  case 64   : *_TCCR2A |= static_cast<uint8_t>(TIMER2_Prescaler_64  ); break;
  case 128  : *_TCCR2A |= static_cast<uint8_t>(TIMER2_Prescaler_128 ); break;
  case 256  : *_TCCR2A |= static_cast<uint8_t>(TIMER2_Prescaler_256 ); break;
  case 1024 : *_TCCR2A |= static_cast<uint8_t>(TIMER2_Prescaler_1024); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA164P_324P_644P_1284P */

} /* hal */

} /* spectre */
