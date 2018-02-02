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

#ifndef INCLUDE_SPECTRE_MEMORY_RINGBUFFER_H_
#define INCLUDE_SPECTRE_MEMORY_RINGBUFFER_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace memory
{

namespace container
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

template <class T>
class Queue
{

public:

   Queue(uint16_t const size);
  ~Queue();

  bool     push(T const   data);
  bool     pop (T       * data);
  uint16_t size(              ) const;

private:

  uint16_t    _size,
              _head,
              _tail,
              _num_entries;

  T         * _data;

  bool isFull       (               ) const;
  bool isEmpty      (               ) const;
  void pushData     (T  const   data);
  void popData      (T        * data);
  void incrementPtr (uint16_t * ptr ) const;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* container*/

} /* memory */

} /* spectre */

/**************************************************************************************
 * TEMPLATE CODE IMPLEMENTATION
 **************************************************************************************/

#include "Queue.ipp"

#endif /* INCLUDE_SPECTRE_MEMORY_RINGBUFFER_H_ */
