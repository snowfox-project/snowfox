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
 * INCLUDES
 **************************************************************************************/

#include <spectre/os/task.h>

#include <stdlib.h>

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

struct task_control_block_t * spectre_create_task(TaskFunc task_func, void * task_arg, uint16_t const task_prio)
{
  struct task_control_block_t * tcb = (struct task_control_block_t *)malloc(sizeof(struct task_control_block_t));

  tcb->top_of_stack = 0; /* TODO */
  tcb->task_func    = task_func;
  tcb->task_arg     = task_arg;
  tcb->task_prio    = task_prio;

  return tcb;
}
