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

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>

#include <assert.h>

/* Required for 'assert' which in turn needs 'abort' in avr-gcc */
#if defined(MCU_ARCH_avr)
  #include <stdlib.h> 
#endif

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
 * DEFINES
 **************************************************************************************/

/* EIMSK */
#define INT0_bm   (1<<0)
#define INT1_bm   (1<<1)

/* PCICR */
#define PCIE0_bm  (1<<0)
#define PCIE1_bm  (1<<1)
#define PCIE2_bm  (1<<2)

/* WDTCSR */
#define WDIE_bm   (1<<6)

/* TIMSK2 */
#define TOIE2_bm  (1<<0)
#define OCIE2A_bm (1<<1)
#define OCIE2B_bm (1<<2)

/* TIMSK1 */
#define TOIE1_bm  (1<<0)
#define OCIE1A_bm (1<<1)
#define OCIE1B_bm (1<<2)
#define ICIE1_bm  (1<<5)

/* TIMSK0 */
#define TOIE0_bm  (1<<0)
#define OCIE0A_bm (1<<1)
#define OCIE0B_bm (1<<2)

/* SPCR */
#define SPIE_bm   (1<<7)

/* UCSR0B */
#define UDRIE0_bm (1<<5)
#define TXCIE0_bm (1<<6)
#define RXCIE0_bm (1<<7)

/* ADCSRA */
#define ADIE_bm   (1<<3)

/* EECR */
#define EERIE_bm  (1<<3)

/* ACSR */
#define ACIE_bm   (1<<3)

/* TWCR */
#define TWIE_bm   (1<<0)

/* SPMCSR */
#define SPMIE_bm  (1<<7)

/* INTERRUPT NUMBERS */
#define INT_EXTERNAL_INT0                    0
#define INT_EXTERNAL_INT1                    1
#define INT_PIN_CHANGE_INT0                  2
#define INT_PIN_CHANGE_INT1                  3
#define INT_PIN_CHANGE_INT2                  4
#define INT_WATCHDOG_TIMER                   5
#define INT_TIMER2_COMPARE_A                 6
#define INT_TIMER2_COMPARE_B                 7
#define INT_TIMER2_OVERFLOW                  8
#define INT_TIMER1_CAPTURE                   9
#define INT_TIMER1_COMPARE_A                10
#define INT_TIMER1_COMPARE_B                11
#define INT_TIMER1_OVERFLOW                 12
#define INT_TIMER0_COMPARE_A                13
#define INT_TIMER0_COMPARE_B                14
#define INT_TIMER0_OVERFLOW                 15
#define INT_SPI_SERIAL_TRANSFER_COMPLETE    16
#define INT_USART_RECEIVE_COMPLETE          17
#define INT_USART_UART_DATA_REGISTER_EMPTY  18
#define INT_USART_TRANSMIT_COMPLETE         19
#define INT_ANALOG_DIGITAL_CONVERTER        20
#define INT_EEPROM_READY                    21
#define INT_ANALOG_COMPARATOR               22
#define INT_TWO_WIRE_INT                    23
#define INT_SPM_READY                       24
#define INT_GLOBAL                          25
#define INT_INVALID                         255

/* INTERRUPT SERVICE ROUTINE NUMBERS */
#define ISR_EXTERNAL_INT0                    0
#define ISR_EXTERNAL_INT1                    1
#define ISR_PIN_CHANGE_INT0                  2
#define ISR_PIN_CHANGE_INT1                  3
#define ISR_PIN_CHANGE_INT2                  4
#define ISR_WATCHDOG_TIMER                   5
#define ISR_TIMER2_COMPARE_A                 6
#define ISR_TIMER2_COMPARE_B                 7
#define ISR_TIMER2_OVERFLOW                  8
#define ISR_TIMER1_CAPTURE                   9
#define ISR_TIMER1_COMPARE_A                10
#define ISR_TIMER1_COMPARE_B                11
#define ISR_TIMER1_OVERFLOW                 12
#define ISR_TIMER0_COMPARE_A                13
#define ISR_TIMER0_COMPARE_B                14
#define ISR_TIMER0_OVERFLOW                 15
#define ISR_SPI_SERIAL_TRANSFER_COMPLETE    16
#define ISR_USART_RECEIVE_COMPLETE          17
#define ISR_USART_UART_DATA_REGISTER_EMPTY  18
#define ISR_USART_TRANSMIT_COMPLETE         19
#define ISR_ANALOG_DIGITAL_CONVERTER        20
#define ISR_EEPROM_READY                    21
#define ISR_ANALOG_COMPARATOR               22
#define ISR_TWO_WIRE_INT                    23
#define ISR_SPM_READY                       24
#define ISR_INVALID                         255

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

static interface::InterruptCallback * isr_external_int0                  = 0,
                                    * isr_external_int1                  = 0,
                                    * isr_pin_change_int0                = 0,
                                    * isr_pin_change_int1                = 0,
                                    * isr_pin_change_int2                = 0,
                                    * isr_watchdog_timer                 = 0,
                                    * isr_timer2_compare_a               = 0,
                                    * isr_timer2_compare_b               = 0,
                                    * isr_timer2_overflow                = 0,
                                    * isr_timer1_capture                 = 0,
                                    * isr_timer1_compare_a               = 0,
                                    * isr_timer1_compare_b               = 0,
                                    * isr_timer1_overflow                = 0,
                                    * isr_timer0_compare_a               = 0,
                                    * isr_timer0_compare_b               = 0,
                                    * isr_timer0_overflow                = 0,
                                    * isr_spi_serial_transfer_complete   = 0,
                                    * isr_usart_receive_complete         = 0,
                                    * isr_usart_uart_data_register_empty = 0,
                                    * isr_usart_transmit_complete        = 0,
                                    * isr_analog_digital_converter       = 0,
                                    * isr_eeprom_ready                   = 0,
                                    * isr_analog_comparator              = 0,
                                    * isr_two_wire_int                   = 0,
                                    * isr_spm_ready                      = 0;

/**************************************************************************************
 * GLOBAL FUNCTIONS
 **************************************************************************************/

uint8_t toIntNum(Interrupt const interrupt)
{
  switch(interrupt)
  {
  case Interrupt::EXTERNAL_INT0                  : return INT_EXTERNAL_INT0;                  break;
  case Interrupt::EXTERNAL_INT1                  : return INT_EXTERNAL_INT1;                  break;
  case Interrupt::PIN_CHANGE_INT0                : return INT_PIN_CHANGE_INT0;                break;
  case Interrupt::PIN_CHANGE_INT1                : return INT_PIN_CHANGE_INT1;                break;
  case Interrupt::PIN_CHANGE_INT2                : return INT_PIN_CHANGE_INT2;                break;
  case Interrupt::WATCHDOG_TIMER                 : return INT_WATCHDOG_TIMER;                 break;
  case Interrupt::TIMER2_COMPARE_A               : return INT_TIMER2_COMPARE_A;               break;
  case Interrupt::TIMER2_COMPARE_B               : return INT_TIMER2_COMPARE_B;               break;
  case Interrupt::TIMER2_OVERFLOW                : return INT_TIMER2_OVERFLOW;                break;
  case Interrupt::TIMER1_CAPTURE                 : return INT_TIMER1_CAPTURE;                 break;
  case Interrupt::TIMER1_COMPARE_A               : return INT_TIMER1_COMPARE_A;               break;
  case Interrupt::TIMER1_COMPARE_B               : return INT_TIMER1_COMPARE_B;               break;
  case Interrupt::TIMER1_OVERFLOW                : return INT_TIMER1_OVERFLOW;                break;
  case Interrupt::TIMER0_COMPARE_A               : return INT_TIMER0_COMPARE_A;               break;
  case Interrupt::TIMER0_COMPARE_B               : return INT_TIMER0_COMPARE_B;               break;
  case Interrupt::TIMER0_OVERFLOW                : return INT_TIMER0_OVERFLOW;                break;
  case Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   : return INT_SPI_SERIAL_TRANSFER_COMPLETE;   break;
  case Interrupt::USART_RECEIVE_COMPLETE         : return INT_USART_RECEIVE_COMPLETE;         break;
  case Interrupt::USART_UART_DATA_REGISTER_EMPTY : return INT_USART_UART_DATA_REGISTER_EMPTY; break;
  case Interrupt::USART_TRANSMIT_COMPLETE        : return INT_USART_TRANSMIT_COMPLETE;        break;
  case Interrupt::ANALOG_DIGITAL_CONVERTER       : return INT_ANALOG_DIGITAL_CONVERTER;       break;
  case Interrupt::EEPROM_READY                   : return INT_EEPROM_READY;                   break;
  case Interrupt::ANALOG_COMPARATOR              : return INT_ANALOG_COMPARATOR;              break;
  case Interrupt::TWO_WIRE_INT                   : return INT_TWO_WIRE_INT;                   break;
  case Interrupt::SPM_READY                      : return INT_SPM_READY;                      break;
  case Interrupt::GLOBAL                         : return INT_GLOBAL;                         break;
  default                                        : return INT_INVALID;                        break;
  }
}

uint8_t toIsrNum(InterruptServiceRoutine const interrupt_service_routine)
{
  switch(interrupt_service_routine)
  {
  case InterruptServiceRoutine::EXTERNAL_INT0                  : return ISR_EXTERNAL_INT0;                  break;
  case InterruptServiceRoutine::EXTERNAL_INT1                  : return ISR_EXTERNAL_INT1;                  break;
  case InterruptServiceRoutine::PIN_CHANGE_INT0                : return ISR_PIN_CHANGE_INT0;                break;
  case InterruptServiceRoutine::PIN_CHANGE_INT1                : return ISR_PIN_CHANGE_INT1;                break;
  case InterruptServiceRoutine::PIN_CHANGE_INT2                : return ISR_PIN_CHANGE_INT2;                break;
  case InterruptServiceRoutine::WATCHDOG_TIMER                 : return ISR_WATCHDOG_TIMER;                 break;
  case InterruptServiceRoutine::TIMER2_COMPARE_A               : return ISR_TIMER2_COMPARE_A;               break;
  case InterruptServiceRoutine::TIMER2_COMPARE_B               : return ISR_TIMER2_COMPARE_B;               break;
  case InterruptServiceRoutine::TIMER2_OVERFLOW                : return ISR_TIMER2_OVERFLOW;                break;
  case InterruptServiceRoutine::TIMER1_CAPTURE                 : return ISR_TIMER1_CAPTURE;                 break;
  case InterruptServiceRoutine::TIMER1_COMPARE_A               : return ISR_TIMER1_COMPARE_A;               break;
  case InterruptServiceRoutine::TIMER1_COMPARE_B               : return ISR_TIMER1_COMPARE_B;               break;
  case InterruptServiceRoutine::TIMER1_OVERFLOW                : return ISR_TIMER1_OVERFLOW;                break;
  case InterruptServiceRoutine::TIMER0_COMPARE_A               : return ISR_TIMER0_COMPARE_A;               break;
  case InterruptServiceRoutine::TIMER0_COMPARE_B               : return ISR_TIMER0_COMPARE_B;               break;
  case InterruptServiceRoutine::TIMER0_OVERFLOW                : return ISR_TIMER0_OVERFLOW;                break;
  case InterruptServiceRoutine::SPI_SERIAL_TRANSFER_COMPLETE   : return ISR_SPI_SERIAL_TRANSFER_COMPLETE;   break;
  case InterruptServiceRoutine::USART_RECEIVE_COMPLETE         : return ISR_USART_RECEIVE_COMPLETE;         break;
  case InterruptServiceRoutine::USART_UART_DATA_REGISTER_EMPTY : return ISR_USART_UART_DATA_REGISTER_EMPTY; break;
  case InterruptServiceRoutine::USART_TRANSMIT_COMPLETE        : return ISR_USART_TRANSMIT_COMPLETE;        break;
  case InterruptServiceRoutine::ANALOG_DIGITAL_CONVERTER       : return ISR_ANALOG_DIGITAL_CONVERTER;       break;
  case InterruptServiceRoutine::EEPROM_READY                   : return ISR_EEPROM_READY;                   break;
  case InterruptServiceRoutine::ANALOG_COMPARATOR              : return ISR_ANALOG_COMPARATOR;              break;
  case InterruptServiceRoutine::TWO_WIRE_INT                   : return ISR_TWO_WIRE_INT;                   break;
  case InterruptServiceRoutine::SPM_READY                      : return ISR_SPM_READY;                      break;
  default                                                      : return ISR_INVALID;                        break;
  }
}

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

InterruptController::InterruptController(volatile uint8_t * eimsk,
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
                                         volatile uint8_t * spmcsr)
: _EIMSK  (eimsk ),
  _PCICR  (pcicr ),
  _WDTCSR (wdtcsr),
  _TIMSK2 (timsk2),
  _TIMSK1 (timsk1),
  _TIMSK0 (timsk0),
  _SPCR   (spcr  ),
  _UCSR0B (ucsr0b),
  _ADCSRA (adcsra),
  _EECR   (eecr  ),
  _ACSR   (acsr  ),
  _TWCR   (twcr  ),
  _SPMCSR (spmcsr)
{

}

InterruptController::~InterruptController()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void InterruptController::enableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case INT_EXTERNAL_INT0                  : *_EIMSK   |= INT0_bm;   break;
  case INT_EXTERNAL_INT1                  : *_EIMSK   |= INT1_bm;   break;
  case INT_PIN_CHANGE_INT0                : *_PCICR   |= PCIE0_bm;  break;
  case INT_PIN_CHANGE_INT1                : *_PCICR   |= PCIE1_bm;  break;
  case INT_PIN_CHANGE_INT2                : *_PCICR   |= PCIE2_bm;  break;
  case INT_WATCHDOG_TIMER                 : *_WDTCSR  |= WDIE_bm;   break;
  case INT_TIMER2_COMPARE_A               : *_TIMSK2  |= OCIE2A_bm; break;
  case INT_TIMER2_COMPARE_B               : *_TIMSK2  |= OCIE2B_bm; break;
  case INT_TIMER2_OVERFLOW                : *_TIMSK2  |= TOIE2_bm;  break;
  case INT_TIMER1_CAPTURE                 : *_TIMSK1  |= ICIE1_bm;  break;
  case INT_TIMER1_COMPARE_A               : *_TIMSK1  |= OCIE1A_bm; break;
  case INT_TIMER1_COMPARE_B               : *_TIMSK1  |= OCIE1B_bm; break;
  case INT_TIMER1_OVERFLOW                : *_TIMSK1  |= TOIE1_bm;  break;
  case INT_TIMER0_COMPARE_A               : *_TIMSK0  |= OCIE0A_bm; break;
  case INT_TIMER0_COMPARE_B               : *_TIMSK0  |= OCIE0B_bm; break;
  case INT_TIMER0_OVERFLOW                : *_TIMSK0  |= TOIE0_bm;  break;
  case INT_SPI_SERIAL_TRANSFER_COMPLETE   : *_SPCR    |= SPIE_bm;   break;
  case INT_USART_RECEIVE_COMPLETE         : *_UCSR0B  |= RXCIE0_bm; break;
  case INT_USART_UART_DATA_REGISTER_EMPTY : *_UCSR0B  |= UDRIE0_bm; break;
  case INT_USART_TRANSMIT_COMPLETE        : *_UCSR0B  |= TXCIE0_bm; break;
  case INT_ANALOG_DIGITAL_CONVERTER       : *_ADCSRA  |= ADIE_bm;   break;
  case INT_EEPROM_READY                   : *_EECR    |= EERIE_bm;  break;
  case INT_ANALOG_COMPARATOR              : *_ACSR    |= ACIE_bm;   break;
  case INT_TWO_WIRE_INT                   : *_TWCR    |= TWIE_bm;   break;
  case INT_SPM_READY                      : *_SPMCSR  |= SPMIE_bm;  break;
#if defined(MCU_ARCH_avr) && defined(MCU_TYPE_atmega328p)
  case INT_GLOBAL                         : asm volatile("sei");    break;
#endif
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case INT_EXTERNAL_INT0                  : *_EIMSK   &= ~INT0_bm;   break;
  case INT_EXTERNAL_INT1                  : *_EIMSK   &= ~INT1_bm;   break;
  case INT_PIN_CHANGE_INT0                : *_PCICR   &= ~PCIE0_bm;  break;
  case INT_PIN_CHANGE_INT1                : *_PCICR   &= ~PCIE1_bm;  break;
  case INT_PIN_CHANGE_INT2                : *_PCICR   &= ~PCIE2_bm;  break;
  case INT_WATCHDOG_TIMER                 : *_WDTCSR  &= ~WDIE_bm;   break;
  case INT_TIMER2_COMPARE_A               : *_TIMSK2  &= ~OCIE2A_bm; break;
  case INT_TIMER2_COMPARE_B               : *_TIMSK2  &= ~OCIE2B_bm; break;
  case INT_TIMER2_OVERFLOW                : *_TIMSK2  &= ~TOIE2_bm;  break;
  case INT_TIMER1_CAPTURE                 : *_TIMSK1  &= ~ICIE1_bm;  break;
  case INT_TIMER1_COMPARE_A               : *_TIMSK1  &= ~OCIE1A_bm; break;
  case INT_TIMER1_COMPARE_B               : *_TIMSK1  &= ~OCIE1B_bm; break;
  case INT_TIMER1_OVERFLOW                : *_TIMSK1  &= ~TOIE1_bm;  break;
  case INT_TIMER0_COMPARE_A               : *_TIMSK0  &= ~OCIE0A_bm; break;
  case INT_TIMER0_COMPARE_B               : *_TIMSK0  &= ~OCIE0B_bm; break;
  case INT_TIMER0_OVERFLOW                : *_TIMSK0  &= ~TOIE0_bm;  break;
  case INT_SPI_SERIAL_TRANSFER_COMPLETE   : *_SPCR    &= ~SPIE_bm;   break;
  case INT_USART_RECEIVE_COMPLETE         : *_UCSR0B  &= ~RXCIE0_bm; break;
  case INT_USART_UART_DATA_REGISTER_EMPTY : *_UCSR0B  &= ~UDRIE0_bm; break;
  case INT_USART_TRANSMIT_COMPLETE        : *_UCSR0B  &= ~TXCIE0_bm; break;
  case INT_ANALOG_DIGITAL_CONVERTER       : *_ADCSRA  &= ~ADIE_bm;   break;
  case INT_EEPROM_READY                   : *_EECR    &= ~EERIE_bm;  break;
  case INT_ANALOG_COMPARATOR              : *_ACSR    &= ~ACIE_bm;   break;
  case INT_TWO_WIRE_INT                   : *_TWCR    &= ~TWIE_bm;   break;
  case INT_SPM_READY                      : *_SPMCSR  &= ~SPMIE_bm;  break;
#if defined(MCU_ARCH_avr) && defined(MCU_TYPE_atmega328p)
  case INT_GLOBAL                         : asm volatile("cli");     break;
#endif
  }
}

void InterruptController::registerInterruptCallback(uint8_t const isr_num, interface::InterruptCallback * interrupt_callback)
{
  switch(isr_num)
  {
  case ISR_EXTERNAL_INT0                  : isr_external_int0                  = interrupt_callback; break;
  case ISR_EXTERNAL_INT1                  : isr_external_int1                  = interrupt_callback; break;
  case ISR_PIN_CHANGE_INT0                : isr_pin_change_int0                = interrupt_callback; break;
  case ISR_PIN_CHANGE_INT1                : isr_pin_change_int1                = interrupt_callback; break;
  case ISR_PIN_CHANGE_INT2                : isr_pin_change_int1                = interrupt_callback; break;
  case ISR_WATCHDOG_TIMER                 : isr_watchdog_timer                 = interrupt_callback; break;
  case ISR_TIMER2_COMPARE_A               : isr_timer2_compare_a               = interrupt_callback; break;
  case ISR_TIMER2_COMPARE_B               : isr_timer2_compare_b               = interrupt_callback; break;
  case ISR_TIMER2_OVERFLOW                : isr_timer2_overflow                = interrupt_callback; break;
  case ISR_TIMER1_CAPTURE                 : isr_timer1_capture                 = interrupt_callback; break;
  case ISR_TIMER1_COMPARE_A               : isr_timer1_compare_a               = interrupt_callback; break;
  case ISR_TIMER1_COMPARE_B               : isr_timer1_compare_b               = interrupt_callback; break;
  case ISR_TIMER1_OVERFLOW                : isr_timer1_overflow                = interrupt_callback; break;
  case ISR_TIMER0_COMPARE_A               : isr_timer0_compare_a               = interrupt_callback; break;
  case ISR_TIMER0_COMPARE_B               : isr_timer0_compare_b               = interrupt_callback; break;
  case ISR_TIMER0_OVERFLOW                : isr_timer0_overflow                = interrupt_callback; break;
  case ISR_SPI_SERIAL_TRANSFER_COMPLETE   : isr_spi_serial_transfer_complete   = interrupt_callback; break;
  case ISR_USART_RECEIVE_COMPLETE         : isr_usart_receive_complete         = interrupt_callback; break;
  case ISR_USART_UART_DATA_REGISTER_EMPTY : isr_usart_uart_data_register_empty = interrupt_callback; break;
  case ISR_USART_TRANSMIT_COMPLETE        : isr_usart_transmit_complete        = interrupt_callback; break;
  case ISR_ANALOG_DIGITAL_CONVERTER       : isr_analog_digital_converter       = interrupt_callback; break;
  case ISR_EEPROM_READY                   : isr_eeprom_ready                   = interrupt_callback; break;
  case ISR_ANALOG_COMPARATOR              : isr_analog_comparator              = interrupt_callback; break;
  case ISR_TWO_WIRE_INT                   : isr_two_wire_int                   = interrupt_callback; break;
  case ISR_SPM_READY                      : isr_spm_ready                      = interrupt_callback; break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* spectre */

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

#if defined(MCU_ARCH_avr) && defined(MCU_TYPE_atmega328p)

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre::hal::ATMEGA328P;

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

ISR(INT0_vect)
{
  if(isr_external_int0) isr_external_int0->interruptServiceRoutine();
}

ISR(INT1_vect)
{
  if(isr_external_int1) isr_external_int1->interruptServiceRoutine();
}

ISR(PCINT0_vect)
{
  if(isr_pin_change_int0) isr_pin_change_int0->interruptServiceRoutine();
}

ISR(PCINT1_vect)
{
  if(isr_pin_change_int1) isr_pin_change_int1->interruptServiceRoutine();
}

ISR(PCINT2_vect)
{
  if(isr_pin_change_int2) isr_pin_change_int2->interruptServiceRoutine();
}

ISR(WDT_vect)
{
  if(isr_watchdog_timer) isr_watchdog_timer->interruptServiceRoutine();
}

ISR(TIMER2_COMPA_vect)
{
  if(isr_timer2_compare_a) isr_timer2_compare_a->interruptServiceRoutine();
}

ISR(TIMER2_COMPB_vect)
{
  if(isr_timer2_compare_b) isr_timer2_compare_b->interruptServiceRoutine();
}

ISR(TIMER2_OVF_vect)
{
  if(isr_timer2_overflow) isr_timer2_overflow->interruptServiceRoutine();
}

ISR(TIMER1_CAPT_vect)
{
  if(isr_timer1_capture) isr_timer1_capture->interruptServiceRoutine();
}

ISR(TIMER1_COMPA_vect)
{
  if(isr_timer1_compare_a) isr_timer1_compare_a->interruptServiceRoutine();
}

ISR(TIMER1_COMPB_vect)
{
  if(isr_timer1_compare_b) isr_timer1_compare_b->interruptServiceRoutine();
}

ISR(TIMER1_OVF_vect)
{
  if(isr_timer1_overflow) isr_timer1_overflow->interruptServiceRoutine();
}

ISR(TIMER0_COMPA_vect)
{
  if(isr_timer0_compare_a) isr_timer0_compare_a->interruptServiceRoutine();
}

ISR(TIMER0_COMPB_vect)
{
  if(isr_timer0_compare_b) isr_timer0_compare_b->interruptServiceRoutine();
}

ISR(TIMER0_OVF_vect)
{
  if(isr_timer0_overflow) isr_timer0_overflow->interruptServiceRoutine();
}

ISR(SPI_STC_vect)
{
  if(isr_spi_serial_transfer_complete) isr_spi_serial_transfer_complete->interruptServiceRoutine();
}

ISR(USART_RX_vect)
{
  if(isr_usart_receive_complete) isr_usart_receive_complete->interruptServiceRoutine();
}

ISR(USART_UDRE_vect)
{
  if(isr_usart_uart_data_register_empty) isr_usart_uart_data_register_empty->interruptServiceRoutine();
}

ISR(USART_TX_vect)
{
  if(isr_usart_transmit_complete) isr_usart_transmit_complete->interruptServiceRoutine();
}

ISR(ADC_vect)
{
  if(isr_analog_digital_converter) isr_analog_digital_converter->interruptServiceRoutine();
}

ISR(EE_READY_vect)
{
  if(isr_eeprom_ready) isr_eeprom_ready->interruptServiceRoutine();
}

ISR(ANALOG_COMP_vect)
{
  if(isr_analog_comparator) isr_analog_comparator->interruptServiceRoutine();
}

ISR(TWI_vect)
{
  if(isr_two_wire_int) isr_two_wire_int->interruptServiceRoutine();
}

ISR(SPM_READY_vect)
{
  if(isr_spm_ready) isr_spm_ready->interruptServiceRoutine();
}

#endif /* defined(MCU_ARCH_avr) && defined(MCU_TYPE_atmega328p) */
