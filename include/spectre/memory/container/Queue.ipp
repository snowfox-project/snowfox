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
Queue<T>::Queue(uint16_t const capacity)
: _capacity(capacity),
  _head    (0),
  _tail    (0),
  _size	   (0),
  _data    (new T[_capacity])
{

}

template <class T>
Queue<T>::~Queue()
{
  delete []_data; _data = 0;
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

template <class T>
bool Queue<T>::push(T const data)
{
  if(isFull())  return false;
  else
  {
    pushData(data);
    return true;
  }
}

template <class T>
bool Queue<T>::pop(T * data)
{
  if(isEmpty()) return false;
  else
  {
    popData(data);
    return true;
  }
}

template <class T>
uint16_t Queue<T>::size() const
{
  return _size;
}

template <class T>
uint16_t Queue<T>::capacity() const
{
  return _capacity;
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

template <class T>
bool Queue<T>::isFull() const
{
  return (_size == _capacity);
}

template <class T>
bool Queue<T>::isEmpty() const
{
  return (_size == 0);
}

template <class T>
void Queue<T>::pushData(T const data)
{
  _data[_head] = data;

  incrementPtr(&_head);

  _size++;
}

template <class T>
void Queue<T>::popData(T * data)
{
  *data = _data[_tail];

  incrementPtr(&_tail);

  _size--;
}

template <class T>
void Queue<T>::incrementPtr(uint16_t * ptr) const
{
  uint16_t const tmp_ptr = *ptr + 1;

  if  (tmp_ptr == _capacity)  *ptr = 0;
  else                    	  *ptr = tmp_ptr;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* container*/

} /* memory */

} /* spectre */
