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

#ifndef INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATMEGA164P_324P_644P_1284P_INTERRUPTCONTROLLER_H_
#define INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATMEGA164P_324P_644P_1284P_INTERRUPTCONTROLLER_H_

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

namespace ATMEGA164P_324P_644P_1284P
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Interrupt : uint8_t
{
  EXTERNAL_INT0                   =  0,
  EXTERNAL_INT1                   =  1,
  EXTERNAL_INT2                   =  2,
  PIN_CHANGE_INT0                 =  3,
  PIN_CHANGE_INT1                 =  4,
  PIN_CHANGE_INT2                 =  5,
  PIN_CHANGE_INT3                 =  6,
  PIN_CHANGE_INT4                 =  7,
  PIN_CHANGE_INT5                 =  8,
  PIN_CHANGE_INT6                 =  9,
  PIN_CHANGE_INT7                 = 10,
  PIN_CHANGE_INT8                 = 11,
  PIN_CHANGE_INT9                 = 12,
  PIN_CHANGE_INT10                = 13,
  PIN_CHANGE_INT11                = 14,
  PIN_CHANGE_INT12                = 15,
  PIN_CHANGE_INT13                = 16,
  PIN_CHANGE_INT14                = 17,
  PIN_CHANGE_INT15                = 18,
  PIN_CHANGE_INT16                = 19,
  PIN_CHANGE_INT17                = 20,
  PIN_CHANGE_INT18                = 21,
  PIN_CHANGE_INT19                = 22,
  PIN_CHANGE_INT20                = 23,
  PIN_CHANGE_INT21                = 24,
  PIN_CHANGE_INT22                = 25,
  PIN_CHANGE_INT23                = 26,
  PIN_CHANGE_INT24                = 27,
  PIN_CHANGE_INT25                = 28,
  PIN_CHANGE_INT26                = 29,
  PIN_CHANGE_INT27                = 30,
  PIN_CHANGE_INT28                = 31,
  PIN_CHANGE_INT29                = 32,
  PIN_CHANGE_INT30                = 33,
  PIN_CHANGE_INT31                = 34,
  WATCHDOG_TIMER                  = 35,
  TIMER2_COMPARE_A                = 36,
  TIMER2_COMPARE_B                = 37,
  TIMER2_OVERFLOW                 = 38,
  TIMER1_CAPTURE                  = 39,
  TIMER1_COMPARE_A                = 40,
  TIMER1_COMPARE_B                = 41,
  TIMER1_OVERFLOW                 = 42,
  TIMER0_COMPARE_A                = 43,
  TIMER0_COMPARE_B                = 44,
  TIMER0_OVERFLOW                 = 45,
  SPI_SERIAL_TRANSFER_COMPLETE    = 46,
  USART0_RECEIVE_COMPLETE         = 47,
  USART0_UART_DATA_REGISTER_EMPTY = 48,
  USART0_TRANSMIT_COMPLETE        = 49,
  ANALOG_COMPARATOR               = 50,
  ANALOG_DIGITAL_CONVERTER        = 51,
  EEPROM_READY                    = 52,
  TWO_WIRE_INT                    = 53,
  SPM_READY                       = 54,
  USART1_RECEIVE_COMPLETE         = 55,
  USART1_UART_DATA_REGISTER_EMPTY = 56,
  USART1_TRANSMIT_COMPLETE        = 57,
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
                               volatile uint8_t * pcmsk3,
                               volatile uint8_t * wdtcsr,
                               volatile uint8_t * timsk0,
                               volatile uint8_t * timsk1,
                               volatile uint8_t * timsk2,
                               volatile uint8_t * ucsr0b,
                               volatile uint8_t * ucsr1b,
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
                   * _PCMSK3,
                   * _WDTCSR,
                   * _TIMSK0,
                   * _TIMSK1,
                   * _TIMSK2,
                   * _UCSR0B,
                   * _UCSR1B,
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

} /* ATMEGA164P_324P_644P_1284P */

} /* hal */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATMEGA164P_324P_644P_1284P_INTERRUPTCONTROLLER_H_ */
