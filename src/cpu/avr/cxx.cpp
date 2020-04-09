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
 * INCLUDE
 **************************************************************************************/

#include <snowfox/cpu/avr/cxx.h>

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

int   __cxa_guard_acquire (__guard *g )
{
  return !*(char *)(g);
}

void  __cxa_guard_release (__guard *g )
{
  *(char *)g = 1;
}

void  __cxa_guard_abort   (__guard *  )
{

}

void  __cxa_pure_virtual  (void       )
{

}

void * operator new(size_t size)
{
  return malloc(size);
}

void * operator new(size_t size, void * ptr)
{
  (void)size;
  return ptr;
}

void operator delete(void * ptr)
{
  if(ptr)
  {
    free(ptr);
  }
}

void operator delete(void * ptr, size_t /* size */)
{
  return ::operator delete(ptr);
}

void * operator new[] (size_t size)
{
  return ::operator new(size);
}

void operator delete[] (void *ptr)
{
  return ::operator delete(ptr);
}

void operator delete[](void * ptr, size_t /* size */)
{
  return ::operator delete(ptr);
}