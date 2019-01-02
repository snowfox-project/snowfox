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

#include <spectre/hal/avr/common/ATxxxx/CriticalSection.h>

#ifdef MCU_ARCH_avr
#include <avr/interrupt.h>
#endif

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATxxxx
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

#define GI_bm   (1<<7)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

CriticalSection::CriticalSection(volatile uint8_t * sreg)
: _sreg      (sreg),
  _sreg_iflag(0   )
{

}

CriticalSection::~CriticalSection()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void CriticalSection::lock()
{
  _sreg_iflag = *_sreg & GI_bm;
#if MCU_ARCH_avr
  asm volatile("cli");
#else
  *_sreg &= ~GI_bm; /* Has the same effect as 'cli' */
#endif
}

void CriticalSection::unlock()
{
  *_sreg |= _sreg_iflag;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */
