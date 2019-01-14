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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_INTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_INTERRUPTCONTROLLER_H_

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

namespace ATMEGA328P
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Interrupt : uint8_t
{
  EXTERNAL_INT0                  =  0,
  EXTERNAL_INT1                  =  1,
  PIN_CHANGE_INT0                =  2,
  PIN_CHANGE_INT1                =  3,
  PIN_CHANGE_INT2                =  4,
  PIN_CHANGE_INT3                =  5,
  PIN_CHANGE_INT4                =  6,
  PIN_CHANGE_INT5                =  7,
  PIN_CHANGE_INT6                =  8,
  PIN_CHANGE_INT7                =  9,
  PIN_CHANGE_INT8                = 10,
  PIN_CHANGE_INT9                = 11,
  PIN_CHANGE_INT10               = 12,
  PIN_CHANGE_INT11               = 13,
  PIN_CHANGE_INT12               = 14,
  PIN_CHANGE_INT13               = 15,
  PIN_CHANGE_INT14               = 16,
  PIN_CHANGE_INT16               = 17,
  PIN_CHANGE_INT17               = 18,
  PIN_CHANGE_INT18               = 19,
  PIN_CHANGE_INT19               = 20,
  PIN_CHANGE_INT20               = 21,
  PIN_CHANGE_INT21               = 22,
  PIN_CHANGE_INT22               = 23,
  PIN_CHANGE_INT23               = 24,
  WATCHDOG_TIMER                 = 25,
  TIMER2_COMPARE_A               = 26,
  TIMER2_COMPARE_B               = 27,
  TIMER2_OVERFLOW                = 28,
  TIMER1_CAPTURE                 = 29,
  TIMER1_COMPARE_A               = 30,
  TIMER1_COMPARE_B               = 31,
  TIMER1_OVERFLOW                = 32,
  TIMER0_COMPARE_A               = 33,
  TIMER0_COMPARE_B               = 34,
  TIMER0_OVERFLOW                = 35,
  SPI_SERIAL_TRANSFER_COMPLETE   = 36,
  USART_RECEIVE_COMPLETE         = 37,
  USART_UART_DATA_REGISTER_EMPTY = 38,
  USART_TRANSMIT_COMPLETE        = 39,
  ANALOG_DIGITAL_CONVERTER       = 40,
  EEPROM_READY                   = 41,
  ANALOG_COMPARATOR              = 42,
  TWO_WIRE_INT                   = 43,
  SPM_READY                      = 44,
  GLOBAL                         = interface::InterruptController::GLOBAL_INT_NUM,
  INVALID                        = interface::InterruptController::INVALID_INT_NUM
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
                               volatile uint8_t * ucsr0b,
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
                   * _UCSR0B,
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

} /* ATMEGA328P */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_INTERRUPTCONTROLLER_H_ */
