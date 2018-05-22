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
: _is_event_signaled(false   ),
  _crit_sec         (crit_sec)
{

}

Event::~Event()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

void Event::signal()
{
  hal::interface::LockGuard lock(_crit_sec);

  _is_event_signaled = true;
}

void Event::wait()
{
  bool is_event_signaled = false;

  while(!is_event_signaled)
  {
    hal::interface::LockGuard lock(_crit_sec);
    is_event_signaled = _is_event_signaled;
    if(_is_event_signaled) _is_event_signaled = false;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* spectre */

} /* os */
