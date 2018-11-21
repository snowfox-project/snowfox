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

#include <spectre/hal/avr/common/ATMEGA3209_4809/TIMERB.h>

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

/* TCB_CTRLA */
#define TCB_CLKSEL1_bm  (1<<2)
#define TCB_CLKSEL0_bm  (1<<1)
#define TCB_ENABLE_bm   (1<<0)

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Prescaler : uint8_t
{
  P1      = 0,
  P2      =                 TCB_CLKSEL0_bm,
  CLK_TCA = TCB_CLKSEL1_bm,
};

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

TIMERB::TIMERB(volatile uint8_t  * tcb_ctrla,
               volatile uint16_t * tcb_cnt)
: _TCB_CTRLA(tcb_ctrla),
  _TCB_CNT  (tcb_cnt  )
{

}

TIMERB::~TIMERB()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void TIMERB::start()
{
  *_TCB_CTRLA |= TCB_ENABLE_bm;
}

void TIMERB::stop()
{
  *_TCB_CTRLA &= ~TCB_ENABLE_bm;
}

void TIMERB::set(uint16_t const val)
{
  *_TCB_CNT = val;
}

uint16_t TIMERB::get()
{
  return *_TCB_CNT;
}

void TIMERB::setCompareRegister(uint8_t const reg_sel, uint16_t const reg_val)
{
  /* TIMERB has no compare register */
}

void TIMERB::setPrescaler(uint32_t const prescaler)
{
  *_TCB_CTRLA &= ~(TCB_CLKSEL1_bm | TCB_CLKSEL0_bm);

  switch(prescaler)
  {
  case 1   : *_TCB_CTRLA |= static_cast<uint8_t>(Prescaler::P1     ); break;
  case 2   : *_TCB_CTRLA |= static_cast<uint8_t>(Prescaler::P2     ); break;
  case 3   : *_TCB_CTRLA |= static_cast<uint8_t>(Prescaler::CLK_TCA); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA3209_4809 */

} /* hal */

} /* spectre */
