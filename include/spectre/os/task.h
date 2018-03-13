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
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  Ready,
  Running,
  Suspended,
  Blocked
} TaskState;

typedef void (*TaskFunc)(void *);

struct task_control_block_t
{
  void      * top_of_stack;

  TaskState   task_state;
  TaskFunc    task_func;
  void      * task_arg;
  uint16_t    task_prio;
};

struct task_list_t
{
  struct task_control_block_t   tcb;
  struct task_list_t          * next,
                              * prev;
};

/**************************************************************************************
 * PROTOTYPES
 **************************************************************************************/

struct task_list_t * spectre_create_task(struct task_list_t * task_list_head, TaskFunc task_func, void * task_arg, uint16_t const task_prio);

#endif /* INCLUDE_SPECTRE_OS_TASK_H_ */
