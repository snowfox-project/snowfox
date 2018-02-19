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

#ifndef INCLUDE_SPECTRE_OS_TASK_H_
#define INCLUDE_SPECTRE_OS_TASK_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * EXTERN "C"
 **************************************************************************************/

extern "C"
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

enum class TaskState : uint8_t
{
  Ready, Running, Suspended, Blocked
};

typedef void * TaskArgument;

typedef void (*TaskFunction)(TaskArgument);

typedef struct
{
  void         * top_of_stack;
  TaskState      task_state;
  TaskFunction   task_func;
  TaskArgument   task_arg;
} TaskControlBlock;

/**************************************************************************************
 * EXTERN "C"
 **************************************************************************************/

} /* extern "C"

#endif /* INCLUDE_SPECTRE_OS_TASK_H_ */
