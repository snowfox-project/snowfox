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

#include <spectre/hal/avr/ATxxxx/CriticalSection.h>

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
 * CTOR/DTOR
 **************************************************************************************/

CriticalSection::CriticalSection(volatile uint8_t * sreg)
: _sreg                  (sreg ),
  _is_global_int_flag_set(false)
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
#if MCU_ARCH_avr
  _is_global_int_flag_set = isGobalIntFlagSet(*_sreg);
  asm volatile("cli");
#endif
}

void CriticalSection::unlock()
{
#if MCU_ARCH_avr
  if(_is_global_int_flag_set)
  {
    asm volatile("sei");
  }
#endif
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */
