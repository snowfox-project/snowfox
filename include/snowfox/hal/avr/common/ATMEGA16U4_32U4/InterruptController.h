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

#ifndef INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATMEGA16U4_32U4_INTERRUPTCONTROLLER_H_
#define INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATMEGA16U4_32U4_INTERRUPTCONTROLLER_H_

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

namespace ATMEGA16U4_32U4
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
  EXTERNAL_INT6                   =  4,
  PIN_CHANGE_INT0                 =  5,
  PIN_CHANGE_INT1                 =  6,
  PIN_CHANGE_INT2                 =  7,
  PIN_CHANGE_INT3                 =  8,
  PIN_CHANGE_INT4                 =  9,
  PIN_CHANGE_INT5                 = 10,
  PIN_CHANGE_INT6                 = 11,
  PIN_CHANGE_INT7                 = 12,
  USB_GENERAL                     = 13,
  USB_ENDPOINT                    = 14,
  WATCHDOG_TIMER                  = 15,
  TIMER1_CAPTURE                  = 16,
  TIMER1_COMPARE_A                = 17,
  TIMER1_COMPARE_B                = 18,
  TIMER1_COMPARE_C                = 19,
  TIMER1_OVERFLOW                 = 20,
  TIMER0_COMPARE_A                = 21,
  TIMER0_COMPARE_B                = 22,
  TIMER0_OVERFLOW                 = 23,
  SPI_SERIAL_TRANSFER_COMPLETE    = 24,
  USART1_RECEIVE_COMPLETE         = 25,
  USART1_UART_DATA_REGISTER_EMPTY = 26,
  USART1_TRANSMIT_COMPLETE        = 27,
  ANALOG_COMPARATOR               = 28,
  ANALOG_DIGITAL_CONVERTER        = 29,
  EEPROM_READY                    = 30,
  TIMER3_CAPTURE                  = 31,
  TIMER3_COMPARE_A                = 32,
  TIMER3_COMPARE_B                = 33,
  TIMER3_COMPARE_C                = 34,
  TIMER3_OVERFLOW                 = 35,
  TWO_WIRE_INT                    = 36,
  SPM_READY                       = 37,
  TIMER4_COMPARE_A                = 38,
  TIMER4_COMPARE_B                = 39,
  TIMER4_COMPARE_D                = 40,
  TIMER4_OVERFLOW                 = 41,
  TIMER4_FAULT_PROTECTION         = 42,
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
                               volatile uint8_t * wdtcsr,
                               volatile uint8_t * timsk0,
                               volatile uint8_t * timsk1,
                               volatile uint8_t * timsk3,
                               volatile uint8_t * timsk4,
                               volatile uint8_t * tccr4d,
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
                   * _WDTCSR,
                   * _TIMSK0,
                   * _TIMSK1,
                   * _TIMSK3,
                   * _TIMSK4,
                   * _TCCR4D,
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

} /* ATMEGA16U4_32U4 */

} /* hal */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_HAL_AVR_COMMON_ATMEGA16U4_32U4_INTERRUPTCONTROLLER_H_ */
