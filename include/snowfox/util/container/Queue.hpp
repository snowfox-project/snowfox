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

#ifndef INCLUDE_SNOWFOX_MEMORY_RINGBUFFER_H_
#define INCLUDE_SNOWFOX_MEMORY_RINGBUFFER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#ifdef MCU_ARCH_avr
  #include <stdlib.h>
#else
  #include <cstdlib>
  #include <memory>
#endif

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::util::container
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

template <class T>
class Queue
{

public:

  explicit  Queue(size_t const capacity);
#ifdef MCU_ARCH_avr
           ~Queue();
#endif


  bool   push    (T const   data);
  bool   pop     (T       * data);
  size_t size    () const;
  size_t capacity() const;
  bool   isFull  () const;
  bool   isEmpty () const;


private:

#ifdef MCU_ARCH_avr
  T * _data;
#else
  std::unique_ptr<T[]> _data;
#endif
  size_t _capacity, _head, _tail, _size;

  void pushData    (T const data);
  void popData     (T * data);
  void incrementPtr(size_t & ptr) const;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::util::container */

/**************************************************************************************
 * TEMPLATE CODE IMPLEMENTATION
 **************************************************************************************/

#include "Queue.ipp"

#endif /* INCLUDE_SNOWFOX_MEMORY_RINGBUFFER_H_ */
