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

#include <spectre/driver/console/Serial/SerialQueue.h>

#include <spectre/hal/interface/locking/LockGuard.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace console
{

namespace serial
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

SerialQueue::SerialQueue(hal::interface::CriticalSection & crit_sec, uint16_t const size)
: _crit_sec(crit_sec),
  _queue   (size    )
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool SerialQueue::push(uint8_t const data)
{
  hal::interface::LockGuard lock(_crit_sec);
  return _queue.push(data);
}

bool SerialQueue::pop(uint8_t * data)
{
  hal::interface::LockGuard lock(_crit_sec);
  return _queue.pop(data);
}

uint16_t SerialQueue::size()
{
  hal::interface::LockGuard lock(_crit_sec);
  return _queue.size();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* serial */

} /* console */

} /* driver */

} /* spectre */
