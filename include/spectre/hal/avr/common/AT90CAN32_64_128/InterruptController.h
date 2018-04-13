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

#ifndef INCLUDE_SPECTRE_HAL_AVR_AT90CAN32_64_128_INTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_AT90CAN32_64_128_INTERRUPTCONTROLLER_H_

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

namespace AT90CAN32_64_128
{

/**************************************************************************************
 * TYPEDEFS
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
  TIMER2_COMPARE                  =  8,
  TIMER2_OVERFLOW                 =  9,
  TIMER1_CAPTURE                  = 10,
  TIMER1_COMPARE_A                = 11,
  TIMER1_COMPARE_B                = 12,
  TIMER1_COMPARE_C                = 13,
  TIMER1_OVERFLOW                 = 14,
  TIMER0_COMPARE                  = 15,
  TIMER0_OVERFLOW                 = 16,
  CAN_ALL                         = 17,
  CAN_BUS_OFF                     = 18,
  CAN_RECEIVE                     = 19,
  CAN_TRANSMIT                    = 20,
  CAN_FRAME_BUFFER                = 21,
  CAN_GENERAL_ERROR               = 22,
  CAN_TIMER_OVERRUN               = 23,
  SPI_SERIAL_TRANSFER_COMPLETE    = 24,
  USART0_RECEIVE_COMPLETE         = 25,
  USART0_UART_DATA_REGISTER_EMPTY = 26,
  USART0_TRANSMIT_COMPLETE        = 27,
  ANALOG_COMPARATOR               = 28,
  ANALOG_DIGITAL_CONVERTER        = 29,
  EEPROM_READY                    = 30,
  TIMER3_CAPTURE                  = 31,
  TIMER3_COMPARE_A                = 32,
  TIMER3_COMPARE_B                = 33,
  TIMER3_COMPARE_C                = 34,
  TIMER3_OVERFLOW                 = 35,
  USART1_RECEIVE_COMPLETE         = 36,
  USART1_UART_DATA_REGISTER_EMPTY = 37,
  USART1_TRANSMIT_COMPLETE        = 38,
  TWO_WIRE_INT                    = 39,
  SPM_READY                       = 40,
  GLOBAL                          = 41
};

enum class InterruptServiceRoutine : uint8_t
{
  EXTERNAL_INT0                   =  0,
  EXTERNAL_INT1                   =  1,
  EXTERNAL_INT2                   =  2,
  EXTERNAL_INT3                   =  3,
  EXTERNAL_INT4                   =  4,
  EXTERNAL_INT5                   =  5,
  EXTERNAL_INT6                   =  6,
  EXTERNAL_INT7                   =  7,
  TIMER2_COMPARE                  =  8,
  TIMER2_OVERFLOW                 =  9,
  TIMER1_CAPTURE                  = 10,
  TIMER1_COMPARE_A                = 11,
  TIMER1_COMPARE_B                = 12,
  TIMER1_COMPARE_C                = 13,
  TIMER1_OVERFLOW                 = 14,
  TIMER0_COMPARE                  = 15,
  TIMER0_OVERFLOW                 = 16,
  CAN_ALL                         = 17,
  CAN_TIMER_OVERRUN               = 18,
  SPI_SERIAL_TRANSFER_COMPLETE    = 19,
  USART0_RECEIVE_COMPLETE         = 20,
  USART0_UART_DATA_REGISTER_EMPTY = 21,
  USART0_TRANSMIT_COMPLETE        = 22,
  ANALOG_COMPARATOR               = 23,
  ANALOG_DIGITAL_CONVERTER        = 24,
  EEPROM_READY                    = 25,
  TIMER3_CAPTURE                  = 26,
  TIMER3_COMPARE_A                = 27,
  TIMER3_COMPARE_B                = 28,
  TIMER3_COMPARE_C                = 29,
  TIMER3_OVERFLOW                 = 30,
  USART1_RECEIVE_COMPLETE         = 31,
  USART1_UART_DATA_REGISTER_EMPTY = 32,
  USART1_TRANSMIT_COMPLETE        = 33,
  TWO_WIRE_INT                    = 34,
  SPM_READY                       = 35
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

} /* AT90CAN32_64_128 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_AT90CAN32_64_128_INTERRUPTCONTROLLER_H_ */
