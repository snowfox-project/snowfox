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

#ifndef INCLUDE_SPECTRE_MEMORY_CONTAINER_LIST_H_
#define INCLUDE_SPECTRE_MEMORY_CONTAINER_LIST_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/memory/container/ListNode.h>

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
class List
{

public:

   List();
  ~List();


  void          push_front(T const & data);
  void          push_back (T const & data);

  ListNode<T> * begin     (              );
  ListNode<T> * end       (              );

private:

  ListNode<T> * _head,
              * _tail;

};

/**************************************************************************************
 * PROTOTYPES
 **************************************************************************************/

template <typename T>
ListNode<T> * next(ListNode<T> * node);

template <typename T>
ListNode<T> * prev(ListNode<T> * node);

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* container*/

} /* memory */

} /* spectre */

/**************************************************************************************
 * TEMPLATE CODE IMPLEMENTATION
 **************************************************************************************/

#include "List.ipp"

#endif /* INCLUDE_SPECTRE_MEMORY_CONTAINER_LIST_H_ */
