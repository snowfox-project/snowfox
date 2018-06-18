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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_INTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_INTERRUPTCONTROLLER_H_

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

namespace ATMEGA328P
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Interrupt : uint8_t
{
  EXTERNAL_INT0                   =  0,
  EXTERNAL_INT1                   =  1,
  PIN_CHANGE_INT0                 =  2,
  PIN_CHANGE_INT1                 =  3,
  PIN_CHANGE_INT2                 =  4,
  WATCHDOG_TIMER                  =  5,
  TIMER2_COMPARE_A                =  6,
  TIMER2_COMPARE_B                =  7,
  TIMER2_OVERFLOW                 =  8,
  TIMER1_CAPTURE                  =  9,
  TIMER1_COMPARE_A                = 11,
  TIMER1_COMPARE_B                = 12,
  TIMER1_OVERFLOW                 = 13,
  TIMER0_COMPARE_A                = 14,
  TIMER0_COMPARE_B                = 15,
  TIMER0_OVERFLOW                 = 16,
  SPI_SERIAL_TRANSFER_COMPLETE    = 17,
  USART_RECEIVE_COMPLETE          = 18,
  USART_UART_DATA_REGISTER_EMPTY  = 19,
  USART_TRANSMIT_COMPLETE         = 20,
  ANALOG_DIGITAL_CONVERTER        = 21,
  EEPROM_READY                    = 22,
  ANALOG_COMPARATOR               = 23,
  TWO_WIRE_INT                    = 24,
  SPM_READY                       = 25,
  GLOBAL                          = 26
};

enum class InterruptServiceRoutine : uint8_t
{
  EXTERNAL_INT0                   =  0,
  EXTERNAL_INT1                   =  1,
  PIN_CHANGE_INT0                 =  2,
  PIN_CHANGE_INT1                 =  3,
  PIN_CHANGE_INT2                 =  4,
  WATCHDOG_TIMER                  =  5,
  TIMER2_COMPARE_A                =  6,
  TIMER2_COMPARE_B                =  7,
  TIMER2_OVERFLOW                 =  8,
  TIMER1_CAPTURE                  =  9,
  TIMER1_COMPARE_A                = 10,
  TIMER1_COMPARE_B                = 11,
  TIMER1_OVERFLOW                 = 12,
  TIMER0_COMPARE_A                = 13,
  TIMER0_COMPARE_B                = 14,
  TIMER0_OVERFLOW                 = 15,
  SPI_SERIAL_TRANSFER_COMPLETE    = 16,
  USART_RECEIVE_COMPLETE          = 17,
  USART_UART_DATA_REGISTER_EMPTY  = 18,
  USART_TRANSMIT_COMPLETE         = 19,
  ANALOG_DIGITAL_CONVERTER        = 20,
  EEPROM_READY                    = 21,
  ANALOG_COMPARATOR               = 22,
  TWO_WIRE_INT                    = 23,
  SPM_READY                       = 24
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
                               volatile uint8_t * adcsra,
                               volatile uint8_t * eecr,
                               volatile uint8_t * acsr,
                               volatile uint8_t * twcr,
                               volatile uint8_t * spmcsr);
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
                   * _ADCSRA,
                   * _EECR,
                   * _ACSR,
                   * _TWCR,
                   * _SPMCSR;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_INTERRUPTCONTROLLER_H_ */
