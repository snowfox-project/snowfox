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

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace console
{

namespace Serial
{

/**************************************************************************************
 * FUNCTIONS
 **************************************************************************************/

bool isEmpty(SerialQueue const & queue)
{
  bool const is_empty = (queue.size() == 0);
  return is_empty;
}

bool isFull(SerialQueue const & queue)
{
  bool const is_full = (queue.size() == queue.capacity());
  return is_full;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* Serial */

} /* console */

} /* driver */

} /* spectre */
