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

#include <spectre/hal/avr/common/ATMEGA16U4_32U4/InterruptController.h>

#include <spectre/util/BitManip.h>

#include <spectre/cpu/avr/io/common/ATMEGA16U4_32U4.h>

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
 * GLOBAL VARIABLES
 **************************************************************************************/

static interface::InterruptCallback * isr_external_int0                   = 0,
                                    * isr_external_int1                   = 0,
                                    * isr_external_int2                   = 0,
                                    * isr_external_int3                   = 0,
                                    * isr_external_int6                   = 0,
                                    * isr_pin_change_int0                 = 0,
                                    * isr_usb_general                     = 0,
                                    * isr_usb_endpoint                    = 0,
                                    * isr_watchdog_timer                  = 0,
                                    * isr_timer1_capture                  = 0,
                                    * isr_timer1_compare_a                = 0,
                                    * isr_timer1_compare_b                = 0,
                                    * isr_timer1_compare_c                = 0,
                                    * isr_timer1_overflow                 = 0,
                                    * isr_timer0_compare_a                = 0,
                                    * isr_timer0_compare_b                = 0,
                                    * isr_timer0_overflow                 = 0,
                                    * isr_spi_serial_transfer_complete    = 0,
                                    * isr_usart1_receive_complete         = 0,
                                    * isr_usart1_uart_data_register_empty = 0,
                                    * isr_usart1_transmit_complete        = 0,
                                    * isr_analog_comparator               = 0,
                                    * isr_analog_digital_converter        = 0,
                                    * isr_eeprom_ready                    = 0,
                                    * isr_timer3_capture                  = 0,
                                    * isr_timer3_compare_a                = 0,
                                    * isr_timer3_compare_b                = 0,
                                    * isr_timer3_compare_c                = 0,
                                    * isr_timer3_overflow                 = 0,
                                    * isr_two_wire_int                    = 0,
                                    * isr_spm_ready                       = 0,
                                    * isr_timer4_compare_a                = 0,
                                    * isr_timer4_compare_b                = 0,
                                    * isr_timer4_compare_d                = 0,
                                    * isr_timer4_overflow                 = 0,
                                    * isr_timer4_fault_protection         = 0;

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

InterruptController::InterruptController(volatile uint8_t * eimsk,
                                         volatile uint8_t * pcicr,
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
                                         volatile uint8_t * adcsra)
: _EIMSK (eimsk ),
  _PCICR (pcicr ),
  _WDTCSR(wdtcsr),
  _TIMSK0(timsk0),
  _TIMSK1(timsk1),
  _TIMSK3(timsk3),
  _TIMSK4(timsk4),
  _TCCR4D(tccr4d),
  _UCSR1B(ucsr1b),
  _SPCR  (spcr  ),
  _TWCR  (twcr  ),
  _EECR  (eecr  ),
  _SPMCSR(spmcsr),
  _ACSR  (acsr  ),
  _ADCSRA(adcsra)
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
  case toIntNum(Interrupt::EXTERNAL_INT0                  ): util::setBit(_EIMSK , INT0_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT1                  ): util::setBit(_EIMSK , INT1_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT2                  ): util::setBit(_EIMSK , INT2_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT3                  ): util::setBit(_EIMSK , INT3_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT6                  ): util::setBit(_EIMSK , INT6_bp  ); break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0                ): util::setBit(_PCICR , PCIE0_bp ); break;
  case toIntNum(Interrupt::USB_GENERAL                    ): /* TODO */                        break;
  case toIntNum(Interrupt::USB_ENDPOINT                   ): /* TODO */                        break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                 ): util::setBit(_WDTCSR, WDIE_bp  ); break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                 ): util::setBit(_TIMSK1, ICIE1_bp ); break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A               ): util::setBit(_TIMSK1, OCIE1A_bp); break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B               ): util::setBit(_TIMSK1, OCIE1B_bp); break;
  case toIntNum(Interrupt::TIMER1_COMPARE_C               ): util::setBit(_TIMSK1, OCIE1C_bp); break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW                ): util::setBit(_TIMSK1, TOIE1_bp ); break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A               ): util::setBit(_TIMSK0, OCIE0A_bp); break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B               ): util::setBit(_TIMSK0, OCIE0B_bp); break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW                ): util::setBit(_TIMSK0, TOIE0_bp ); break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   ): util::setBit(_SPCR  , SPIE_bp  ); break;
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ): util::setBit(_UCSR1B, RXCIE1_bp); break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY): util::setBit(_UCSR1B, UDRIE1_bp); break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ): util::setBit(_UCSR1B, TXCIE1_bp); break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR              ): util::setBit(_ACSR  , ACIE_bp  ); break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER       ): util::setBit(_ADCSRA, ADIE_bp  ); break;
  case toIntNum(Interrupt::EEPROM_READY                   ): util::setBit(_EECR  , EERIE_bp ); break;
  case toIntNum(Interrupt::TIMER3_CAPTURE                 ): util::setBit(_TIMSK3, ICIE3_bp ); break;
  case toIntNum(Interrupt::TIMER3_COMPARE_A               ): util::setBit(_TIMSK3, OCIE3A_bp); break;
  case toIntNum(Interrupt::TIMER3_COMPARE_B               ): util::setBit(_TIMSK3, OCIE3B_bp); break;
  case toIntNum(Interrupt::TIMER3_COMPARE_C               ): util::setBit(_TIMSK3, OCIE3C_bp); break;
  case toIntNum(Interrupt::TIMER3_OVERFLOW                ): util::setBit(_TIMSK3, TOIE3_bp ); break;
  case toIntNum(Interrupt::TWO_WIRE_INT                   ): util::setBit(_TWCR  , TWIE_bp  ); break;
  case toIntNum(Interrupt::SPM_READY                      ): util::setBit(_SPMCSR, SPMIE_bp ); break;
  case toIntNum(Interrupt::TIMER4_COMPARE_A               ): util::setBit(_TIMSK4, OCIE4A_bp); break;
  case toIntNum(Interrupt::TIMER4_COMPARE_B               ): util::setBit(_TIMSK4, OCIE4B_bp); break;
  case toIntNum(Interrupt::TIMER4_COMPARE_D               ): util::setBit(_TIMSK4, OCIE4D_bp); break;
  case toIntNum(Interrupt::TIMER4_OVERFLOW                ): util::setBit(_TIMSK4, TOIE4_bp ); break;
  case toIntNum(Interrupt::TIMER4_FAULT_PROTECTION        ): util::setBit(_TCCR4D, FPIE4_bp ); break;
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                         ): asm volatile("sei");   break;
#endif
  default                                                  : /* DO NOTHING */       break;
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case toIntNum(Interrupt::EXTERNAL_INT0                  ): util::clrBit(_EIMSK , INT0_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT1                  ): util::clrBit(_EIMSK , INT1_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT2                  ): util::clrBit(_EIMSK , INT2_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT3                  ): util::clrBit(_EIMSK , INT3_bp  ); break;
  case toIntNum(Interrupt::EXTERNAL_INT6                  ): util::clrBit(_EIMSK , INT6_bp  ); break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0                ): util::clrBit(_PCICR , PCIE0_bp ); break;
  case toIntNum(Interrupt::USB_GENERAL                    ): /* TODO */                        break;
  case toIntNum(Interrupt::USB_ENDPOINT                   ): /* TODO */                        break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                 ): util::clrBit(_WDTCSR, WDIE_bp  ); break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                 ): util::clrBit(_TIMSK1, ICIE1_bp ); break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A               ): util::clrBit(_TIMSK1, OCIE1A_bp); break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B               ): util::clrBit(_TIMSK1, OCIE1B_bp); break;
  case toIntNum(Interrupt::TIMER1_COMPARE_C               ): util::clrBit(_TIMSK1, OCIE1C_bp); break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW                ): util::clrBit(_TIMSK1, TOIE1_bp ); break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A               ): util::clrBit(_TIMSK0, OCIE0A_bp); break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B               ): util::clrBit(_TIMSK0, OCIE0B_bp); break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW                ): util::clrBit(_TIMSK0, TOIE0_bp ); break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   ): util::clrBit(_SPCR  , SPIE_bp  ); break;
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ): util::clrBit(_UCSR1B, RXCIE1_bp); break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY): util::clrBit(_UCSR1B, UDRIE1_bp); break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ): util::clrBit(_UCSR1B, TXCIE1_bp); break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR              ): util::clrBit(_ACSR  , ACIE_bp  ); break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER       ): util::clrBit(_ADCSRA, ADIE_bp  ); break;
  case toIntNum(Interrupt::EEPROM_READY                   ): util::clrBit(_EECR  , EERIE_bp ); break;
  case toIntNum(Interrupt::TIMER3_CAPTURE                 ): util::clrBit(_TIMSK3, ICIE3_bp ); break;
  case toIntNum(Interrupt::TIMER3_COMPARE_A               ): util::clrBit(_TIMSK3, OCIE3A_bp); break;
  case toIntNum(Interrupt::TIMER3_COMPARE_B               ): util::clrBit(_TIMSK3, OCIE3B_bp); break;
  case toIntNum(Interrupt::TIMER3_COMPARE_C               ): util::clrBit(_TIMSK3, OCIE3C_bp); break;
  case toIntNum(Interrupt::TIMER3_OVERFLOW                ): util::clrBit(_TIMSK3, TOIE3_bp ); break;
  case toIntNum(Interrupt::TWO_WIRE_INT                   ): util::clrBit(_TWCR  , TWIE_bp  ); break;
  case toIntNum(Interrupt::SPM_READY                      ): util::clrBit(_SPMCSR, SPMIE_bp ); break;
  case toIntNum(Interrupt::TIMER4_COMPARE_A               ): util::clrBit(_TIMSK4, OCIE4A_bp); break;
  case toIntNum(Interrupt::TIMER4_COMPARE_B               ): util::clrBit(_TIMSK4, OCIE4B_bp); break;
  case toIntNum(Interrupt::TIMER4_COMPARE_D               ): util::clrBit(_TIMSK4, OCIE4D_bp); break;
  case toIntNum(Interrupt::TIMER4_OVERFLOW                ): util::clrBit(_TIMSK4, TOIE4_bp ); break;
  case toIntNum(Interrupt::TIMER4_FAULT_PROTECTION        ): util::clrBit(_TCCR4D, FPIE4_bp ); break;
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                         ): asm volatile("cli");    break;
#endif
  default                                                  : /* DO NOTHING */        break;
  }
}

void InterruptController::registerInterruptCallback(uint8_t const int_num, interface::InterruptCallback * interrupt_callback)
{
  switch(int_num)
  {
  case toIntNum(Interrupt::EXTERNAL_INT0                  ): isr_external_int0                   = interrupt_callback; break;
  case toIntNum(Interrupt::EXTERNAL_INT1                  ): isr_external_int1                   = interrupt_callback; break;
  case toIntNum(Interrupt::EXTERNAL_INT2                  ): isr_external_int2                   = interrupt_callback; break;
  case toIntNum(Interrupt::EXTERNAL_INT3                  ): isr_external_int3                   = interrupt_callback; break;
  case toIntNum(Interrupt::EXTERNAL_INT6                  ): isr_external_int6                   = interrupt_callback; break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0                ): isr_pin_change_int0                 = interrupt_callback; break;
  case toIntNum(Interrupt::USB_GENERAL                    ): isr_usb_general                     = interrupt_callback; break;
  case toIntNum(Interrupt::USB_ENDPOINT                   ): isr_usb_endpoint                    = interrupt_callback; break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                 ): isr_watchdog_timer                  = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                 ): isr_timer1_capture                  = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A               ): isr_timer1_compare_a                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B               ): isr_timer1_compare_b                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_C               ): isr_timer1_compare_c                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW                ): isr_timer1_overflow                 = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A               ): isr_timer0_compare_a                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B               ): isr_timer0_compare_b                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW                ): isr_timer0_overflow                 = interrupt_callback; break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   ): isr_spi_serial_transfer_complete    = interrupt_callback; break;
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ): isr_usart1_receive_complete         = interrupt_callback; break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY): isr_usart1_uart_data_register_empty = interrupt_callback; break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ): isr_usart1_transmit_complete        = interrupt_callback; break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR              ): isr_analog_comparator               = interrupt_callback; break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER       ): isr_analog_digital_converter        = interrupt_callback; break;
  case toIntNum(Interrupt::EEPROM_READY                   ): isr_eeprom_ready                    = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER3_CAPTURE                 ): isr_timer3_capture                  = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER3_COMPARE_A               ): isr_timer3_compare_a                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER3_COMPARE_B               ): isr_timer3_compare_b                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER3_COMPARE_C               ): isr_timer3_compare_c                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER3_OVERFLOW                ): isr_timer3_overflow                 = interrupt_callback; break;
  case toIntNum(Interrupt::TWO_WIRE_INT                   ): isr_two_wire_int                    = interrupt_callback; break;
  case toIntNum(Interrupt::SPM_READY                      ): isr_spm_ready                       = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER4_COMPARE_A               ): isr_timer4_compare_a                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER4_COMPARE_B               ): isr_timer4_compare_b                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER4_COMPARE_D               ): isr_timer4_compare_d                = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER4_OVERFLOW                ): isr_timer4_overflow                 = interrupt_callback; break;
  case toIntNum(Interrupt::TIMER4_FAULT_PROTECTION        ): isr_timer4_fault_protection         = interrupt_callback; break;
  default                                                  : /* DO NOTHING */                                          break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA16U4_32U4 */

} /* hal */

} /* spectre */

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

#if defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega32u4) || defined(MCU_TYPE_atmega16u4) )

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre::hal::ATMEGA16U4_32U4;

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

ISR(INT2_vect)
{
  executeCallbackIfValid(isr_external_int2);
}

ISR(INT3_vect)
{
  executeCallbackIfValid(isr_external_int3);
}

ISR(INT6_vect)
{
  executeCallbackIfValid(isr_external_int6);
}

ISR(PCINT0_vect)
{
  executeCallbackIfValid(isr_pin_change_int0);
}

ISR(USB_GEN_vect)
{
  executeCallbackIfValid(isr_usb_general);
}

ISR(USB_COM_vect)
{
  executeCallbackIfValid(isr_usb_endpoint);
}

ISR(WDT_vect)
{
  executeCallbackIfValid(isr_watchdog_timer);
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

ISR(TIMER1_COMPC_vect)
{
  executeCallbackIfValid(isr_timer1_compare_c);
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

ISR(USART1_RX_vect)
{
  executeCallbackIfValid(isr_usart1_receive_complete);
}

ISR(USART1_UDRE_vect)
{
  executeCallbackIfValid(isr_usart1_uart_data_register_empty);
}

ISR(USART1_TX_vect)
{
  executeCallbackIfValid(isr_usart1_transmit_complete);
}

ISR(ANALOG_COMP_vect)
{
  executeCallbackIfValid(isr_analog_comparator);
}

ISR(ADC_vect)
{
  executeCallbackIfValid(isr_analog_digital_converter);
}

ISR(EE_READY_vect)
{
  executeCallbackIfValid(isr_eeprom_ready);
}

ISR(TIMER3_CAPT_vect)
{
  executeCallbackIfValid(isr_timer3_capture);
}

ISR(TIMER3_COMPA_vect)
{
  executeCallbackIfValid(isr_timer3_compare_a);
}

ISR(TIMER3_COMPB_vect)
{
  executeCallbackIfValid(isr_timer3_compare_b);
}

ISR(TIMER3_COMPC_vect)
{
  executeCallbackIfValid(isr_timer3_compare_c);
}

ISR(TIMER3_OVF_vect)
{
  executeCallbackIfValid(isr_timer3_overflow);
}

ISR(TWI_vect)
{
  executeCallbackIfValid(isr_two_wire_int);
}

ISR(SPM_READY_vect)
{
  executeCallbackIfValid(isr_spm_ready);
}

ISR(TIMER4_COMPA_vect)
{
  executeCallbackIfValid(isr_timer4_compare_a);
}

ISR(TIMER4_COMPB_vect)
{
  executeCallbackIfValid(isr_timer4_compare_b);
}

ISR(TIMER4_COMPD_vect)
{
  executeCallbackIfValid(isr_timer4_compare_d);
}

ISR(TIMER4_OVF_vect)
{
  executeCallbackIfValid(isr_timer4_overflow);
}

ISR(TIMER4_FPF_vect)
{
  executeCallbackIfValid(isr_timer4_fault_protection);
}

#endif /* defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega32u4) || defined(MCU_TYPE_atmega16u4) ) */
