/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2019 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SNOWFOX_CPU_AVR_IO_COMMON_ATMEGA164P_324P_644P_1284P_H_
#define INCLUDE_SNOWFOX_CPU_AVR_IO_COMMON_ATMEGA164P_324P_644P_1284P_H_

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* EIMSK */
#define INT2_bp    (2)
#define INT1_bp    (1)
#define INT0_bp    (0)

/* PCICR */
#define PCIE3_bp   (3)
#define PCIE2_bp   (2)
#define PCIE1_bp   (1)
#define PCIE0_bp   (0)

/* PCMSK0 */
#define PCINT7_bp  (7)
#define PCINT6_bp  (6)
#define PCINT5_bp  (5)
#define PCINT4_bp  (4)
#define PCINT3_bp  (3)
#define PCINT2_bp  (2)
#define PCINT1_bp  (1)
#define PCINT0_bp  (0)

/* PCMSK1 */
#define PCINT15_bp (7)
#define PCINT14_bp (6)
#define PCINT13_bp (5)
#define PCINT12_bp (4)
#define PCINT11_bp (3)
#define PCINT10_bp (2)
#define PCINT9_bp  (1)
#define PCINT8_bp  (0)

/* PCMSK2 */
#define PCINT23_bp (7)
#define PCINT22_bp (6)
#define PCINT21_bp (5)
#define PCINT20_bp (4)
#define PCINT19_bp (3)
#define PCINT18_bp (2)
#define PCINT17_bp (1)
#define PCINT16_bp (0)

/* PCMSK3 */
#define PCINT31_bp (7)
#define PCINT30_bp (6)
#define PCINT29_bp (5)
#define PCINT28_bp (4)
#define PCINT27_bp (3)
#define PCINT26_bp (2)
#define PCINT25_bp (1)
#define PCINT24_bp (0)

/* WDTCSR */
#define WDIE_bp    (6)

/* TIMSK2 */
#define OCIE2B_bp  (2)
#define OCIE2A_bp  (1)
#define TOIE2_bp   (0)

/* TIMSK1 */
#define ICIE1_bp   (5)
#define OCIE1B_bp  (2)
#define OCIE1A_bp  (1)
#define TOIE1_bp   (0)

/* TIMSK0 */
#define OCIE0B_bp  (2)
#define OCIE0A_bp  (1)
#define TOIE0_bp   (0)

/* TCCR0B */
#define CS02_bp    (2)
#define CS02_bm    (1<<CS02_bp)
#define CS01_bp    (1)
#define CS01_bm    (1<<CS01_bp)
#define CS00_bp    (0)
#define CS00_bm    (1<<CS00_bp)

/* TCCR2A */
#define CS22_bp    (2)
#define CS22_bm    (1<<CS22_bp)
#define CS21_bp    (1)
#define CS21_bm    (1<<CS21_bp)
#define CS20_bp    (0)
#define CS20_bm    (1<<CS20_bp)

/* SPCR */
#define SPIE_bp    (7)

/* UCSR0B */
#define RXCIE0_bp  (7)
#define TXCIE0_bp  (6)
#define UDRIE0_bp  (5)

/* ACSR */
#define ACIE_bp    (3)

/* ADCSRA */
#define ADIE_bp    (3)

/* EECR */
#define EERIE_bp   (3)

/* TWCR */
#define TWIE_bp    (0)

/* SPMCSR */
#define SPMIE_bp   (7)

/* UCSR1B */
#define RXCIE1_bp  (7)
#define TXCIE1_bp  (6)
#define UDRIE1_bp  (5)

#endif /* INCLUDE_SNOWFOX_CPU_AVR_IO_COMMON_ATMEGA164P_324P_644P_1284P_H_ */
