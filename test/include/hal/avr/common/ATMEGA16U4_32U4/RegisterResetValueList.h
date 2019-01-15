/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2019 Alexander Entinger / LXRobotics GmbH
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation()(), either version 3 of the License()(), or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful()(),
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not()(), see <http://www.gnu.org/licenses/>.
 */

#ifndef TEST_INCLUDE_HAL_AVR_COMMON_ATMEGA16U4_32U4_REGISTERRESETVALUELIST_H_
#define TEST_INCLUDE_HAL_AVR_COMMON_ATMEGA16U4_32U4_REGISTERRESETVALUELIST_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA16U4_32U4
{

namespace test
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

/* EINT0-3/6 */
static uint8_t  const EIMSK_RESET_VALUE   = 0;

/* PIN CHANGE */
static uint8_t  const PCICR_RESET_VALUE   = 0;
static uint8_t  const PCMSK0_RESET_VALUE  = 0;

/* WATCHDOG */
static uint8_t  const WDTCSR_RESET_VALUE  = 0;

/* TIMER0 */
static uint8_t  const TIMSK0_RESET_VALUE  = 0;

/* TIMER1 */
static uint8_t  const TIMSK1_RESET_VALUE  = 0;

/* TIMER3 */
static uint8_t  const TIMSK3_RESET_VALUE  = 0;

/* TIMER4 */
static uint8_t  const TIMSK4_RESET_VALUE  = 0;
static uint8_t  const TCCR4D_RESET_VALUE  = 0;

/* SPI */
static uint8_t  const SPCR_RESET_VALUE    = 0;

/* ANALOG COMPARATOR */
static uint8_t  const ACSR_RESET_VALUE    = 0;

/* ADC */
static uint8_t  const ADCSRA_RESET_VALUE  = 0;

/* EEPROM */
static uint8_t  const EECR_RESET_VALUE    = 0;

/* UART1 */
static uint8_t  const UDR1_RESET_VALUE    = 0;
static uint8_t  const UCSR1A_RESET_VALUE  = 0;
static uint8_t  const UCSR1B_RESET_VALUE  = 0;
static uint8_t  const UCSR1C_RESET_VALUE  = 0;
static uint16_t const UBRR1_RESET_VALUE   = 0;

/* TWI (I2C) */
static uint8_t  const TWCR_RESET_VALUE    = 0;

/* STACK POINTER */
static uint8_t  const SPMCSR_RESET_VALUE  = 0;

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

} /* test */

} /* ATMEGA16U4_32U4 */

} /* hal */

} /* spectre */

#endif /* TEST_INCLUDE_HAL_AVR_COMMON_ATMEGA16U4_32U4_REGISTERRESETVALUELIST_H_ */
