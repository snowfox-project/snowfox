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

#ifndef INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA640_1280_2560_INTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA640_1280_2560_INTERRUPTCONTROLLER_H_

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
  WATCHDOG_TIMER                  = 11,
  TIMER2_COMPARE_A                = 12,
  TIMER2_COMPARE_B                = 13,
  TIMER2_OVERFLOW                 = 14,
  TIMER1_CAPTURE                  = 15,
  TIMER1_COMPARE_A                = 16,
  TIMER1_COMPARE_B                = 17,
  TIMER1_COMPARE_C                = 18,
  TIMER1_OVERFLOW                 = 19,
  TIMER0_COMPARE_A                = 20,
  TIMER0_COMPARE_B                = 21,
  TIMER0_OVERFLOW                 = 22,
  SPI_SERIAL_TRANSFER_COMPLETE    = 23,
  USART0_RECEIVE_COMPLETE         = 24,
  USART0_UART_DATA_REGISTER_EMPTY = 25,
  USART0_TRANSMIT_COMPLETE        = 26,
  ANALOG_COMPARATOR               = 27,
  ANALOG_DIGITAL_CONVERTER        = 28,
  EEPROM_READY                    = 29,
  TIMER3_CAPTURE                  = 30,
  TIMER3_COMPARE_A                = 31,
  TIMER3_COMPARE_B                = 32,
  TIMER3_COMPARE_C                = 33,
  TIMER3_OVERFLOW                 = 34,
  USART1_RECEIVE_COMPLETE         = 35,
  USART1_UART_DATA_REGISTER_EMPTY = 36,
  USART1_TRANSMIT_COMPLETE        = 37,
  TWO_WIRE_INT                    = 38,
  SPM_READY                       = 39,
  TIMER4_CAPTURE                  = 40,
  TIMER4_COMPARE_A                = 41,
  TIMER4_COMPARE_B                = 42,
  TIMER4_COMPARE_C                = 43,
  TIMER4_OVERFLOW                 = 44,
  TIMER5_CAPTURE                  = 45,
  TIMER5_COMPARE_A                = 46,
  TIMER5_COMPARE_B                = 47,
  TIMER5_COMPARE_C                = 48,
  TIMER5_OVERFLOW                 = 49,
  USART2_RECEIVE_COMPLETE         = 50,
  USART2_UART_DATA_REGISTER_EMPTY = 51,
  USART2_TRANSMIT_COMPLETE        = 52,
  USART3_RECEIVE_COMPLETE         = 53,
  USART3_UART_DATA_REGISTER_EMPTY = 54,
  USART3_TRANSMIT_COMPLETE        = 55,
  GLOBAL                          = 56,
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

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA640_1280_2560_INTERRUPTCONTROLLER_H_ */
