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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/os/task.h>

#include <stdlib.h>

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

struct task_list_t * spectre_create_task(struct task_list_t * task_list_head, TaskFunc task_func, void * task_arg, uint16_t const task_prio)
{
  struct task_list_t * new_task = (struct task_list_t *)malloc(sizeof(struct task_list_t));

  new_task->tcb.top_of_stack = 0; /* TODO */
  new_task->tcb.task_func    = task_func;
  new_task->tcb.task_arg     = task_arg;
  new_task->tcb.task_prio    = task_prio;

  if(task_list_head == 0)
  {
    new_task->prev = 0;
    new_task->next = 0;
    task_list_head = new_task;
  }
  else
  {
    struct task_list_t * current_task = task_list_head;
    for(;
        current_task->next != 0 &&
        current_task->next->tcb.task_prio > current_task->tcb.task_prio;
        current_task = current_task->next) { }

    new_task->prev = current_task;
    new_task->next = current_task->next;
    current_task->next = new_task;
  }

  return task_list_head;
}

#if defined(MCU_ARCH_avr) && defined(MCU_TYPE_at90can128)
#include "avr/at90can128/task-port.c"
#endif
