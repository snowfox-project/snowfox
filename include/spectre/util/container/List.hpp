/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SPECTRE_MEMORY_CONTAINER_LIST_H_
#define INCLUDE_SPECTRE_MEMORY_CONTAINER_LIST_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/util/container/ListNode.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace util
{

namespace container
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

template <class T>
class List
{

public:

   List();
  ~List();


  void          push_front(T           const & data);
  void          push_back (T           const & data);
  void          erase     (ListNode<T>       * node);

  inline ListNode<T> * first() { return _head; }
  inline ListNode<T> * last () { return _tail; }

private:

  ListNode<T> * _head,
              * _tail;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* container*/

} /* util */

} /* spectre */

/**************************************************************************************
 * TEMPLATE CODE IMPLEMENTATION
 **************************************************************************************/

#include "List.ipp"

#endif /* INCLUDE_SPECTRE_MEMORY_CONTAINER_LIST_H_ */
