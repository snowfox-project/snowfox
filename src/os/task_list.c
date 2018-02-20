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

#include <spectre/os/task_list.h>

#include <stdlib.h>

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

void spectre_add_task(struct task_list_t * task_list_head, struct task_control_block_t * tcb)
{
  /* TODO - list is sorted from top to bottom according to priority - highest priority = lowest value = 0 = front */

  /*
   * First Task -> It does not matter which spot -> always the first task in the list
   * Second Task -> Is always a insert
   *  -> insert in the front
   *  -> insert in the middle
   *  -> insert in the end
   */

}

void insert_task(struct task_list_t * task_list_node, struct task_control_block_t * tcb)
{
  struct task_list_t * new_task_list_node = (struct task_list_t *)malloc(sizeof(struct task_list_t));

  new_task_list_node->next = task_list_node->next;
  new_task_list_node->prev = task_list_node;
  task_list_node->next     = new_task_list_node;
}
