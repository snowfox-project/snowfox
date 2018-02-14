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
 * INCLUDES
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
 * TYPEDEFS
 **************************************************************************************/

enum class Interrupt : uint8_t
{
  EXTERNAL_INT0,
  EXTERNAL_INT1,
  PIN_CHANGE_INT0,
  PIN_CHANGE_INT1,
  PIN_CHANGE_INT2,
  WATCHDOG_TIMER,
  TIMER2_COMPARE_A,
  TIMER2_COMPARE_B,
  TIMER2_OVERFLOW,
  TIMER1_CAPTURE,
  TIMER1_COMPARE_A,
  TIMER1_COMPARE_B,
  TIMER1_OVERFLOW,
  TIMER0_COMPARE_A,
  TIMER0_COMPARE_B,
  TIMER0_OVERFLOW,
  SPI_SERIAL_TRANSFER_COMPLETE,
  USART_RECEIVE_COMPLETE,
  USART_UART_DATA_REGISTER_EMPTY,
  USART_TRANSMIT_COMPLETE,
  ANALOG_DIGITAL_CONVERTER,
  EEPROM_READY,
  ANALOG_COMPARATOR,
  TWO_WIRE_INT,
  SPM_READY,
  GLOBAL,
};

/**************************************************************************************
 * PROTOTYPES
 **************************************************************************************/

uint8_t toIntNum(Interrupt               const interrupt);

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

  virtual void registerISR(uint8_t            const int_num,
                           interface::ISRFunc       isr_func,
                           interface::ISRArg        isr_arg) override;

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
