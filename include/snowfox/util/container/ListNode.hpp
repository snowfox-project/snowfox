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

#ifndef INCLUDE_SNOWFOX_MEMORY_CONTAINER_LISTNODE_H_
#define INCLUDE_SNOWFOX_MEMORY_CONTAINER_LISTNODE_H_

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace util
{

namespace container
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

template <class T>
class ListNode
{

public:

  ListNode(T const & data, ListNode<T> * next, ListNode<T> * prev);

  inline T           & data   (                  ) { return _data; }
  inline ListNode<T> * next   (                  ) { return _next; }
  inline ListNode<T> * prev   (                  ) { return _prev; }
  inline void          setNext(ListNode<T> * next) { _next = next; }
  inline void          setPrev(ListNode<T> * prev) { _prev = prev; }

private:

  T             _data;
  ListNode<T> * _prev,
              * _next;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* container*/

} /* util */

} /* snowfox */

/**************************************************************************************
 * TEMPLATE CODE IMPLEMENTATION
 **************************************************************************************/

#include "ListNode.ipp"

#endif /* INCLUDE_SNOWFOX_MEMORY_CONTAINER_LISTNODE_H_ */
