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

#ifndef INCLUDE_SPECTRE_CPU_AVR_IO_ATMEGA3209_4809_H_
#define INCLUDE_SPECTRE_CPU_AVR_IO_ATMEGA3209_4809_H_

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* CRCSCAN_CTRLA */
#define CRCSCAN_NMIEN_bp (1)

/* BOD_INTCTRL */
#define BOD_VLMIE_bp     (0)

/* RTC_INTCTRL */
#define RTC_CMP_bp       (1)
#define RTC_OVF_bp       (0)

/* RTC_PITINTCTRL */
#define RTC_PI_bp        (0)

/* TCAx_INTCTRL */
#define TCAx_CMP2_bp     (6)
#define TCAx_CMP1_bp     (5)
#define TCAx_CMP0_bp     (4)
#define TCAx_OVF_bp      (0)

/* TCBx_INTCTRL */
#define TCBx_CAPT_bp     (0)

/* USARTx_CTRLA */
#define USARTx_RXCIE_bp  (7)
#define USARTx_TXCIE_bp  (6)
#define USARTx_DREIE_bp  (5)
#define USARTx_RXSIE_bp  (4)

/* TWI_MLCTRA */
#define TWI_WIEN_bp      (6)
#define TWI_RIEN_bp      (7)

/* TWI_SLCTRA */
#define TWI_DIEN_bp      (7)
#define TWI_APIEN_bp     (6)
#define TWI_PIEN_bp      (5)

#endif /* INCLUDE_SPECTRE_CPU_AVR_IO_ATMEGA3209_4809_H_ */
