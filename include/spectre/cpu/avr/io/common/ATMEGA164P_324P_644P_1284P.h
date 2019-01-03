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

#ifndef INCLUDE_SPECTRE_CPU_AVR_IO_COMMON_ATMEGA164P_324P_644P_1284P_H_
#define INCLUDE_SPECTRE_CPU_AVR_IO_COMMON_ATMEGA164P_324P_644P_1284P_H_

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* EIMSK */
#define INT2_bp   (2)
#define INT1_bp   (1)
#define INT0_bp   (0)

/* PCICR */
#define PCIE3_bp  (3)
#define PCIE2_bp  (2)
#define PCIE1_bp  (1)
#define PCIE0_bp  (0)

/* WDTCSR */
#define WDIE_bp   (6)

/* TIMSK2 */
#define OCIE2B_bp (2)
#define OCIE2A_bp (1)
#define TOIE2_bp  (0)

/* TIMSK1 */
#define ICIE1_bp  (5)
#define OCIE1B_bp (2)
#define OCIE1A_bp (1)
#define TOIE1_bp  (0)

/* TIMSK0 */
#define OCIE0B_bp (2)
#define OCIE0A_bp (1)
#define TOIE0_bp  (0)

/* SPCR */
#define SPIE_bp   (7)

/* UCSR0B */
#define RXCIE0_bp (7)
#define TXCIE0_bp (6)
#define UDRIE0_bp (5)

/* ACSR */
#define ACIE_bp   (3)

/* ADCSRA */
#define ADIE_bp   (3)

/* EECR */
#define EERIE_bp  (3)

/* TWCR */
#define TWIE_bp   (0)

/* SPMCSR */
#define SPMIE_bp  (7)

/* UCSR1B */
#define RXCIE1_bp (7)
#define TXCIE1_bp (6)
#define UDRIE1_bp (5)

#endif /* INCLUDE_SPECTRE_CPU_AVR_IO_COMMON_ATMEGA164P_324P_644P_1284P_H_ */
