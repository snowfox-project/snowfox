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

#include <spectre/hal/avr/common/ATMEGA16U4_32U4/InterruptController.h>

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
 * DEFINES
 **************************************************************************************/

/* EIMSK */
#define INT6_bm   (1<<6)
#define INT3_bm   (1<<3)
#define INT2_bm   (1<<2)
#define INT1_bm   (1<<1)
#define INT0_bm   (1<<0)

/* PCICR */
#define PCIE0_bm  (1<<0)


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
                                         volatile uint8_t * pcicr)
: _EIMSK (eimsk ),
  _PCICR (pcicr )
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
  case toIntNum(Interrupt::EXTERNAL_INT0                  ): *_EIMSK   |= INT0_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT1                  ): *_EIMSK   |= INT1_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT2                  ): *_EIMSK   |= INT2_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT3                  ): *_EIMSK   |= INT3_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT6                  ): *_EIMSK   |= INT6_bm;   break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0                ): *_PCICR   |= PCIE0_bm;  break;
  case toIntNum(Interrupt::USB_GENERAL                    ): break;
  case toIntNum(Interrupt::USB_ENDPOINT                   ): break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                 ): break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                 ): break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A               ): break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B               ): break;
  case toIntNum(Interrupt::TIMER1_COMPARE_C               ): break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW                ): break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A               ): break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B               ): break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW                ): break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   ): break;
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ): break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY): break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ): break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR              ): break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER       ): break;
  case toIntNum(Interrupt::EEPROM_READY                   ): break;
  case toIntNum(Interrupt::TIMER3_CAPTURE                 ): break;
  case toIntNum(Interrupt::TIMER3_COMPARE_A               ): break;
  case toIntNum(Interrupt::TIMER3_COMPARE_B               ): break;
  case toIntNum(Interrupt::TIMER3_COMPARE_C               ): break;
  case toIntNum(Interrupt::TIMER3_OVERFLOW                ): break;
  case toIntNum(Interrupt::TWO_WIRE_INT                   ): break;
  case toIntNum(Interrupt::SPM_READY                      ): break;
  case toIntNum(Interrupt::TIMER4_COMPARE_A               ): break;
  case toIntNum(Interrupt::TIMER4_COMPARE_B               ): break;
  case toIntNum(Interrupt::TIMER4_COMPARE_D               ): break;
  case toIntNum(Interrupt::TIMER4_OVERFLOW                ): break;
  case toIntNum(Interrupt::TIMER4_FAULT_PROTECTION        ): break;
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                         ): asm volatile("sei");    break;
#endif
  default                                                  : /* DO NOTHING */        break;
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case toIntNum(Interrupt::EXTERNAL_INT0                  ): *_EIMSK   &= ~INT0_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT1                  ): *_EIMSK   &= ~INT1_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT2                  ): *_EIMSK   &= ~INT2_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT3                  ): *_EIMSK   &= ~INT3_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT6                  ): *_EIMSK   &= ~INT6_bm;   break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0                ): *_PCICR   &= ~PCIE0_bm;  break;
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                         ): asm volatile("cli");     break;
#endif
  default                                                  : /* DO NOTHING */         break;
  }
}

void InterruptController::registerInterruptCallback(uint8_t const isr_num, interface::InterruptCallback * interrupt_callback)
{
  switch(isr_num)
  {
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT0                  ): isr_external_int0                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT1                  ): isr_external_int1                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT2                  ): isr_external_int2                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT3                  ): isr_external_int3                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT6                  ): isr_external_int6                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::PIN_CHANGE_INT0                ): isr_pin_change_int0                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USB_GENERAL                    ): isr_usb_general                     = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USB_ENDPOINT                   ): isr_usb_endpoint                    = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::WATCHDOG_TIMER                 ): isr_watchdog_timer                  = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_CAPTURE                 ): isr_timer1_capture                  = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_COMPARE_A               ): isr_timer1_compare_a                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_COMPARE_B               ): isr_timer1_compare_b                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_COMPARE_C               ): isr_timer1_compare_c                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_OVERFLOW                ): isr_timer1_overflow                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER0_COMPARE_A               ): isr_timer0_compare_a                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER0_COMPARE_B               ): isr_timer0_compare_b                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER0_OVERFLOW                ): isr_timer0_overflow                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::SPI_SERIAL_TRANSFER_COMPLETE   ): isr_spi_serial_transfer_complete    = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART1_RECEIVE_COMPLETE        ): isr_usart1_receive_complete         = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART1_UART_DATA_REGISTER_EMPTY): isr_usart1_uart_data_register_empty = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART1_TRANSMIT_COMPLETE       ): isr_usart1_transmit_complete        = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::ANALOG_COMPARATOR              ): isr_analog_comparator               = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::ANALOG_DIGITAL_CONVERTER       ): isr_analog_digital_converter        = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EEPROM_READY                   ): isr_eeprom_ready                    = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_CAPTURE                 ): isr_timer3_capture                  = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_COMPARE_A               ): isr_timer3_compare_a                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_COMPARE_B               ): isr_timer3_compare_b                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_COMPARE_C               ): isr_timer3_compare_c                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_OVERFLOW                ): isr_timer3_overflow                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TWO_WIRE_INT                   ): isr_two_wire_int                    = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::SPM_READY                      ): isr_spm_ready                       = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER4_COMPARE_A               ): isr_timer4_compare_a                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER4_COMPARE_B               ): isr_timer4_compare_b                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER4_COMPARE_D               ): isr_timer4_compare_d                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER4_OVERFLOW                ): isr_timer4_overflow                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER4_FAULT_PROTECTION        ): isr_timer4_fault_protection         = interrupt_callback; break;
  default                                                                : /* DO NOTHING */                                          break;
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
  if(isr_external_int0) isr_external_int0->interruptServiceRoutine();
}

ISR(INT1_vect)
{
  if(isr_external_int1) isr_external_int1->interruptServiceRoutine();
}

ISR(INT2_vect)
{
  if(isr_external_int2) isr_external_int2->interruptServiceRoutine();
}

ISR(INT3_vect)
{
  if(isr_external_int3) isr_external_int3->interruptServiceRoutine();
}

ISR(INT6_vect)
{
  if(isr_external_int6) isr_external_int6->interruptServiceRoutine();
}

ISR(PCINT0_vect)
{
  if(isr_pin_change_int0) isr_pin_change_int0->interruptServiceRoutine();
}

ISR(USB_GEN_vect)
{
  if(isr_usb_general) isr_usb_general->interruptServiceRoutine();
}

ISR(USB_COM_vect)
{
  if(isr_usb_endpoint) isr_usb_endpoint->interruptServiceRoutine();
}

ISR(WDT_vect)
{
  if(isr_watchdog_timer) isr_watchdog_timer->interruptServiceRoutine();
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

ISR(TIMER1_COMPC_vect)
{
  if(isr_timer1_compare_c) isr_timer1_compare_c->interruptServiceRoutine();
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

ISR(USART1_RX_vect)
{
  if(isr_usart1_receive_complete) isr_usart1_receive_complete->interruptServiceRoutine();
}

ISR(USART1_UDRE_vect)
{
  if(isr_usart1_uart_data_register_empty) isr_usart1_uart_data_register_empty->interruptServiceRoutine();
}

ISR(USART1_TX_vect)
{
  if(isr_usart1_transmit_complete) isr_usart1_transmit_complete->interruptServiceRoutine();
}

ISR(ANALOG_COMP_vect)
{
  if(isr_analog_comparator) isr_analog_comparator->interruptServiceRoutine();
}

ISR(ADC_vect)
{
  if(isr_analog_digital_converter) isr_analog_digital_converter->interruptServiceRoutine();
}

ISR(EE_READY_vect)
{
  if(isr_eeprom_ready) isr_eeprom_ready->interruptServiceRoutine();
}

ISR(TIMER3_CAPT_vect)
{
  if(isr_timer3_capture) isr_timer3_capture->interruptServiceRoutine();
}

ISR(TIMER3_COMPA_vect)
{
  if(isr_timer3_compare_a) isr_timer3_compare_a->interruptServiceRoutine();
}

ISR(TIMER3_COMPB_vect)
{
  if(isr_timer3_compare_b) isr_timer3_compare_b->interruptServiceRoutine();
}

ISR(TIMER3_COMPC_vect)
{
  if(isr_timer3_compare_c) isr_timer3_compare_c->interruptServiceRoutine();
}

ISR(TIMER3_OVF_vect)
{
  if(isr_timer3_overflow) isr_timer3_overflow->interruptServiceRoutine();
}

ISR(TWI_vect)
{
  if(isr_two_wire_int) isr_two_wire_int->interruptServiceRoutine();
}

ISR(SPM_READY_vect)
{
  if(isr_spm_ready) isr_spm_ready->interruptServiceRoutine();
}

ISR(TIMER4_COMPA_vect)
{
  if(isr_timer4_compare_a) isr_timer4_compare_a->interruptServiceRoutine();
}

ISR(TIMER4_COMPB_vect)
{
  if(isr_timer4_compare_b) isr_timer4_compare_b->interruptServiceRoutine();
}

ISR(TIMER4_COMPD_vect)
{
  if(isr_timer4_compare_d) isr_timer4_compare_d->interruptServiceRoutine();
}

ISR(TIMER4_OVF_vect)
{
  if(isr_timer4_overflow) isr_timer4_overflow->interruptServiceRoutine();
}

ISR(TIMER4_FPF_vect)
{
  if(isr_timer4_fault_protection) isr_timer4_fault_protection->interruptServiceRoutine();
}

#endif /* defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega32u4) || defined(MCU_TYPE_atmega16u4) ) */
