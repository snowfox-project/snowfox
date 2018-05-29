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
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace memory
{

namespace container
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

template <class T>
List<T>::List()
: _head(0),
  _tail(0)
{

}

template <class T>
List<T>::~List()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

template <class T>
void List<T>::push_front(T const & data)
{
  if(_head == 0)
  {
    ListNode<T> * node = new ListNode<T>(data, 0, 0);
    _head = node;
    _tail = node;
  }
  else
  {
    ListNode<T> * node = new ListNode<T>(data, 0, _head);
    _head->setPrev(node);
    _head = node;
  }
}

template <class T>
void List<T>::push_back(T const & data)
{
  if(_tail == 0)
  {
    ListNode<T> * node = new ListNode<T>(data, 0, 0);
    _head = node;
    _tail = node;
  }
  else
  {
    ListNode<T> * node = new ListNode<T>(data, _tail, 0);
    _tail->setNext(node);
    _tail = node;
  }
}

template <class T>
ListNode<T> * List<T>::begin()
{
  return _head;
}

template <class T>
ListNode<T> * List<T>::end()
{
  return _tail;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* container*/

} /* memory */

} /* spectre */
