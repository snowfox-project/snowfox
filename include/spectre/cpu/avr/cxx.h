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

#ifndef INCLUDE_SPECTRE_HAL_AVR_CXX_CXX_H_
#define INCLUDE_SPECTRE_HAL_AVR_CXX_CXX_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdlib.h>

/**************************************************************************************
 * PUBLIC PROTOTYPES
 **************************************************************************************/

__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int  __cxa_guard_acquire (__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort   (__guard *);
extern "C" void __cxa_pure_virtual  (void     );

           void *  operator new     (size_t   size);
           void    operator delete  (void   * ptr );
           void *  operator new[]   (size_t   size);
           void    operator delete[](void   * ptr );

#endif /* INCLUDE_SPECTRE_HAL_AVR_CXX_CXX_H_ */
