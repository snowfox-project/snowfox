/**
 * Snowfox is a modular RTOS with extensive IO support.
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

#include <snowfox/hal/avr/common/ATMEGA640_1280_2560/TIMER4.h>

#include <snowfox/cpu/avr/io/common/ATMEGA640_1280_2560.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace ATMEGA640_1280_2560
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Timer4Prescaler : uint8_t
{
  P_0    = 0,
  P_1    =                     CS40_bm,
  P_8    =           CS41_bm,
  P_64   =           CS41_bm | CS40_bm,
  P_256  = CS42_bm,
  P_1024 = CS42_bm |           CS40_bm
};

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

TIMER4::TIMER4(volatile uint16_t * tcnt4,
               volatile uint8_t  * tccr4b,
               volatile uint16_t * ocr4a,
               volatile uint16_t * ocr4b,
               volatile uint16_t * ocr4c)
: _prescaler(0     ),
  _TCNT4    (tcnt4 ),
  _TCCR4B   (tccr4b),
  _OCR4A    (ocr4a ),
  _OCR4B    (ocr4b ),
  _OCR4C    (ocr4c )
{

}

TIMER4::~TIMER4()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void TIMER4::start()
{
  setPrescaler_TCCR4B(_prescaler);
}

void TIMER4::stop()
{
  setPrescaler_TCCR4B(0);
}

void TIMER4::set(uint16_t const val)
{
  *_TCNT4 = val;
}

uint16_t TIMER4::get()
{
  return *_TCNT4;
}

void TIMER4::setCompareRegister(uint8_t const reg_sel, uint16_t const reg_val)
{
  switch(reg_sel)
  {
  case COMPARE_A: *_OCR4A = reg_val; break;
  case COMPARE_B: *_OCR4B = reg_val; break;
  case COMPARE_C: *_OCR4C = reg_val; break;
  }
}

void TIMER4::setPrescaler(uint32_t const prescaler)
{
  _prescaler = prescaler;
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

void TIMER4::setPrescaler_TCCR4B(uint32_t const prescaler)
{
  *_TCCR4B &= ~(CS42_bm | CS41_bm | CS40_bm);

  switch(prescaler)
  {
  case 0    : *_TCCR4B |= static_cast<uint8_t>(Timer4Prescaler::P_0   ); break;
  case 1    : *_TCCR4B |= static_cast<uint8_t>(Timer4Prescaler::P_1   ); break;
  case 8    : *_TCCR4B |= static_cast<uint8_t>(Timer4Prescaler::P_8   ); break;
  case 64   : *_TCCR4B |= static_cast<uint8_t>(Timer4Prescaler::P_64  ); break;
  case 256  : *_TCCR4B |= static_cast<uint8_t>(Timer4Prescaler::P_256 ); break;
  case 1024 : *_TCCR4B |= static_cast<uint8_t>(Timer4Prescaler::P_1024); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA640_1280_2560 */

} /* hal */

} /* snowfox */
