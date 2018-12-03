/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#include <spectre/hal/avr/common/ATMEGA3209_4809/TIMERA0.h>

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
 * DEFINES
 **************************************************************************************/

/* TCA_CTRLA */
#define TCA_CLKSEL2_bm  (1<<3)
#define TCA_CLKSEL1_bm  (1<<2)
#define TCA_CLKSEL0_bm  (1<<1)
#define TCA_ENABLE_bm   (1<<0)

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Prescaler : uint8_t
{
  P1    = 0,
  P2    =                                   TCA_CLKSEL0_bm,
  P4    =                  TCA_CLKSEL1_bm,
  P8    =                  TCA_CLKSEL1_bm | TCA_CLKSEL0_bm,
  P16   = TCA_CLKSEL2_bm,
  P64   = TCA_CLKSEL2_bm |                  TCA_CLKSEL0_bm,
  P256  = TCA_CLKSEL2_bm | TCA_CLKSEL1_bm,
  P1024 = TCA_CLKSEL2_bm | TCA_CLKSEL1_bm | TCA_CLKSEL0_bm
};

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

TIMERA0::TIMERA0(volatile uint8_t  * tca_ctrla,
                 volatile uint16_t * tca_cnt,
                 volatile uint16_t * tca_cmp0,
                 volatile uint16_t * tca_cmp1,
                 volatile uint16_t * tca_cmp2)
: _TCA_CTRLA(tca_ctrla),
  _TCA_CNT  (tca_cnt  ),
  _TCA_CMP0 (tca_cmp0 ),
  _TCA_CMP1 (tca_cmp1 ),
  _TCA_CMP2 (tca_cmp2 )
{

}

TIMERA0::~TIMERA0()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void TIMERA0::start()
{
  *_TCA_CTRLA |= TCA_ENABLE_bm;
}

void TIMERA0::stop()
{
  *_TCA_CTRLA &= ~TCA_ENABLE_bm;
}

void TIMERA0::set(uint16_t const val)
{
  *_TCA_CNT = val;
}

uint16_t TIMERA0::get()
{
  return *_TCA_CNT;
}

void TIMERA0::setCompareRegister(uint8_t const reg_sel, uint16_t const reg_val)
{
  switch(reg_sel)
  {
  case COMPARE_CHANNEL_0: *_TCA_CMP0 = reg_val; break;
  case COMPARE_CHANNEL_1: *_TCA_CMP1 = reg_val; break;
  case COMPARE_CHANNEL_2: *_TCA_CMP2 = reg_val; break;
  }
}

void TIMERA0::setPrescaler(uint32_t const prescaler)
{
  *_TCA_CTRLA &= ~(TCA_CLKSEL2_bm | TCA_CLKSEL1_bm | TCA_CLKSEL0_bm);

  switch(prescaler)
  {
  case 1   : *_TCA_CTRLA |= static_cast<uint8_t>(Prescaler::P1   ); break;
  case 2   : *_TCA_CTRLA |= static_cast<uint8_t>(Prescaler::P2   ); break;
  case 4   : *_TCA_CTRLA |= static_cast<uint8_t>(Prescaler::P4   ); break;
  case 8   : *_TCA_CTRLA |= static_cast<uint8_t>(Prescaler::P8   ); break;
  case 16  : *_TCA_CTRLA |= static_cast<uint8_t>(Prescaler::P16  ); break;
  case 64  : *_TCA_CTRLA |= static_cast<uint8_t>(Prescaler::P64  ); break;
  case 256 : *_TCA_CTRLA |= static_cast<uint8_t>(Prescaler::P256 ); break;
  case 1024: *_TCA_CTRLA |= static_cast<uint8_t>(Prescaler::P1024); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA3209_4809 */

} /* hal */

} /* spectre */
