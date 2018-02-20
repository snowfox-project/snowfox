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

#include <spectre/os/scheduler.h>

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

void schedule(struct task_list_t * task_list_head)
{
  struct task_list_t * current_task = task_list_head;

  for(;
      current_task->next != 0 && current_task->tcb.task_state != Ready;
      current_task = current_task->next) { }

  /* dispatch current task  TODO */
}
