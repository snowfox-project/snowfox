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

#include <snowfox/hal/avr/common/ATMEGA640_1280_2560/TIMER3.h>

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

enum class Timer3Prescaler : uint8_t
{
  P_0    = 0,
  P_1    =                     CS30_bm,
  P_8    =           CS31_bm,
  P_64   =           CS31_bm | CS30_bm,
  P_256  = CS32_bm,
  P_1024 = CS32_bm |           CS30_bm
};

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

TIMER3::TIMER3(volatile uint16_t * tcnt3,
               volatile uint8_t  * tccr3a,
               volatile uint16_t * ocr3a,
               volatile uint16_t * ocr3b,
               volatile uint16_t * ocr3c)
: _prescaler(0     ),
  _TCNT3    (tcnt3 ),
  _TCCR3B   (tccr3a),
  _OCR3A    (ocr3a ),
  _OCR3B    (ocr3b ),
  _OCR3C    (ocr3c )
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
  case 0    : *_TCCR3B |= static_cast<uint8_t>(Timer3Prescaler::P_0   ); break;
  case 1    : *_TCCR3B |= static_cast<uint8_t>(Timer3Prescaler::P_1   ); break;
  case 8    : *_TCCR3B |= static_cast<uint8_t>(Timer3Prescaler::P_8   ); break;
  case 64   : *_TCCR3B |= static_cast<uint8_t>(Timer3Prescaler::P_64  ); break;
  case 256  : *_TCCR3B |= static_cast<uint8_t>(Timer3Prescaler::P_256 ); break;
  case 1024 : *_TCCR3B |= static_cast<uint8_t>(Timer3Prescaler::P_1024); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA640_1280_2560 */

} /* hal */

} /* snowfox */
