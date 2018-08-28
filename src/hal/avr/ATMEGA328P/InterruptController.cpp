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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>

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
 * CTOR/DTOR
 **************************************************************************************/

InterruptController::InterruptController(volatile uint8_t * eimsk,
                                         volatile uint8_t * pcicr,
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
                                         volatile uint8_t * adcsra)
: _EIMSK  (eimsk ),
  _PCICR  (pcicr ),
  _WDTCSR (wdtcsr),
  _TIMSK0 (timsk0),
  _TIMSK1 (timsk1),
  _TIMSK2 (timsk2),
  _UCSR0B (ucsr0b),
  _SPCR   (spcr  ),
  _TWCR   (twcr  ),
  _EECR   (eecr  ),
  _SPMCSR (spmcsr),
  _ACSR   (acsr  ),
  _ADCSRA (adcsra)
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
  case toIntNum(Interrupt::EXTERNAL_INT0                 ): *_EIMSK   |= INT0_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT1                 ): *_EIMSK   |= INT1_bm;   break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0               ): *_PCICR   |= PCIE0_bm;  break;
  case toIntNum(Interrupt::PIN_CHANGE_INT1               ): *_PCICR   |= PCIE1_bm;  break;
  case toIntNum(Interrupt::PIN_CHANGE_INT2               ): *_PCICR   |= PCIE2_bm;  break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                ): *_WDTCSR  |= WDIE_bm;   break;
  case toIntNum(Interrupt::TIMER2_COMPARE_A              ): *_TIMSK2  |= OCIE2A_bm; break;
  case toIntNum(Interrupt::TIMER2_COMPARE_B              ): *_TIMSK2  |= OCIE2B_bm; break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW               ): *_TIMSK2  |= TOIE2_bm;  break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                ): *_TIMSK1  |= ICIE1_bm;  break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A              ): *_TIMSK1  |= OCIE1A_bm; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B              ): *_TIMSK1  |= OCIE1B_bm; break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW               ): *_TIMSK1  |= TOIE1_bm;  break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A              ): *_TIMSK0  |= OCIE0A_bm; break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B              ): *_TIMSK0  |= OCIE0B_bm; break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW               ): *_TIMSK0  |= TOIE0_bm;  break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE  ): *_SPCR    |= SPIE_bm;   break;
  case toIntNum(Interrupt::USART_RECEIVE_COMPLETE        ): *_UCSR0B  |= RXCIE0_bm; break;
  case toIntNum(Interrupt::USART_UART_DATA_REGISTER_EMPTY): *_UCSR0B  |= UDRIE0_bm; break;
  case toIntNum(Interrupt::USART_TRANSMIT_COMPLETE       ): *_UCSR0B  |= TXCIE0_bm; break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER      ): *_ADCSRA  |= ADIE_bm;   break;
  case toIntNum(Interrupt::EEPROM_READY                  ): *_EECR    |= EERIE_bm;  break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR             ): *_ACSR    |= ACIE_bm;   break;
  case toIntNum(Interrupt::TWO_WIRE_INT                  ): *_TWCR    |= TWIE_bm;   break;
  case toIntNum(Interrupt::SPM_READY                     ): *_SPMCSR  |= SPMIE_bm;  break;
#if defined(MCU_ARCH_avr) && defined(MCU_TYPE_atmega328p)
  case toIntNum(Interrupt::GLOBAL                        ): asm volatile("sei");    break;
#endif
  case toIntNum(Interrupt::INVALID                       ): /* DO NOTHING */        break;
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case toIntNum(Interrupt::EXTERNAL_INT0                 ): *_EIMSK   &= ~INT0_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT1                 ): *_EIMSK   &= ~INT1_bm;   break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0               ): *_PCICR   &= ~PCIE0_bm;  break;
  case toIntNum(Interrupt::PIN_CHANGE_INT1               ): *_PCICR   &= ~PCIE1_bm;  break;
  case toIntNum(Interrupt::PIN_CHANGE_INT2               ): *_PCICR   &= ~PCIE2_bm;  break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                ): *_WDTCSR  &= ~WDIE_bm;   break;
  case toIntNum(Interrupt::TIMER2_COMPARE_A              ): *_TIMSK2  &= ~OCIE2A_bm; break;
  case toIntNum(Interrupt::TIMER2_COMPARE_B              ): *_TIMSK2  &= ~OCIE2B_bm; break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW               ): *_TIMSK2  &= ~TOIE2_bm;  break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                ): *_TIMSK1  &= ~ICIE1_bm;  break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A              ): *_TIMSK1  &= ~OCIE1A_bm; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B              ): *_TIMSK1  &= ~OCIE1B_bm; break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW               ): *_TIMSK1  &= ~TOIE1_bm;  break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A              ): *_TIMSK0  &= ~OCIE0A_bm; break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B              ): *_TIMSK0  &= ~OCIE0B_bm; break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW               ): *_TIMSK0  &= ~TOIE0_bm;  break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE  ): *_SPCR    &= ~SPIE_bm;   break;
  case toIntNum(Interrupt::USART_RECEIVE_COMPLETE        ): *_UCSR0B  &= ~RXCIE0_bm; break;
  case toIntNum(Interrupt::USART_UART_DATA_REGISTER_EMPTY): *_UCSR0B  &= ~UDRIE0_bm; break;
  case toIntNum(Interrupt::USART_TRANSMIT_COMPLETE       ): *_UCSR0B  &= ~TXCIE0_bm; break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER      ): *_ADCSRA  &= ~ADIE_bm;   break;
  case toIntNum(Interrupt::EEPROM_READY                  ): *_EECR    &= ~EERIE_bm;  break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR             ): *_ACSR    &= ~ACIE_bm;   break;
  case toIntNum(Interrupt::TWO_WIRE_INT                  ): *_TWCR    &= ~TWIE_bm;   break;
  case toIntNum(Interrupt::SPM_READY                     ): *_SPMCSR  &= ~SPMIE_bm;  break;
#if defined(MCU_ARCH_avr) && defined(MCU_TYPE_atmega328p)
  case toIntNum(Interrupt::GLOBAL                        ): asm volatile("cli");     break;
#endif
  }
}

void InterruptController::registerInterruptCallback(uint8_t const isr_num, interface::InterruptCallback * interrupt_callback)
{
  switch(isr_num)
  {
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT0                 ) : isr_external_int0                  = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT1                 ) : isr_external_int1                  = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::PIN_CHANGE_INT0               ) : isr_pin_change_int0                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::PIN_CHANGE_INT1               ) : isr_pin_change_int1                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::PIN_CHANGE_INT2               ) : isr_pin_change_int2                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::WATCHDOG_TIMER                ) : isr_watchdog_timer                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER2_COMPARE_A              ) : isr_timer2_compare_a               = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER2_COMPARE_B              ) : isr_timer2_compare_b               = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER2_OVERFLOW               ) : isr_timer2_overflow                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_CAPTURE                ) : isr_timer1_capture                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_COMPARE_A              ) : isr_timer1_compare_a               = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_COMPARE_B              ) : isr_timer1_compare_b               = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_OVERFLOW               ) : isr_timer1_overflow                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER0_COMPARE_A              ) : isr_timer0_compare_a               = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER0_COMPARE_B              ) : isr_timer0_compare_b               = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER0_OVERFLOW               ) : isr_timer0_overflow                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::SPI_SERIAL_TRANSFER_COMPLETE  ) : isr_spi_serial_transfer_complete   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART_RECEIVE_COMPLETE        ) : isr_usart_receive_complete         = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART_UART_DATA_REGISTER_EMPTY) : isr_usart_uart_data_register_empty = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART_TRANSMIT_COMPLETE       ) : isr_usart_transmit_complete        = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::ANALOG_DIGITAL_CONVERTER      ) : isr_analog_digital_converter       = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EEPROM_READY                  ) : isr_eeprom_ready                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::ANALOG_COMPARATOR             ) : isr_analog_comparator              = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TWO_WIRE_INT                  ) : isr_two_wire_int                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::SPM_READY                     ) : isr_spm_ready                      = interrupt_callback; break;
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
 * INCLUDE
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
