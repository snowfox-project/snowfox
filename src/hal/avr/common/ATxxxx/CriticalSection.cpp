/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#include <snowfox/hal/avr/common/ATxxxx/CriticalSection.h>

#ifdef MCU_ARCH_avr
#include <avr/io.h>
#include <avr/interrupt.h>
#endif

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::ATxxxx
{

/**************************************************************************************
 * STATIC INITIALISATION
 **************************************************************************************/

volatile uint8_t CriticalSection::_sreg_save = 0;

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void CriticalSection::lock()
{
#if MCU_ARCH_avr
  _sreg_save = SREG;
  __asm__ volatile ("" ::: "memory");
  cli();
#endif
}

void CriticalSection::unlock()
{
#if MCU_ARCH_avr
  SREG = _sreg_save;
  __asm__ volatile ("" ::: "memory");
#endif
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::ATxxxx */
