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

#ifndef INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA16U4_32U4_INTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA16U4_32U4_INTERRUPTCONTROLLER_H_

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
  USB_GENERAL                     =  6,
  USB_ENDPOINT                    =  7,
  WATCHDOG_TIMER                  =  8,
  TIMER1_CAPTURE                  =  9,
  TIMER1_COMPARE_A                = 10,
  TIMER1_COMPARE_B                = 11,
  TIMER1_COMPARE_C                = 12,
  TIMER1_OVERFLOW                 = 13,
  TIMER0_COMPARE_A                = 14,
  TIMER0_COMPARE_B                = 15,
  TIMER0_OVERFLOW                 = 16,
  SPI_SERIAL_TRANSFER_COMPLETE    = 17,
  USART1_RECEIVE_COMPLETE         = 18,
  USART1_UART_DATA_REGISTER_EMPTY = 19,
  USART1_TRANSMIT_COMPLETE        = 20,
  ANALOG_COMPARATOR               = 21,
  ANALOG_DIGITAL_CONVERTER        = 22,
  EEPROM_READY                    = 23,
  TIMER3_CAPTURE                  = 24,
  TIMER3_COMPARE_A                = 25,
  TIMER3_COMPARE_B                = 26,
  TIMER3_COMPARE_C                = 27,
  TIMER3_OVERFLOW                 = 28,
  TWO_WIRE_INT                    = 29,
  SPM_READY                       = 30,
  TIMER4_COMPARE_A                = 31,
  TIMER4_COMPARE_B                = 32,
  TIMER4_COMPARE_D                = 33,
  TIMER4_OVERFLOW                 = 34,
  TIMER4_FAULT_PROTECTION         = 35,
  GLOBAL                          = 36,
  INVALID                         = interface::InterruptController::INVALID_INT_NUM
};

enum class InterruptServiceRoutine : uint8_t
{
  EXTERNAL_INT0                   =  0,
  EXTERNAL_INT1                   =  1,
  EXTERNAL_INT2                   =  2,
  EXTERNAL_INT3                   =  3,
  EXTERNAL_INT6                   =  4,
  PIN_CHANGE_INT0                 =  5,
  USB_GENERAL                     =  6,
  USB_ENDPOINT                    =  7,
  WATCHDOG_TIMER                  =  8,
  TIMER1_CAPTURE                  =  9,
  TIMER1_COMPARE_A                = 10,
  TIMER1_COMPARE_B                = 11,
  TIMER1_COMPARE_C                = 12,
  TIMER1_OVERFLOW                 = 13,
  TIMER0_COMPARE_A                = 14,
  TIMER0_COMPARE_B                = 15,
  TIMER0_OVERFLOW                 = 16,
  SPI_SERIAL_TRANSFER_COMPLETE    = 17,
  USART1_RECEIVE_COMPLETE         = 18,
  USART1_UART_DATA_REGISTER_EMPTY = 19,
  USART1_TRANSMIT_COMPLETE        = 20,
  ANALOG_COMPARATOR               = 21,
  ANALOG_DIGITAL_CONVERTER        = 22,
  EEPROM_READY                    = 23,
  TIMER3_CAPTURE                  = 24,
  TIMER3_COMPARE_A                = 25,
  TIMER3_COMPARE_B                = 26,
  TIMER3_COMPARE_C                = 27,
  TIMER3_OVERFLOW                 = 28,
  TWO_WIRE_INT                    = 29,
  SPM_READY                       = 30,
  TIMER4_COMPARE_A                = 31,
  TIMER4_COMPARE_B                = 32,
  TIMER4_COMPARE_D                = 33,
  TIMER4_OVERFLOW                 = 34,
  TIMER4_FAULT_PROTECTION         = 35
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

class InterruptController : public interface::InterruptController
{

public:

           InterruptController(volatile uint8_t * eimsk,
                               volatile uint8_t * pcicr);
  virtual ~InterruptController();


  /* Interrupt Controller Interface */

  virtual void enableInterrupt (uint8_t const int_num) override;
  virtual void disableInterrupt(uint8_t const int_num) override;


  /* Interrupt Controller Assembly Interface */

  virtual void registerInterruptCallback(uint8_t const isr_num, interface::InterruptCallback * interrupt_callback) override;


private:

  volatile uint8_t * _EIMSK,
                   * _PCICR;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA16U4_32U4 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA16U4_32U4_INTERRUPTCONTROLLER_H_ */
