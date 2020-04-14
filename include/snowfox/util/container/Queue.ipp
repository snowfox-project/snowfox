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
 * CTOR/DTOR
 **************************************************************************************/

template <class T>
Queue<T>::Queue(size_t const capacity)
: _size{0}
, _capacity{capacity}
{

}

template <class T>
Queue<T>::~Queue()
{
  _data.clear();
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

template <class T>
bool Queue<T>::push(T const data)
{
  if(isFull()) return false;
  else
  {
    _data.push_back(data);
    _size++;
    return true;
  }
}

template <class T>
bool Queue<T>::pop(T * data)
{
  if(isEmpty()) return false;
  else
  {
    *data = _data.front();
    _data.pop_front();
    _size--;
    return true;
  }
}

template <class T>
size_t Queue<T>::size() const
{
  return _size;
}

template <class T>
size_t Queue<T>::capacity() const
{
  return _capacity;
}

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

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* container*/

} /* util */

} /* snowfox */
