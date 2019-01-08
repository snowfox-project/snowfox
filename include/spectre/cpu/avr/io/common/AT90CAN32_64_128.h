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

#ifndef INCLUDE_SPECTRE_CPU_AVR_IO_COMMON_AT90CAN32_64_128_H_
#define INCLUDE_SPECTRE_CPU_AVR_IO_COMMON_AT90CAN32_64_128_H_

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* EIMSK */
#define INT7_bp   (7)
#define INT6_bp   (6)
#define INT5_bp   (5)
#define INT4_bp   (4)
#define INT3_bp   (3)
#define INT2_bp   (2)
#define INT1_bp   (1)
#define INT0_bp   (0)

/* TIMSK2 */
#define OCIE2A_bp (1)
#define TOIE2_bp  (0)

/* TIMSK1 */
#define ICIE1_bp  (5)
#define OCIE1C_bp (3)
#define OCIE1B_bp (2)
#define OCIE1A_bp (1)
#define TOIE1_bp  (0)

/* TIMSK0 */
#define OCIE0A_bp (1)
#define TOIE0_bp  (0)

/* CANGIE */
#define ENIT_bp   (7)
#define ENBOFF_bp (6)
#define ENRX_bp   (5)
#define ENTX_bp   (4)
#define ENERR_bp  (3)
#define ENBX_bp   (2)
#define ENERG_bp  (1)
#define ENOVRT_bp (0)

/* CANGIT */
#define CANIT_bp  (7)
#define BOFFIT_bp (6)
#define OVRTIM_bp (5)
#define BXOK_bp   (4)
#define SERG_bp   (3)
#define CERG_bp   (2)
#define FERG_bp   (1)
#define AERG_bp   (0)

/* CANSTMOB */
#define DLCW_bp   (7)
#define TXOK_bp   (6)
#define RXOK_bp   (5)
#define BERR_bp   (4)
#define SERR_bp   (3)
#define CERR_bp   (2)
#define FERR_bp   (1)
#define AERR_bp   (0)

/* SPCR */
#define SPIE_bp   (7)

/* UCSR0B */
#define UDRIE0_bp (5)
#define TXCIE0_bp (6)
#define RXCIE0_bp (7)

/* ACSR */
#define ACIE_bp   (3)

/* ADCSRA */
#define ADIE_bp   (3)

/* EECR */
#define EERIE_bp  (3)

/* TIMSK3 */
#define ICIE3_bp  (5)
#define OCIE3C_bp (3)
#define OCIE3B_bp (2)
#define OCIE3A_bp (1)
#define TOIE3_bp  (0)

/* TCCR0A */
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

/* TCCR2A */
#define CS22_bp   (2)
#define CS22_bm   (1<<CS22_bp)
#define CS21_bp   (1)
#define CS21_bm   (1<<CS21_bp)
#define CS20_bp   (0)
#define CS20_bm   (1<<CS20_bp)

/* TCCR3B */
#define CS32_bp   (2)
#define CS32_bm   (1<<CS32_bp)
#define CS31_bp   (1)
#define CS31_bm   (1<<CS31_bp)
#define CS30_bp   (0)
#define CS30_bm   (1<<CS30_bp)

/* UCSR1B */
#define UDRIE1_bp (5)
#define TXCIE1_bp (6)
#define RXCIE1_bp (7)

/* TWCR */
#define TWIE_bp   (0)

/* SPMCSR */
#define SPMIE_bp  (7)

#endif /* INCLUDE_SPECTRE_CPU_AVR_IO_COMMON_AT90CAN32_64_128_H_ */
