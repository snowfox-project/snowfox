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

#ifndef INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_INTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_INTERRUPTCONTROLLER_H_


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

namespace AT90CAN128
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

enum class Interrupt : uint8_t
{
  EXTERNAL_INT0,
  EXTERNAL_INT1,
  EXTERNAL_INT2,
  EXTERNAL_INT3,
  EXTERNAL_INT4,
  EXTERNAL_INT5,
  EXTERNAL_INT6,
  EXTERNAL_INT7,
  TIMER2_COMPARE,
  TIMER2_OVERFLOW,
  TIMER1_CAPTURE,
  TIMER1_COMPARE_A,
  TIMER1_COMPARE_B,
  TIMER1_COMPARE_C,
  TIMER1_OVERFLOW,
  TIMER0_COMPARE,
  TIMER0_OVERFLOW,
  CAN_ALL,
  CAN_BUS_OFF,
  CAN_RECEIVE,
  CAN_TRANSMIT,
  CAN_FRAME_BUFFER,
  CAN_GENERAL_ERROR,
  CAN_TIMER_OVERRUN,
  SPI_SERIAL_TRANSFER_COMPLETE,
  USART0_RECEIVE_COMPLETE,
  USART0_UART_DATA_REGISTER_EMPTY,
  USART0_TRANSMIT_COMPLETE,
  ANALOG_COMPARATOR,
  ANALOG_DIGITAL_CONVERTER,
  EEPROM_READY,
  TIMER3_CAPTURE,
  TIMER3_COMPARE_A,
  TIMER3_COMPARE_B,
  TIMER3_COMPARE_C,
  TIMER3_OVERFLOW,
  USART1_RECEIVE_COMPLETE,
  USART1_UART_DATA_REGISTER_EMPTY,
  USART1_TRANSMIT_COMPLETE,
  TWO_WIRE_INT,
  SPM_READY,
  GLOBAL
};

enum class InterruptServiceRoutine : uint8_t
{
  EXTERNAL_INT0,
  EXTERNAL_INT1,
  EXTERNAL_INT2,
  EXTERNAL_INT3,
  EXTERNAL_INT4,
  EXTERNAL_INT5,
  EXTERNAL_INT6,
  EXTERNAL_INT7,
  TIMER2_COMPARE,
  TIMER2_OVERFLOW,
  TIMER1_CAPTURE,
  TIMER1_COMPARE_A,
  TIMER1_COMPARE_B,
  TIMER1_COMPARE_C,
  TIMER1_OVERFLOW,
  TIMER0_COMPARE,
  TIMER0_OVERFLOW,
  CAN_ALL,
  CAN_TIMER_OVERRUN,
  SPI_SERIAL_TRANSFER_COMPLETE,
  USART0_RECEIVE_COMPLETE,
  USART0_UART_DATA_REGISTER_EMPTY,
  USART0_TRANSMIT_COMPLETE,
  ANALOG_COMPARATOR,
  ANALOG_DIGITAL_CONVERTER,
  EEPROM_READY,
  TIMER3_CAPTURE,
  TIMER3_COMPARE_A,
  TIMER3_COMPARE_B,
  TIMER3_COMPARE_C,
  TIMER3_OVERFLOW,
  USART1_RECEIVE_COMPLETE,
  USART1_UART_DATA_REGISTER_EMPTY,
  USART1_TRANSMIT_COMPLETE,
  TWO_WIRE_INT,
  SPM_READY
};

/**************************************************************************************
 * PROTOTYPES
 **************************************************************************************/

uint8_t toIntNum(Interrupt               const interrupt                );
uint8_t toIsrNum(InterruptServiceRoutine const interrupt_service_routine);

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class InterruptController : public interface::InterruptController,
                            public interface::InterruptControllerAssembly
{

public:

           InterruptController(volatile uint8_t * eimsk,
                               volatile uint8_t * timsk2,
                               volatile uint8_t * timsk1,
                               volatile uint8_t * timsk0,
                               volatile uint8_t * cangie,
                               volatile uint8_t * spcr,
                               volatile uint8_t * ucsr0b,
                               volatile uint8_t * acsr,
                               volatile uint8_t * adcsra,
                               volatile uint8_t * eecr,
                               volatile uint8_t * timsk3,
                               volatile uint8_t * ucsr1b,
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
                   * _TIMSK2,
                   * _TIMSK1,
                   * _TIMSK0,
                   * _CANGIE,
                   * _SPCR,
                   * _UCSR0B,
                   * _ACSR,
                   * _ADCSRA,
                   * _EECR,
                   * _TIMSK3,
                   * _UCSR1B,
                   * _TWCR,
                   * _SPMCSR;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN128 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_INTERRUPTCONTROLLER_H_ */
