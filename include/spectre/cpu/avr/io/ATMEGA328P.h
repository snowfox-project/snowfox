/**
 * Spectre is a modular RTOS with extensive IO support.
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

#ifndef INCLUDE_SPECTRE_CPU_AVR_IO_ATMEGA328P_H_
#define INCLUDE_SPECTRE_CPU_AVR_IO_ATMEGA328P_H_

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* EIMSK */
#define INT0_bp   (0)
#define INT1_bp   (1)

/* PCICR */
#define PCIE0_bp  (0)
#define PCIE1_bp  (1)
#define PCIE2_bp  (2)

/* WDTCSR */
#define WDIE_bp   (6)

/* TIMSK2 */
#define TOIE2_bp  (0)
#define OCIE2A_bp (1)
#define OCIE2B_bp (2)

/* TIMSK1 */
#define TOIE1_bp  (0)
#define OCIE1A_bp (1)
#define OCIE1B_bp (2)
#define ICIE1_bp  (5)

/* TIMSK0 */
#define TOIE0_bp  (0)
#define OCIE0A_bp (1)
#define OCIE0B_bp (2)

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

/* TCCR2B */
#define CS22_bp    (2)
#define CS22_bm    (1<<CS22_bp)
#define CS21_bp    (1)
#define CS21_bm    (1<<CS21_bp)
#define CS20_bp    (0)
#define CS20_bm    (1<<CS20_bp)

/* SPCR */
#define SPIE_bp   (7)

/* UCSR0B */
#define UDRIE0_bp (5)
#define TXCIE0_bp (6)
#define RXCIE0_bp (7)

/* ADCSRA */
#define ADIE_bp   (3)

/* EECR */
#define EERIE_bp  (3)

/* ACSR */
#define ACIE_bp   (3)

/* TWCR */
#define TWIE_bp   (0)

/* SPMCSR */
#define SPMIE_bp  (7)

#endif /* INCLUDE_SPECTRE_CPU_AVR_IO_ATMEGA328P_H_ */
