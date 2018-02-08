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

#ifndef INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_INTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_INTERRUPTCONTROLLER_H_


/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/interface/interrupt/InterruptController.h>
#include <spectre/hal/interface/interrupt/InterruptControllerAssembly.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace AT90CAN128
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint8_t const EXTERNAL_INT0                    = 0;
static uint8_t const EXTERNAL_INT1                    = 1;
static uint8_t const EXTERNAL_INT2                    = 2;
static uint8_t const EXTERNAL_INT3                    = 3;
static uint8_t const EXTERNAL_INT4                    = 4;
static uint8_t const EXTERNAL_INT5                    = 5;
static uint8_t const EXTERNAL_INT6                    = 6;
static uint8_t const EXTERNAL_INT7                    = 7;
static uint8_t const TIMER2_COMPARE                   = 8;
static uint8_t const TIMER2_OVERFLOW                  = 9;
static uint8_t const TIMER1_CAPTURE                   = 10;
static uint8_t const TIMER1_COMPARE_A                 = 11;
static uint8_t const TIMER1_COMPARE_B                 = 12;
static uint8_t const TIMER1_COMPARE_C                 = 13;
static uint8_t const TIMER1_OVERFLOW                  = 14;
static uint8_t const TIMER0_COMPARE                   = 15;
static uint8_t const TIMER0_OVERFLOW                  = 16;
static uint8_t const CAN_INT                          = 17;
static uint8_t const CAN_TIMER_OVERRUN                = 18;
static uint8_t const SPI_SERIAL_TRANSFER_COMPLETE     = 19;
static uint8_t const USART0_RECEIVE_COMPLETE          = 20;
static uint8_t const USART0_UART_DATA_REGISTER_EMPTY  = 21;
static uint8_t const USART0_TRANSMIT_COMPLETE         = 22;
static uint8_t const ANALOG_COMPARATOR                = 23;
static uint8_t const ANALOG_DIGITAL_CONVERTER         = 24;
static uint8_t const EEPROM_READY                     = 25;
static uint8_t const TIMER3_CAPTURE                   = 26;
static uint8_t const TIMER3_COMPARE_A                 = 27;
static uint8_t const TIMER3_COMPARE_B                 = 28;
static uint8_t const TIMER3_COMPARE_C                 = 29;
static uint8_t const TIMER3_OVERFLOW                  = 30;
static uint8_t const USART1_RECEIVE_COMPLETE          = 31;
static uint8_t const USART1_UART_DATA_REGISTER_EMPTY  = 32;
static uint8_t const USART1_TRANSMIT_COMPLETE         = 33;
static uint8_t const TWO_WIRE_INT                     = 34;
static uint8_t const SPM_READY                        = 35;
static uint8_t const GLOBAL                           = 36;

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class InterruptController : public interface::InterruptController,
                            public interface::InterruptControllerAssembly
{

public:

           InterruptController(volatile uint8_t * eimsk,
                               volatile uint8_t * timsk2,
                               volatile uint8_t * timsk1,
                               volatile uint8_t * timsk0,
                               volatile uint8_t * cangie,
                               volatile uint8_t * spcr,
                               volatile uint8_t * ucsr0b,
                               volatile uint8_t * acsr,
                               volatile uint8_t * adcsra,
                               volatile uint8_t * eecr,
                               volatile uint8_t * timsk3,
                               volatile uint8_t * ucsr1b,
                               volatile uint8_t * twcr,
                               volatile uint8_t * spmcsr);
  virtual ~InterruptController();


  /* Interrupt Controller Interface */

  virtual void enableInterrupt (uint8_t const int_num) override;
  virtual void disableInterrupt(uint8_t const int_num) override;


  /* Interrupt Controller Assembly Interface */

  virtual void registerISR(uint8_t            const int_num,
                           interface::ISRFunc       isr_func,
                           interface::ISRArg        isr_arg) override;

private:

  volatile uint8_t * _EIMSK,
                   * _TIMSK2,
                   * _TIMSK1,
                   * _TIMSK0,
                   * _CANGIE,
                   * _SPCR,
                   * _UCSR0B,
                   * _ACSR,
                   * _ADCSRA,
                   * _EECR,
                   * _TIMSK3,
                   * _UCSR1B,
                   * _TWCR,
                   * _SPMCSR;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN128 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_INTERRUPTCONTROLLER_H_ */
