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

/**************************************************************************************
 * FUNCTIONS
 **************************************************************************************/

/* The current processor state in a AT90CAN128 is specified by the content of
 * the following registers:
 *  * General Purpose Registers : R0 - R31
 *  * Status Register           : SREG
 *  * Program Counter           : PC
 *  * Stack Pointer             : SPH, SPL
 */

void spectre_switch_task(struct task_list_t * new_task, struct task_list_t * old_task)
{
  asm volatile(
      /* Save general purpose registers R0 - R31 */
      "push r0        \n\t"
      "push r1        \n\t"
      "push r2        \n\t"
      "push r3        \n\t"
      "push r4        \n\t"
      "push r5        \n\t"
      "push r6        \n\t"
      "push r7        \n\t"
      "push r8        \n\t"
      "push r9        \n\t"
      "push r10       \n\t"
      "push r11       \n\t"
      "push r12       \n\t"
      "push r13       \n\t"
      "push r14       \n\t"
      "push r15       \n\t"
      "push r16       \n\t"
      "push r17       \n\t"
      "push r18       \n\t"
      "push r19       \n\t"
      "push r20       \n\t"
      "push r21       \n\t"
      "push r22       \n\t"
      "push r23       \n\t"
      "push r24       \n\t"
      "push r25       \n\t"
      "push r26       \n\t"
      "push r27       \n\t"
      "push r28       \n\t"
      "push r29       \n\t"
      "push r30       \n\t"
      "push r31       \n\t"
      );
}

