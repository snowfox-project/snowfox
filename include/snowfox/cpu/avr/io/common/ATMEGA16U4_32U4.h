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

#ifndef INCLUDE_SNOWFOX_CPU_AVR_IO_COMMON_ATMEGA16U4_32U4_H_
#define INCLUDE_SNOWFOX_CPU_AVR_IO_COMMON_ATMEGA16U4_32U4_H_

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* EIMSK */
#define INT6_bp   (6)
#define INT3_bp   (3)
#define INT2_bp   (2)
#define INT1_bp   (1)
#define INT0_bp   (0)

/* PCICR */
#define PCIE0_bp  (0)

/* WDTCSR */
#define WDIE_bp   (6)

/* TIMSK1 */
#define ICIE1_bp  (5)
#define OCIE1C_bp (3)
#define OCIE1B_bp (2)
#define OCIE1A_bp (1)
#define TOIE1_bp  (0)

/* TIMSK0 */
#define OCIE0B_bp (2)
#define OCIE0A_bp (1)
#define TOIE0_bp  (0)

/* SPCR */
#define SPIE_bp   (7)

/* UCSR1B */
#define RXCIE1_bp (7)
#define TXCIE1_bp (6)
#define UDRIE1_bp (5)

/* ACSR */
#define ACIE_bp   (3)

/* ADCSRA */
#define ADIE_bp   (3)

/* EECR */
#define EERIE_bp  (3)

/* PCMSK0 */
#define PCINT7_bp  (7)
#define PCINT6_bp  (6)
#define PCINT5_bp  (5)
#define PCINT4_bp  (4)
#define PCINT3_bp  (3)
#define PCINT2_bp  (2)
#define PCINT1_bp  (1)
#define PCINT0_bp  (0)

/* TIMSK3 */
#define ICIE3_bp  (5)
#define OCIE3C_bp (3)
#define OCIE3B_bp (2)
#define OCIE3A_bp (1)
#define TOIE3_bp  (0)

/* TCCR0B */
#define CS02_bp   (2)
#define CS02_bm   (1<<CS02_bp)
#define CS01_bp   (1)
#define CS01_bm   (1<<CS01_bp)
#define CS00_bp   (0)
#define CS00_bm   (1<<CS00_bp)

/* TCCR1B */
#define CS12_bp   (2)
#define CS12_bm   (1<<CS12_bp)
#define CS11_bp   (1)
#define CS11_bm   (1<<CS11_bp)
#define CS10_bp   (0)
#define CS10_bm   (1<<CS10_bp)

/* TCCR3B */
#define CS32_bp   (2)
#define CS32_bm   (1<<CS32_bp)
#define CS31_bp   (1)
#define CS31_bm   (1<<CS31_bp)
#define CS30_bp   (0)
#define CS30_bm   (1<<CS30_bp)

/* TWCR */
#define TWIE_bp   (0)

/* SPMCSR */
#define SPMIE_bp  (7)

/* TIMSK4 */
#define OCIE4D_bp (7)
#define OCIE4A_bp (6)
#define OCIE4B_bp (5)
#define TOIE4_bp  (2)

/* TCCR4D */
#define FPIE4_bp  (7)

#endif /* INCLUDE_SNOWFOX_CPU_AVR_IO_COMMON_ATMEGA16U4_32U4_H_ */
