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

#ifndef INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATMEGA3209_4809_INTERRUPTCONTROLLER_H_
#define INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATMEGA3209_4809_INTERRUPTCONTROLLER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/interface/interrupt/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::ATMEGA3209_4809
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Interrupt : uint8_t
{
  CRC_NMI                         =  0,
  VOLTAGE_LEVEL_MONITOR           =  1,
  /* RTC */
  RTC_OVERFLOW                    =  2,
  RTC_COMPARE                     =  3,
  RTC_PERIODIC_INTERRUPT          =  4,
  /* TIMER A0 */
  TIMERA0_OVERFLOW                =  5,
  TIMERA0_COMPARE_0               =  6,
  TIMERA0_COMPARE_1               =  7,
  TIMERA0_COMPARE_2               =  8,
  /* TIMER B0/1/2/3 */
  TIMERB0_CAPTURE                 =  9,
  TIMERB1_CAPTURE                 = 10,
  TIMERB2_CAPTURE                 = 11,
  TIMERB3_CAPTURE                 = 12,
  /* USART0 */
  USART0_RECEIVE_COMPLETE         = 13,
  USART0_TRANSMIT_COMPLETE        = 14,
  USART0_UART_DATA_REGISTER_EMPTY = 15,
  USART0_RECEIVER_START_OF_FRAME  = 16,
  /* USART1 */
  USART1_RECEIVE_COMPLETE         = 17,
  USART1_TRANSMIT_COMPLETE        = 18,
  USART1_UART_DATA_REGISTER_EMPTY = 19,
  USART1_RECEIVER_START_OF_FRAME  = 20,
  /* USART2 */
  USART2_RECEIVE_COMPLETE         = 21,
  USART2_TRANSMIT_COMPLETE        = 22,
  USART2_UART_DATA_REGISTER_EMPTY = 23,
  USART2_RECEIVER_START_OF_FRAME  = 24,
  /* USART3 */
  USART3_RECEIVE_COMPLETE         = 25,
  USART3_TRANSMIT_COMPLETE        = 26,
  USART3_UART_DATA_REGISTER_EMPTY = 28,
  USART3_RECEIVER_START_OF_FRAME  = 29,
  /* TWI0_MASTER/SLAVE */
  TWI0_MASTER_READ                = 30,
  TWI0_MASTER_WRITE               = 31,
  TWI0_SLAVE_DATA                 = 32,
  TWI0_SLAVE_ADDRESS              = 33,
  TWI0_SLAVE_STOP                 = 34,
  /* CCL */
  CONFIGURABLE_CUSTOM_LOGIC       = 35,
  /* EXTERNAL INT / PORT */
  EXTERNAL_INTERRUPT_PORT_A       = 36,
  EXTERNAL_INTERRUPT_PORT_B       = 37,
  EXTERNAL_INTERRUPT_PORT_C       = 38,
  EXTERNAL_INTERRUPT_PORT_D       = 39,
  EXTERNAL_INTERRUPT_PORT_E       = 40,
  EXTERNAL_INTERRUPT_PORT_F       = 41,
  /* ADC / AC */
  ANALOG_COMPARATOR               = 42,
  ADC_RESULT_READY                = 43,
  ADC_WINDOW_COMPARE              = 44,
  /* EEPROM */
  EEPROM_READY                    = 45,
  /* SPI */
  SPI0_TRANFER_COMPLETE           = 46,
  SPI0_WRITE_COLLISION            = 47,
  /* MISC */
  GLOBAL                          = interface::InterruptController::GLOBAL_INT_NUM,
  INVALID                         = interface::InterruptController::INVALID_INT_NUM
};

/**************************************************************************************
 * CONSTEXPR FUNCTIONS
 **************************************************************************************/

constexpr uint8_t toIntNum(Interrupt const interrupt)
{
  return static_cast<uint8_t>(interrupt);
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
                               volatile uint8_t * tcb3_intctrl,
                               volatile uint8_t * usart0_ctrla,
                               volatile uint8_t * usart1_ctrla,
                               volatile uint8_t * usart2_ctrla,
                               volatile uint8_t * usart3_ctrla,
                               volatile uint8_t * twi_mctrla,
                               volatile uint8_t * twi_sctrla,
                               volatile uint8_t * spi_intctrl);
  virtual ~InterruptController();


  /* Interrupt Controller Interface */

  virtual void enableInterrupt (uint8_t const int_num) override;
  virtual void disableInterrupt(uint8_t const int_num) override;


  /* Interrupt Controller Assembly Interface */

  virtual void registerInterruptCallback(uint8_t const int_num, interface::InterruptCallback * interrupt_callback) override;


private:

  volatile uint8_t * _CRCSCAN_CTRLA,
                   * _BOD_INTCTRL,
                   * _RTC_INTCTRL,
                   * _RTC_PITINTCTRL,
                   * _TCA0_INTCTRL,
                   * _TCB0_INTCTRL,
                   * _TCB1_INTCTRL,
                   * _TCB2_INTCTRL,
                   * _TCB3_INTCTRL,
                   * _USART0_CTRLA,
                   * _USART1_CTRLA,
                   * _USART2_CTRLA,
                   * _USART3_CTRLA,
                   * _TWI_MCTRLA,
                   * _TWI_SCTRLA,
                   * _SPI_INTCTRL;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::ATMEGA3209_4809 */

#endif /* INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATMEGA3209_4809_INTERRUPTCONTROLLER_H_ */
