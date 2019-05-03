/**
 * Snowfox is a modular RTOS with extensive IO support.
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

#include <snowfox/hal/avr/ATMEGA328P/InterruptController.h>

#include <snowfox/util/BitUtil.h>

#include <snowfox/cpu/avr/io/ATMEGA328P.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace ATMEGA328P
{

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint8_t constexpr NUM_INTERRUPT_CALLBACKS = 45;

static_assert(NUM_INTERRUPT_CALLBACKS == toIntNum(Interrupt::SPM_READY) + 1, "Error: number of interrupt callbacks is not equal with number of interrupts");

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

static interface::InterruptCallback * isr[NUM_INTERRUPT_CALLBACKS] = {0};

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

InterruptController::InterruptController(volatile uint8_t * eimsk,
                                         volatile uint8_t * pcicr,
                                         volatile uint8_t * pcmsk0,
                                         volatile uint8_t * pcmsk1,
                                         volatile uint8_t * pcmsk2,
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
  _PCMSK0 (pcmsk0),
  _PCMSK1 (pcmsk1),
  _PCMSK2 (pcmsk2),
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
  case toIntNum(Interrupt::EXTERNAL_INT0                 ): { util::setBit(_EIMSK , INT0_bp  );                                    } break;
  case toIntNum(Interrupt::EXTERNAL_INT1                 ): { util::setBit(_EIMSK , INT1_bp  );                                    } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0               ): { util::setBit(_PCICR , PCIE0_bp ); util::setBit(_PCMSK0, PCINT0_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT1               ): { util::setBit(_PCICR , PCIE0_bp ); util::setBit(_PCMSK0, PCINT1_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT2               ): { util::setBit(_PCICR , PCIE0_bp ); util::setBit(_PCMSK0, PCINT2_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT3               ): { util::setBit(_PCICR , PCIE0_bp ); util::setBit(_PCMSK0, PCINT3_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT4               ): { util::setBit(_PCICR , PCIE0_bp ); util::setBit(_PCMSK0, PCINT4_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT5               ): { util::setBit(_PCICR , PCIE0_bp ); util::setBit(_PCMSK0, PCINT5_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT6               ): { util::setBit(_PCICR , PCIE0_bp ); util::setBit(_PCMSK0, PCINT6_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT7               ): { util::setBit(_PCICR , PCIE0_bp ); util::setBit(_PCMSK0, PCINT7_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT8               ): { util::setBit(_PCICR , PCIE1_bp ); util::setBit(_PCMSK1, PCINT8_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT9               ): { util::setBit(_PCICR , PCIE1_bp ); util::setBit(_PCMSK1, PCINT9_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT10              ): { util::setBit(_PCICR , PCIE1_bp ); util::setBit(_PCMSK1, PCINT10_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT11              ): { util::setBit(_PCICR , PCIE1_bp ); util::setBit(_PCMSK1, PCINT11_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT12              ): { util::setBit(_PCICR , PCIE1_bp ); util::setBit(_PCMSK1, PCINT12_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT13              ): { util::setBit(_PCICR , PCIE1_bp ); util::setBit(_PCMSK1, PCINT13_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT14              ): { util::setBit(_PCICR , PCIE1_bp ); util::setBit(_PCMSK1, PCINT14_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT16              ): { util::setBit(_PCICR , PCIE2_bp ); util::setBit(_PCMSK2, PCINT16_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT17              ): { util::setBit(_PCICR , PCIE2_bp ); util::setBit(_PCMSK2, PCINT17_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT18              ): { util::setBit(_PCICR , PCIE2_bp ); util::setBit(_PCMSK2, PCINT18_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT19              ): { util::setBit(_PCICR , PCIE2_bp ); util::setBit(_PCMSK2, PCINT19_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT20              ): { util::setBit(_PCICR , PCIE2_bp ); util::setBit(_PCMSK2, PCINT20_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT21              ): { util::setBit(_PCICR , PCIE2_bp ); util::setBit(_PCMSK2, PCINT21_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT22              ): { util::setBit(_PCICR , PCIE2_bp ); util::setBit(_PCMSK2, PCINT22_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT23              ): { util::setBit(_PCICR , PCIE2_bp ); util::setBit(_PCMSK2, PCINT23_bp); } break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                ): { util::setBit(_WDTCSR, WDIE_bp  );                                    } break;
  case toIntNum(Interrupt::TIMER2_COMPARE_A              ): { util::setBit(_TIMSK2, OCIE2A_bp);                                    } break;
  case toIntNum(Interrupt::TIMER2_COMPARE_B              ): { util::setBit(_TIMSK2, OCIE2B_bp);                                    } break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW               ): { util::setBit(_TIMSK2, TOIE2_bp );                                    } break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                ): { util::setBit(_TIMSK1, ICIE1_bp );                                    } break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A              ): { util::setBit(_TIMSK1, OCIE1A_bp);                                    } break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B              ): { util::setBit(_TIMSK1, OCIE1B_bp);                                    } break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW               ): { util::setBit(_TIMSK1, TOIE1_bp );                                    } break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A              ): { util::setBit(_TIMSK0, OCIE0A_bp);                                    } break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B              ): { util::setBit(_TIMSK0, OCIE0B_bp);                                    } break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW               ): { util::setBit(_TIMSK0, TOIE0_bp );                                    } break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE  ): { util::setBit(_SPCR  , SPIE_bp  );                                    } break;
  case toIntNum(Interrupt::USART_RECEIVE_COMPLETE        ): { util::setBit(_UCSR0B, RXCIE0_bp);                                    } break;
  case toIntNum(Interrupt::USART_UART_DATA_REGISTER_EMPTY): { util::setBit(_UCSR0B, UDRIE0_bp);                                    } break;
  case toIntNum(Interrupt::USART_TRANSMIT_COMPLETE       ): { util::setBit(_UCSR0B, TXCIE0_bp);                                    } break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER      ): { util::setBit(_ADCSRA, ADIE_bp  );                                    } break;
  case toIntNum(Interrupt::EEPROM_READY                  ): { util::setBit(_EECR  , EERIE_bp );                                    } break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR             ): { util::setBit(_ACSR  , ACIE_bp  );                                    } break;
  case toIntNum(Interrupt::TWO_WIRE_INT                  ): { util::setBit(_TWCR  , TWIE_bp  );                                    } break;
  case toIntNum(Interrupt::SPM_READY                     ): { util::setBit(_SPMCSR, SPMIE_bp );                                    } break;
#if defined(MCU_ARCH_avr) && defined(MCU_TYPE_atmega328p)
  case toIntNum(Interrupt::GLOBAL                        ): asm volatile("sei");                                                     break;
#endif
  default                                                 : /* DO NOTHING */                                                         break;
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case toIntNum(Interrupt::EXTERNAL_INT0                 ): { util::clrBit(_EIMSK , INT0_bp  );                                    } break;
  case toIntNum(Interrupt::EXTERNAL_INT1                 ): { util::clrBit(_EIMSK , INT1_bp  );                                    } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0               ): {                                   util::clrBit(_PCMSK0, PCINT0_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT1               ): {                                   util::clrBit(_PCMSK0, PCINT1_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT2               ): {                                   util::clrBit(_PCMSK0, PCINT2_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT3               ): {                                   util::clrBit(_PCMSK0, PCINT3_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT4               ): {                                   util::clrBit(_PCMSK0, PCINT4_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT5               ): {                                   util::clrBit(_PCMSK0, PCINT5_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT6               ): {                                   util::clrBit(_PCMSK0, PCINT6_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT7               ): {                                   util::clrBit(_PCMSK0, PCINT7_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT8               ): {                                   util::clrBit(_PCMSK1, PCINT8_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT9               ): {                                   util::clrBit(_PCMSK1, PCINT9_bp ); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT10              ): {                                   util::clrBit(_PCMSK1, PCINT10_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT11              ): {                                   util::clrBit(_PCMSK1, PCINT11_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT12              ): {                                   util::clrBit(_PCMSK1, PCINT12_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT13              ): {                                   util::clrBit(_PCMSK1, PCINT13_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT14              ): {                                   util::clrBit(_PCMSK1, PCINT14_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT16              ): {                                   util::clrBit(_PCMSK2, PCINT16_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT17              ): {                                   util::clrBit(_PCMSK2, PCINT17_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT18              ): {                                   util::clrBit(_PCMSK2, PCINT18_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT19              ): {                                   util::clrBit(_PCMSK2, PCINT19_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT20              ): {                                   util::clrBit(_PCMSK2, PCINT20_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT21              ): {                                   util::clrBit(_PCMSK2, PCINT21_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT22              ): {                                   util::clrBit(_PCMSK2, PCINT22_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT23              ): {                                   util::clrBit(_PCMSK2, PCINT23_bp); } break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                ): { util::clrBit(_WDTCSR, WDIE_bp  );                                    } break;
  case toIntNum(Interrupt::TIMER2_COMPARE_A              ): { util::clrBit(_TIMSK2, OCIE2A_bp);                                    } break;
  case toIntNum(Interrupt::TIMER2_COMPARE_B              ): { util::clrBit(_TIMSK2, OCIE2B_bp);                                    } break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW               ): { util::clrBit(_TIMSK2, TOIE2_bp );                                    } break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                ): { util::clrBit(_TIMSK1, ICIE1_bp );                                    } break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A              ): { util::clrBit(_TIMSK1, OCIE1A_bp);                                    } break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B              ): { util::clrBit(_TIMSK1, OCIE1B_bp);                                    } break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW               ): { util::clrBit(_TIMSK1, TOIE1_bp );                                    } break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A              ): { util::clrBit(_TIMSK0, OCIE0A_bp);                                    } break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B              ): { util::clrBit(_TIMSK0, OCIE0B_bp);                                    } break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW               ): { util::clrBit(_TIMSK0, TOIE0_bp );                                    } break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE  ): { util::clrBit(_SPCR  , SPIE_bp  );                                    } break;
  case toIntNum(Interrupt::USART_RECEIVE_COMPLETE        ): { util::clrBit(_UCSR0B, RXCIE0_bp);                                    } break;
  case toIntNum(Interrupt::USART_UART_DATA_REGISTER_EMPTY): { util::clrBit(_UCSR0B, UDRIE0_bp);                                    } break;
  case toIntNum(Interrupt::USART_TRANSMIT_COMPLETE       ): { util::clrBit(_UCSR0B, TXCIE0_bp);                                    } break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER      ): { util::clrBit(_ADCSRA, ADIE_bp  );                                    } break;
  case toIntNum(Interrupt::EEPROM_READY                  ): { util::clrBit(_EECR  , EERIE_bp );                                    } break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR             ): { util::clrBit(_ACSR  , ACIE_bp  );                                    } break;
  case toIntNum(Interrupt::TWO_WIRE_INT                  ): { util::clrBit(_TWCR  , TWIE_bp  );                                    } break;
  case toIntNum(Interrupt::SPM_READY                     ): { util::clrBit(_SPMCSR, SPMIE_bp );                                    } break;
#if defined(MCU_ARCH_avr) && defined(MCU_TYPE_atmega328p)
  case toIntNum(Interrupt::GLOBAL                        ): asm volatile("cli");                                                     break;
#endif
  default                                                 : /* DO NOTHING */                                                         break;
  }
}

void InterruptController::registerInterruptCallback(uint8_t const int_num, interface::InterruptCallback * interrupt_callback)
{
  if(int_num < NUM_INTERRUPT_CALLBACKS)
  {
    isr[int_num] = interrupt_callback;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* snowfox */

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

using namespace snowfox::hal::interface;
using namespace snowfox::hal::ATMEGA328P;

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

ISR(INT0_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::EXTERNAL_INT0)]);
}

ISR(INT1_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::EXTERNAL_INT1)]);
}

ISR(PCINT0_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT0)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT1)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT2)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT3)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT4)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT5)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT6)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT7)]);
}

ISR(PCINT1_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT8 )]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT9 )]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT10)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT11)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT12)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT13)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT14)]);
}

ISR(PCINT2_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT16)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT17)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT18)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT19)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT20)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT21)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT22)]);
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT23)]);
}

ISR(WDT_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::WATCHDOG_TIMER)]);
}

ISR(TIMER2_COMPA_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER2_COMPARE_A)]);
}

ISR(TIMER2_COMPB_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER2_COMPARE_B)]);
}

ISR(TIMER2_OVF_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER2_OVERFLOW)]);
}

ISR(TIMER1_CAPT_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER1_CAPTURE)]);
}

ISR(TIMER1_COMPA_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER1_COMPARE_A)]);
}

ISR(TIMER1_COMPB_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER1_COMPARE_B)]);
}

ISR(TIMER1_OVF_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER1_OVERFLOW)]);
}

ISR(TIMER0_COMPA_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER0_COMPARE_A)]);
}

ISR(TIMER0_COMPB_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER0_COMPARE_B)]);
}

ISR(TIMER0_OVF_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER0_OVERFLOW)]);
}

ISR(SPI_STC_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE)]);
}

ISR(USART_RX_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART_RECEIVE_COMPLETE)]);
}

ISR(USART_UDRE_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART_UART_DATA_REGISTER_EMPTY)]);
}

ISR(USART_TX_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART_TRANSMIT_COMPLETE)]);
}

ISR(ADC_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER)]);
}

ISR(EE_READY_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::EEPROM_READY)]);
}

ISR(ANALOG_COMP_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::ANALOG_COMPARATOR)]);
}

ISR(TWI_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TWO_WIRE_INT)]);
}

ISR(SPM_READY_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::SPM_READY)]);
}

#endif /* defined(MCU_ARCH_avr) && defined(MCU_TYPE_atmega328p) */
