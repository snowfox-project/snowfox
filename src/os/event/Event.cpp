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

#include <snowfox/os/event/Event.h>

#include <snowfox/hal/interface/locking/LockGuard.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace os
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Event::Event()
{
  clear();
}

Event::~Event()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

void Event::set()
{
#if defined(MCU_ARCH_avr)
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { _is_set = true; }
#else
  _is_set = true;
#endif
}

void Event::clear()
{
#if defined(MCU_ARCH_avr)
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { _is_set = false; }
#else
  _is_set = false;
#endif
}

bool Event::isSet()
{
#if defined(MCU_ARCH_avr)
  bool is_set = false;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { is_set = _is_set; }
  return is_set;
#else
  return _is_set;
#endif
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox */

} /* os */
