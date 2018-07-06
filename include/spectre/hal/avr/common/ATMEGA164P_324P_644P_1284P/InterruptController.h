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

#ifndef INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA164P_324P_644P_1284P_INTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA164P_324P_644P_1284P_INTERRUPTCONTROLLER_H_

/**************************************************************************************
 * INCLUDE
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
  WATCHDOG_TIMER                  =  7,
  TIMER2_COMPARE_A                =  8,
  TIMER2_COMPARE_B                =  9,
  TIMER2_OVERFLOW                 = 10,
  TIMER1_CAPTURE                  = 11,
  TIMER1_COMPARE_A                = 12,
  TIMER1_COMPARE_B                = 13,
  TIMER1_OVERFLOW                 = 14,
  TIMER0_COMPARE_A                = 15,
  TIMER0_COMPARE_B                = 16,
  TIMER0_OVERFLOW                 = 17,
  SPI_SERIAL_TRANSFER_COMPLETE    = 18,
  USART0_RECEIVE_COMPLETE         = 19,
  USART0_UART_DATA_REGISTER_EMPTY = 20,
  USART0_TRANSMIT_COMPLETE        = 21,
  ANALOG_COMPARATOR               = 22,
  ANALOG_DIGITAL_CONVERTER        = 23,
  EEPROM_READY                    = 24,
  TWO_WIRE_INT                    = 25,
  SPM_READY                       = 26,
  USART1_RECEIVE_COMPLETE         = 27,
  USART1_UART_DATA_REGISTER_EMPTY = 28,
  USART1_TRANSMIT_COMPLETE        = 29,
  GLOBAL                          = 30,
  INVALID                         = interface::InterruptController::INVALID_INT_NUM
};

enum class InterruptServiceRoutine : uint8_t
{
  EXTERNAL_INT0                   =  0,
  EXTERNAL_INT1                   =  1,
  EXTERNAL_INT2                   =  2,
  PIN_CHANGE_INT0                 =  3,
  PIN_CHANGE_INT1                 =  4,
  PIN_CHANGE_INT2                 =  5,
  PIN_CHANGE_INT3                 =  6,
  WATCHDOG_TIMER                  =  7,
  TIMER2_COMPARE_A                =  8,
  TIMER2_COMPARE_B                =  9,
  TIMER2_OVERFLOW                 = 10,
  TIMER1_CAPTURE                  = 11,
  TIMER1_COMPARE_A                = 12,
  TIMER1_COMPARE_B                = 13,
  TIMER1_OVERFLOW                 = 14,
  TIMER0_COMPARE_A                = 15,
  TIMER0_COMPARE_B                = 16,
  TIMER0_OVERFLOW                 = 17,
  SPI_SERIAL_TRANSFER_COMPLETE    = 18,
  USART0_RECEIVE_COMPLETE         = 19,
  USART0_UART_DATA_REGISTER_EMPTY = 20,
  USART0_TRANSMIT_COMPLETE        = 21,
  ANALOG_COMPARATOR               = 22,
  ANALOG_DIGITAL_CONVERTER        = 23,
  EEPROM_READY                    = 24,
  TWO_WIRE_INT                    = 25,
  SPM_READY                       = 26,
  USART1_RECEIVE_COMPLETE         = 27,
  USART1_UART_DATA_REGISTER_EMPTY = 28,
  USART1_TRANSMIT_COMPLETE        = 29
};

/**************************************************************************************
 * CONSTEXPR FUNCTIONS
 **************************************************************************************/

constexpr uint8_t toIntNum(Interrupt const interrupt)
{
  return static_cast<uint8_t>(interrupt);
}

constexpr uint8_t toIsrNum(InterruptServiceRoutine const interrupt_service_routine)
{
  return static_cast<uint8_t>(interrupt_service_routine);
}

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class InterruptController : public interface::InterruptController,
                            public interface::InterruptControllerAssembly
{

public:

           InterruptController(volatile uint8_t * eimsk,
                               volatile uint8_t * pcicr,
                               volatile uint8_t * wdtcsr,
                               volatile uint8_t * timsk2,
                               volatile uint8_t * timsk1,
                               volatile uint8_t * timsk0,
                               volatile uint8_t * spcr,
                               volatile uint8_t * ucsr0b,
                               volatile uint8_t * acsr,
                               volatile uint8_t * adcsra,
                               volatile uint8_t * eecr,
                               volatile uint8_t * twcr,
                               volatile uint8_t * spmcsr,
                               volatile uint8_t * ucsr1b);
  virtual ~InterruptController();


  /* Interrupt Controller Interface */

  virtual void enableInterrupt (uint8_t const int_num) override;
  virtual void disableInterrupt(uint8_t const int_num) override;


  /* Interrupt Controller Assembly Interface */

  virtual void registerInterruptCallback(uint8_t const isr_num, interface::InterruptCallback * interrupt_callback) override;


private:

  volatile uint8_t * _EIMSK,
                   * _PCICR,
                   * _WDTCSR,
                   * _TIMSK2,
                   * _TIMSK1,
                   * _TIMSK0,
                   * _SPCR,
                   * _UCSR0B,
                   * _ACSR,
                   * _ADCSRA,
                   * _EECR,
                   * _TWCR,
                   * _SPMCSR,
                   * _UCSR1B;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA164P_324P_644P_1284P */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA164P_324P_644P_1284P_INTERRUPTCONTROLLER_H_ */
