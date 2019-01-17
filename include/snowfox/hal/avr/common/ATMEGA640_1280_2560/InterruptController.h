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

#ifndef INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATMEGA640_1280_2560_INTERRUPTCONTROLLER_H_
#define INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATMEGA640_1280_2560_INTERRUPTCONTROLLER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/interface/interrupt/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace ATMEGA640_1280_2560
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Interrupt : uint8_t
{
  EXTERNAL_INT0                   =  0,
  EXTERNAL_INT1                   =  1,
  EXTERNAL_INT2                   =  2,
  EXTERNAL_INT3                   =  3,
  EXTERNAL_INT4                   =  4,
  EXTERNAL_INT5                   =  5,
  EXTERNAL_INT6                   =  6,
  EXTERNAL_INT7                   =  7,
  PIN_CHANGE_INT0                 =  8,
  PIN_CHANGE_INT1                 =  9,
  PIN_CHANGE_INT2                 = 10,
  PIN_CHANGE_INT3                 = 11,
  PIN_CHANGE_INT4                 = 12,
  PIN_CHANGE_INT5                 = 13,
  PIN_CHANGE_INT6                 = 14,
  PIN_CHANGE_INT7                 = 15,
  PIN_CHANGE_INT8                 = 16,
  PIN_CHANGE_INT9                 = 17,
  PIN_CHANGE_INT10                = 18,
  PIN_CHANGE_INT11                = 19,
  PIN_CHANGE_INT12                = 20,
  PIN_CHANGE_INT13                = 21,
  PIN_CHANGE_INT14                = 22,
  PIN_CHANGE_INT15                = 23,
  PIN_CHANGE_INT16                = 24,
  PIN_CHANGE_INT17                = 25,
  PIN_CHANGE_INT18                = 26,
  PIN_CHANGE_INT19                = 27,
  PIN_CHANGE_INT20                = 28,
  PIN_CHANGE_INT21                = 29,
  PIN_CHANGE_INT22                = 30,
  PIN_CHANGE_INT23                = 31,
  WATCHDOG_TIMER                  = 32,
  TIMER2_COMPARE_A                = 33,
  TIMER2_COMPARE_B                = 34,
  TIMER2_OVERFLOW                 = 35,
  TIMER1_CAPTURE                  = 36,
  TIMER1_COMPARE_A                = 37,
  TIMER1_COMPARE_B                = 38,
  TIMER1_COMPARE_C                = 39,
  TIMER1_OVERFLOW                 = 40,
  TIMER0_COMPARE_A                = 41,
  TIMER0_COMPARE_B                = 42,
  TIMER0_OVERFLOW                 = 43,
  SPI_SERIAL_TRANSFER_COMPLETE    = 44,
  USART0_RECEIVE_COMPLETE         = 45,
  USART0_UART_DATA_REGISTER_EMPTY = 46,
  USART0_TRANSMIT_COMPLETE        = 47,
  ANALOG_COMPARATOR               = 48,
  ANALOG_DIGITAL_CONVERTER        = 49,
  EEPROM_READY                    = 50,
  TIMER3_CAPTURE                  = 51,
  TIMER3_COMPARE_A                = 52,
  TIMER3_COMPARE_B                = 53,
  TIMER3_COMPARE_C                = 54,
  TIMER3_OVERFLOW                 = 55,
  USART1_RECEIVE_COMPLETE         = 56,
  USART1_UART_DATA_REGISTER_EMPTY = 57,
  USART1_TRANSMIT_COMPLETE        = 58,
  TWO_WIRE_INT                    = 59,
  SPM_READY                       = 60,
  TIMER4_CAPTURE                  = 61,
  TIMER4_COMPARE_A                = 62,
  TIMER4_COMPARE_B                = 63,
  TIMER4_COMPARE_C                = 64,
  TIMER4_OVERFLOW                 = 65,
  TIMER5_CAPTURE                  = 66,
  TIMER5_COMPARE_A                = 67,
  TIMER5_COMPARE_B                = 68,
  TIMER5_COMPARE_C                = 69,
  TIMER5_OVERFLOW                 = 70,
  USART2_RECEIVE_COMPLETE         = 71,
  USART2_UART_DATA_REGISTER_EMPTY = 72,
  USART2_TRANSMIT_COMPLETE        = 73,
  USART3_RECEIVE_COMPLETE         = 74,
  USART3_UART_DATA_REGISTER_EMPTY = 75,
  USART3_TRANSMIT_COMPLETE        = 76,
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

           InterruptController(volatile uint8_t * eimsk,
                               volatile uint8_t * pcicr,
                               volatile uint8_t * pcmsk0,
                               volatile uint8_t * pcmsk1,
                               volatile uint8_t * pcmsk2,
                               volatile uint8_t * wdtcsr,
                               volatile uint8_t * timsk0,
                               volatile uint8_t * timsk1,
                               volatile uint8_t * timsk2,
                               volatile uint8_t * timsk3,
                               volatile uint8_t * timsk4,
                               volatile uint8_t * timsk5,
                               volatile uint8_t * ucsr0b,
                               volatile uint8_t * ucsr1b,
                               volatile uint8_t * ucsr2b,
                               volatile uint8_t * ucsr3b,
                               volatile uint8_t * spcr,
                               volatile uint8_t * twcr,
                               volatile uint8_t * eecr,
                               volatile uint8_t * spmcsr,
                               volatile uint8_t * acsr,
                               volatile uint8_t * adcsra);
  virtual ~InterruptController();


  /* Interrupt Controller Interface */

  virtual void enableInterrupt (uint8_t const int_num) override;
  virtual void disableInterrupt(uint8_t const int_num) override;


  /* Interrupt Controller Assembly Interface */

  virtual void registerInterruptCallback(uint8_t const int_num, interface::InterruptCallback * interrupt_callback) override;


private:

  volatile uint8_t * _EIMSK,
                   * _PCICR,
                   * _PCMSK0,
                   * _PCMSK1,
                   * _PCMSK2,
                   * _WDTCSR,
                   * _TIMSK0,
                   * _TIMSK1,
                   * _TIMSK2,
                   * _TIMSK3,
                   * _TIMSK4,
                   * _TIMSK5,
                   * _UCSR0B,
                   * _UCSR1B,
                   * _UCSR2B,
                   * _UCSR3B,
                   * _SPCR,
                   * _TWCR,
                   * _EECR,
                   * _SPMCSR,
                   * _ACSR,
                   * _ADCSRA;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA640_1280_2560 */

} /* hal */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATMEGA640_1280_2560_INTERRUPTCONTROLLER_H_ */
