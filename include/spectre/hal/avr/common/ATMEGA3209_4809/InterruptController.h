/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA3209_4809_INTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA3209_4809_INTERRUPTCONTROLLER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/interrupt/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA3209_4809
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Interrupt : uint8_t
{
  CRC_NMI,
  VOLTAGE_LEVEL_MONITOR,
  RTC_OVERFLOW,
  RTC_COMPARE,
  RTC_PERIODIC_INTERRUPT,
  TIMERA0_OVER_UNDERFLOW,
  TIMERA0_COMPARE_0,
  TIMERA0_COMPARE_1,
  TIMERA0_COMPARE_2,
  TIMERB0_CAPTURE,
  TIMERB1_CAPTURE,
  TIMERB2_CAPTURE,
  TIMERB3_CAPTURE
};

enum class Isr : uint8_t
{
  CRC_NMI                         =  0,
  VOLTAGE_LEVEL_MONITOR           =  1,
  RTC_OVERFLOW_OR_COMPARE         =  2,
  RTC_PERIODIC_INTERRUPT          =  3,
  CONFIGURABLE_CUSTOM_LOGIC       =  4,
  PORTA_EXTERNAL_INT              =  5,
  TIMERA0_OVERFLOW                =  6,
  TIMERA0_UNDERFLOW               =  7,
  TIMERA0_COMPARE_0               =  8,
  TIMERA0_COMPARE_1               =  9,
  TIMERA0_COMPARE_2               = 10,
  TIMERB0_CAPTURE                 = 11,
  TIMERB1_CAPTURE                 = 12,
  TWI0_SLAVE                      = 13,
  TWI0_MASTER                     = 14,
  SPI0                            = 15,
  USART0_RECEIVE_COMPLETE         = 16,
  USART0_UART_DATA_REGISTER_EMPTY = 17,
  USART0_TRANSMIT_COMPLETE        = 18,
  PORTD_EXTERNAL_INT              = 19,
  ANALOG_COMPARATOR               = 20,
  ADC0_RESULT_READY               = 21,
  ADC0_WINDOW_COMPARE             = 22,
  PORTC_EXTERNAL_INT              = 23,
  TIMERB2_CAPTURE                 = 24,
  USART1_RECEIVE_COMPLETE         = 25,
  USART1_UART_DATA_REGISTER_EMPTY = 26,
  USART1_TRANSMIT_COMPLETE        = 27,
  PORTF_EXTERNAL_INT              = 28,
  NON_VOLATILE_MEMORY_READY       = 29,
  USART2_RECEIVE_COMPLETE         = 30,
  USART2_UART_DATA_REGISTER_EMPTY = 31,
  USART2_TRANSMIT_COMPLETE        = 32,
  PORTB_EXTERNAL_INT              = 33,
  PORTE_EXTERNAL_INT              = 34,
  TIMERB3_CAPTURE                 = 35,
  USART3_RECEIVE_COMPLETE         = 36,
  USART3_UART_DATA_REGISTER_EMPTY = 37,
  USART3_TRANSMIT_COMPLETE        = 38,
  GLOBAL                          = 39,
  INVALID                         = interface::InterruptController::INVALID_INT_NUM
};

/**************************************************************************************
 * CONSTEXPR FUNCTIONS
 **************************************************************************************/

constexpr uint8_t toIntNum(Interrupt const interrupt)
{
  return static_cast<uint8_t>(interrupt);
}

constexpr uint8_t toIsrNum(Isr const isr)
{
  return static_cast<uint8_t>(isr);
}

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class InterruptController : public interface::InterruptController
{

public:

           InterruptController(volatile uint8_t * crcscan_ctrla,
                               volatile uint8_t * bod_intctrl,
                               volatile uint8_t * rtc_intctrl,
                               volatile uint8_t * rtc_pitintctrl,
                               volatile uint8_t * tca0_intctrl,
                               volatile uint8_t * tcb0_intctrl,
                               volatile uint8_t * tcb1_intctrl,
                               volatile uint8_t * tcb2_intctrl,
                               volatile uint8_t * tcb3_intctrl);
  virtual ~InterruptController();


  /* Interrupt Controller Interface */

  virtual void enableInterrupt (uint8_t const int_num) override;
  virtual void disableInterrupt(uint8_t const int_num) override;


  /* Interrupt Controller Assembly Interface */

  virtual void registerInterruptCallback(uint8_t const isr_num, interface::InterruptCallback * interrupt_callback) override;


private:

  volatile uint8_t * _CRCSCAN_CTRLA,
                   * _BOD_INTCTRL,
                   * _RTC_INTCTRL,
                   * _RTC_PITINTCTRL,
                   * _TCA0_INTCTRL,
                   * _TCB0_INTCTRL,
                   * _TCB1_INTCTRL,
                   * _TCB2_INTCTRL,
                   * _TCB3_INTCTRL;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA3209_4809 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA3209_4809_INTERRUPTCONTROLLER_H_ */
