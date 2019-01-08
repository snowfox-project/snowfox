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

#include <spectre/hal/avr/common/ATMEGA3209_4809/TIMERAx.h>

#include <spectre/util/BitManip.h>

#include <spectre/cpu/avr/io/common/ATMEGA3209_4809.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA3209_4809
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Prescaler : uint8_t
{
  P1    = 0,
  P2    =                                     TCAx_CLKSEL0_bm,
  P4    =                   TCAx_CLKSEL1_bm,
  P8    =                   TCAx_CLKSEL1_bm | TCAx_CLKSEL0_bm,
  P16   = TCAx_CLKSEL2_bm,
  P64   = TCAx_CLKSEL2_bm |                   TCAx_CLKSEL0_bm,
  P256  = TCAx_CLKSEL2_bm | TCAx_CLKSEL1_bm,
  P1024 = TCAx_CLKSEL2_bm | TCAx_CLKSEL1_bm | TCAx_CLKSEL0_bm
};

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

TIMERAx::TIMERAx(volatile uint8_t  * tcax_ctrla,
                 volatile uint16_t * tcax_cnt,
                 volatile uint16_t * tcax_cmp0,
                 volatile uint16_t * tcax_cmp1,
                 volatile uint16_t * tcax_cmp2)
: _TCAx_CTRLA(tcax_ctrla),
  _TCAx_CNT  (tcax_cnt  ),
  _TCAx_CMP0 (tcax_cmp0 ),
  _TCAx_CMP1 (tcax_cmp1 ),
  _TCAx_CMP2 (tcax_cmp2 )
{

}

TIMERAx::~TIMERAx()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void TIMERAx::start()
{
  util::setBit(_TCAx_CTRLA, TCAx_ENABLE_bp);
}

void TIMERAx::stop()
{
  util::clrBit(_TCAx_CTRLA, TCAx_ENABLE_bp);
}

void TIMERAx::set(uint16_t const val)
{
  *_TCAx_CNT = val;
}

uint16_t TIMERAx::get()
{
  return *_TCAx_CNT;
}

void TIMERAx::setCompareRegister(uint8_t const reg_sel, uint16_t const reg_val)
{
  switch(reg_sel)
  {
  case COMPARE_CHANNEL_0: *_TCAx_CMP0 = reg_val; break;
  case COMPARE_CHANNEL_1: *_TCAx_CMP1 = reg_val; break;
  case COMPARE_CHANNEL_2: *_TCAx_CMP2 = reg_val; break;
  }
}

void TIMERAx::setPrescaler(uint32_t const prescaler)
{
  *_TCAx_CTRLA &= ~(TCAx_CLKSEL2_bm | TCAx_CLKSEL1_bm | TCAx_CLKSEL0_bm);

  switch(prescaler)
  {
  case 1   : *_TCAx_CTRLA |= static_cast<uint8_t>(Prescaler::P1   ); break;
  case 2   : *_TCAx_CTRLA |= static_cast<uint8_t>(Prescaler::P2   ); break;
  case 4   : *_TCAx_CTRLA |= static_cast<uint8_t>(Prescaler::P4   ); break;
  case 8   : *_TCAx_CTRLA |= static_cast<uint8_t>(Prescaler::P8   ); break;
  case 16  : *_TCAx_CTRLA |= static_cast<uint8_t>(Prescaler::P16  ); break;
  case 64  : *_TCAx_CTRLA |= static_cast<uint8_t>(Prescaler::P64  ); break;
  case 256 : *_TCAx_CTRLA |= static_cast<uint8_t>(Prescaler::P256 ); break;
  case 1024: *_TCAx_CTRLA |= static_cast<uint8_t>(Prescaler::P1024); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA3209_4809 */

} /* hal */

} /* spectre */
