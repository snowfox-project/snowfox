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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>

#include <spectre/util/BitManip.h>

#include <spectre/cpu/avr/io/ATMEGA328P.h>

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
  case toIntNum(Interrupt::EXTERNAL_INT0                 ): util::setBit(_EIMSK , INT0_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT1                 ): util::setBit(_EIMSK , INT1_bp  ); break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0               ): util::setBit(_PCICR , PCIE0_bp ); break;
  case toIntNum(Interrupt::PIN_CHANGE_INT1               ): util::setBit(_PCICR , PCIE1_bp ); break;
  case toIntNum(Interrupt::PIN_CHANGE_INT2               ): util::setBit(_PCICR , PCIE2_bp ); break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                ): util::setBit(_WDTCSR, WDIE_bp  ); break;
  case toIntNum(Interrupt::TIMER2_COMPARE_A              ): util::setBit(_TIMSK2, OCIE2A_bp); break;
  case toIntNum(Interrupt::TIMER2_COMPARE_B              ): util::setBit(_TIMSK2, OCIE2B_bp); break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW               ): util::setBit(_TIMSK2, TOIE2_bp ); break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                ): util::setBit(_TIMSK1, ICIE1_bp ); break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A              ): util::setBit(_TIMSK1, OCIE1A_bp); break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B              ): util::setBit(_TIMSK1, OCIE1B_bp); break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW               ): util::setBit(_TIMSK1, TOIE1_bp ); break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A              ): util::setBit(_TIMSK0, OCIE0A_bp); break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B              ): util::setBit(_TIMSK0, OCIE0B_bp); break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW               ): util::setBit(_TIMSK0, TOIE0_bp ); break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE  ): util::setBit(_SPCR  , SPIE_bp  ); break;
  case toIntNum(Interrupt::USART_RECEIVE_COMPLETE        ): util::setBit(_UCSR0B, RXCIE0_bp); break;
  case toIntNum(Interrupt::USART_UART_DATA_REGISTER_EMPTY): util::setBit(_UCSR0B, UDRIE0_bp); break;
  case toIntNum(Interrupt::USART_TRANSMIT_COMPLETE       ): util::setBit(_UCSR0B, TXCIE0_bp); break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER      ): util::setBit(_ADCSRA, ADIE_bp  ); break;
  case toIntNum(Interrupt::EEPROM_READY                  ): util::setBit(_EECR  , EERIE_bp ); break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR             ): util::setBit(_ACSR  , ACIE_bp  ); break;
  case toIntNum(Interrupt::TWO_WIRE_INT                  ): util::setBit(_TWCR  , TWIE_bp  ); break;
  case toIntNum(Interrupt::SPM_READY                     ): util::setBit(_SPMCSR, SPMIE_bp ); break;
#if defined(MCU_ARCH_avr) && defined(MCU_TYPE_atmega328p)
  case toIntNum(Interrupt::GLOBAL                        ): asm volatile("sei");    break;
#endif
  default                                                 : /* DO NOTHING */        break;
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case toIntNum(Interrupt::EXTERNAL_INT0                 ): util::clrBit(_EIMSK , INT0_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT1                 ): util::clrBit(_EIMSK , INT1_bp  ); break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0               ): util::clrBit(_PCICR , PCIE0_bp ); break;
  case toIntNum(Interrupt::PIN_CHANGE_INT1               ): util::clrBit(_PCICR , PCIE1_bp ); break;
  case toIntNum(Interrupt::PIN_CHANGE_INT2               ): util::clrBit(_PCICR , PCIE2_bp ); break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                ): util::clrBit(_WDTCSR, WDIE_bp  ); break;
  case toIntNum(Interrupt::TIMER2_COMPARE_A              ): util::clrBit(_TIMSK2, OCIE2A_bp); break;
  case toIntNum(Interrupt::TIMER2_COMPARE_B              ): util::clrBit(_TIMSK2, OCIE2B_bp); break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW               ): util::clrBit(_TIMSK2, TOIE2_bp ); break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                ): util::clrBit(_TIMSK1, ICIE1_bp ); break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A              ): util::clrBit(_TIMSK1, OCIE1A_bp); break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B              ): util::clrBit(_TIMSK1, OCIE1B_bp); break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW               ): util::clrBit(_TIMSK1, TOIE1_bp ); break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A              ): util::clrBit(_TIMSK0, OCIE0A_bp); break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B              ): util::clrBit(_TIMSK0, OCIE0B_bp); break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW               ): util::clrBit(_TIMSK0, TOIE0_bp ); break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE  ): util::clrBit(_SPCR  , SPIE_bp  ); break;
  case toIntNum(Interrupt::USART_RECEIVE_COMPLETE        ): util::clrBit(_UCSR0B, RXCIE0_bp); break;
  case toIntNum(Interrupt::USART_UART_DATA_REGISTER_EMPTY): util::clrBit(_UCSR0B, UDRIE0_bp); break;
  case toIntNum(Interrupt::USART_TRANSMIT_COMPLETE       ): util::clrBit(_UCSR0B, TXCIE0_bp); break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER      ): util::clrBit(_ADCSRA, ADIE_bp  ); break;
  case toIntNum(Interrupt::EEPROM_READY                  ): util::clrBit(_EECR  , EERIE_bp ); break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR             ): util::clrBit(_ACSR  , ACIE_bp  ); break;
  case toIntNum(Interrupt::TWO_WIRE_INT                  ): util::clrBit(_TWCR  , TWIE_bp  ); break;
  case toIntNum(Interrupt::SPM_READY                     ): util::clrBit(_SPMCSR, SPMIE_bp ); break;
#if defined(MCU_ARCH_avr) && defined(MCU_TYPE_atmega328p)
  case toIntNum(Interrupt::GLOBAL                        ): asm volatile("cli");     break;
#endif
  default                                                 : /* DO NOTHING */         break;
  }
}

void InterruptController::registerInterruptCallback(uint8_t const int_num, interface::InterruptCallback * interrupt_callback)
{
  switch(int_num)
  {
  case toIntNum(Interrupt::EXTERNAL_INT0                 ) : isr_external_int0                  = interrupt_callback; break;
  case toIntNum(Interrupt::EXTERNAL_INT1                 ) : isr_external_int1                  = interrupt_callback; break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0               ) : isr_pin_change_int0                = interrupt_callback; break;
  case toIntNum(Interrupt::PIN_CHANGE_INT1               ) : isr_pin_change_int1                = interrupt_callback; break;
  case toIntNum(Interrupt::PIN_CHANGE_INT2               ) : isr_pin_change_int2                = interrupt_callback; break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                ) : isr_watchdog_timer                 = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER2_COMPARE_A              ) : isr_timer2_compare_a               = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER2_COMPARE_B              ) : isr_timer2_compare_b               = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW               ) : isr_timer2_overflow                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                ) : isr_timer1_capture                 = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A              ) : isr_timer1_compare_a               = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B              ) : isr_timer1_compare_b               = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW               ) : isr_timer1_overflow                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A              ) : isr_timer0_compare_a               = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B              ) : isr_timer0_compare_b               = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW               ) : isr_timer0_overflow                = interrupt_callback; break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE  ) : isr_spi_serial_transfer_complete   = interrupt_callback; break;
  case toIntNum(Interrupt::USART_RECEIVE_COMPLETE        ) : isr_usart_receive_complete         = interrupt_callback; break;
  case toIntNum(Interrupt::USART_UART_DATA_REGISTER_EMPTY) : isr_usart_uart_data_register_empty = interrupt_callback; break;
  case toIntNum(Interrupt::USART_TRANSMIT_COMPLETE       ) : isr_usart_transmit_complete        = interrupt_callback; break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER      ) : isr_analog_digital_converter       = interrupt_callback; break;
  case toIntNum(Interrupt::EEPROM_READY                  ) : isr_eeprom_ready                   = interrupt_callback; break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR             ) : isr_analog_comparator              = interrupt_callback; break;
  case toIntNum(Interrupt::TWO_WIRE_INT                  ) : isr_two_wire_int                   = interrupt_callback; break;
  case toIntNum(Interrupt::SPM_READY                     ) : isr_spm_ready                      = interrupt_callback; break;
  default                                                  : /* DO NOTHING */                                         break;
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
  executeCallbackIfValid(isr_external_int0);
}

ISR(INT1_vect)
{
  executeCallbackIfValid(isr_external_int1);
}

ISR(PCINT0_vect)
{
  executeCallbackIfValid(isr_pin_change_int0);
}

ISR(PCINT1_vect)
{
  executeCallbackIfValid(isr_pin_change_int1);
}

ISR(PCINT2_vect)
{
  executeCallbackIfValid(isr_pin_change_int2);
}

ISR(WDT_vect)
{
  executeCallbackIfValid(isr_watchdog_timer);
}

ISR(TIMER2_COMPA_vect)
{
  executeCallbackIfValid(isr_timer2_compare_a);
}

ISR(TIMER2_COMPB_vect)
{
  executeCallbackIfValid(isr_timer2_compare_b);
}

ISR(TIMER2_OVF_vect)
{
  executeCallbackIfValid(isr_timer2_overflow);
}

ISR(TIMER1_CAPT_vect)
{
  executeCallbackIfValid(isr_timer1_capture);
}

ISR(TIMER1_COMPA_vect)
{
  executeCallbackIfValid(isr_timer1_compare_a);
}

ISR(TIMER1_COMPB_vect)
{
  executeCallbackIfValid(isr_timer1_compare_b);
}

ISR(TIMER1_OVF_vect)
{
  executeCallbackIfValid(isr_timer1_overflow);
}

ISR(TIMER0_COMPA_vect)
{
  executeCallbackIfValid(isr_timer0_compare_a);
}

ISR(TIMER0_COMPB_vect)
{
  executeCallbackIfValid(isr_timer0_compare_b);
}

ISR(TIMER0_OVF_vect)
{
  executeCallbackIfValid(isr_timer0_overflow);
}

ISR(SPI_STC_vect)
{
  executeCallbackIfValid(isr_spi_serial_transfer_complete);
}

ISR(USART_RX_vect)
{
  executeCallbackIfValid(isr_usart_receive_complete);
}

ISR(USART_UDRE_vect)
{
  executeCallbackIfValid(isr_usart_uart_data_register_empty);
}

ISR(USART_TX_vect)
{
  executeCallbackIfValid(isr_usart_transmit_complete);
}

ISR(ADC_vect)
{
  executeCallbackIfValid(isr_analog_digital_converter);
}

ISR(EE_READY_vect)
{
  executeCallbackIfValid(isr_eeprom_ready);
}

ISR(ANALOG_COMP_vect)
{
  executeCallbackIfValid(isr_analog_comparator);
}

ISR(TWI_vect)
{
  executeCallbackIfValid(isr_two_wire_int);
}

ISR(SPM_READY_vect)
{
  executeCallbackIfValid(isr_spm_ready);
}

#endif /* defined(MCU_ARCH_avr) && defined(MCU_TYPE_atmega328p) */
