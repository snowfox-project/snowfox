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
 * INCLUDE
 **************************************************************************************/

#include <spectre/os/Event.h>

#include <spectre/hal/interface/locking/LockGuard.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace os
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Event::Event(hal::interface::CriticalSection & crit_sec)
: _is_set  (false   ),
  _crit_sec(crit_sec)
{

}

Event::~Event()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

void Event::set()
{
  hal::interface::LockGuard lock(_crit_sec);
  _is_set = true;
}

void Event::clear()
{
  hal::interface::LockGuard lock(_crit_sec);
  _is_set = false;
}

bool Event::isSet()
{
  hal::interface::LockGuard lock(_crit_sec);
  return _is_set;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* spectre */

} /* os */
