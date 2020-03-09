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

#ifndef INCLUDE_SNOWFOX_CPU_AVR_IO_ATMEGA328P_H_
#define INCLUDE_SNOWFOX_CPU_AVR_IO_ATMEGA328P_H_

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* ADCSRA */
#define ADEN_bp   (7)
#define ADEN_bm   (1<<ADEN_bp)
#define ADSC_bp   (6)
#define ADSC_bm   (1<<ADSC_bp)
#define ADATE_bp  (5)
#define ADATE_bm  (1<<ADATE_bp)
#define ADIF_bp   (4)
#define ADIF_bm   (1<<ADIF_bp)
#define ADIE_bp   (3)
#define ADIE_bm   (1<<ADIE_bp)
#define ADPS2_bp  (2)
#define ADPS2_bm  (1<<ADPS2_bp)
#define ADPS1_bp  (1)
#define ADPS1_bm  (1<<ADPS1_bp)
#define ADPS0_bp  (0)
#define ADPS0_bm  (1<<ADPS0_bp)

/* ADMUX */
#define REFS1_bp  (7)
#define REFS1_bm  (1<<REFS1_bp)
#define REFS0_bp  (6)
#define REFS0_bm  (1<<REFS0_bp)
#define ADLAR_bp  (5)
#define ADLAR_bm  (1<<ADLAR_bp)
#define MUX3_bp   (3)
#define MUX3_bm   (1<<MUX3_bp)
#define MUX2_bp   (2)
#define MUX2_bm   (1<<MUX2_bp)
#define MUX1_bp   (1)
#define MUX1_bm   (1<<MUX1_bp)
#define MUX0_bp   (0)
#define MUX0_bm   (1<<MUX0_bp)

/* DIDR0 */
#define ADC5D_bp  (5)
#define ADC5D_bm  (1<<ADC5D_bp)
#define ADC4D_bp  (4)
#define ADC4D_bm  (1<<ADC4D_bp)
#define ADC3D_bp  (3)
#define ADC3D_bm  (1<<ADC3D_bp)
#define ADC2D_bp  (2)
#define ADC2D_bm  (1<<ADC2D_bp)
#define ADC1D_bp  (1)
#define ADC1D_bm  (1<<ADC1D_bp)
#define ADC0D_bp  (0)
#define ADC0D_bm  (1<<ADC0D_bp)

/* EIMSK */
#define INT0_bp   (0)
#define INT1_bp   (1)

/* PCICR */
#define PCIE0_bp  (0)
#define PCIE1_bp  (1)
#define PCIE2_bp  (2)

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

/* EECR */
#define EERIE_bp  (3)

/* ACSR */
#define ACIE_bp   (3)

/* TWCR */
#define TWIE_bp   (0)

/* SPMCSR */
#define SPMIE_bp  (7)

#endif /* INCLUDE_SNOWFOX_CPU_AVR_IO_ATMEGA328P_H_ */
