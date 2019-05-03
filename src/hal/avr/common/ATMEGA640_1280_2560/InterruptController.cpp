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

#include <snowfox/hal/avr/common/ATMEGA640_1280_2560/InterruptController.h>

#include <snowfox/util/BitUtil.h>

#include <snowfox/cpu/avr/io/common/ATMEGA640_1280_2560.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace ATMEGA640_1280_2560
{

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint8_t constexpr NUM_INTERRUPT_CALLBACKS = 77;

static_assert(NUM_INTERRUPT_CALLBACKS == toIntNum(Interrupt::USART3_TRANSMIT_COMPLETE) + 1, "Error: number of interrupt callbacks is not equal with number of interrupts");

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
                                         volatile uint8_t * timsk3,
                                         volatile uint8_t * timsk4,
                                         volatile uint8_t * timsk5,
                                         volatile uint8_t * ucsr0b,
                                         volatile uint8_t * ucsr1b,
                                         volatile uint8_t * ucsr2b,
                                         volatile uint8_t * ucsr3b,
                                         volatile uint8_t * spcr,
                                         volatile uint8_t * twcr,
                                         volatile uint8_t * eecr,
                                         volatile uint8_t * spmcsr,
                                         volatile uint8_t * acsr,
                                         volatile uint8_t * adcsra)
: _EIMSK (eimsk ),
  _PCICR (pcicr ),
  _PCMSK0(pcmsk0),
  _PCMSK1(pcmsk1),
  _PCMSK2(pcmsk2),
  _WDTCSR(wdtcsr),
  _TIMSK0(timsk0),
  _TIMSK1(timsk1),
  _TIMSK2(timsk2),
  _TIMSK3(timsk3),
  _TIMSK4(timsk4),
  _TIMSK5(timsk5),
  _UCSR0B(ucsr0b),
  _UCSR1B(ucsr1b),
  _UCSR2B(ucsr2b),
  _UCSR3B(ucsr3b),
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
  case toIntNum(Interrupt::EXTERNAL_INT0                  ): { util::setBit(_EIMSK , INT0_bp  );                                    } break;
  case toIntNum(Interrupt::EXTERNAL_INT1                  ): { util::setBit(_EIMSK , INT1_bp  );                                    } break;
  case toIntNum(Interrupt::EXTERNAL_INT2                  ): { util::setBit(_EIMSK , INT2_bp  );                                    } break;
  case toIntNum(Interrupt::EXTERNAL_INT3                  ): { util::setBit(_EIMSK , INT3_bp  );                                    } break;
  case toIntNum(Interrupt::EXTERNAL_INT4                  ): { util::setBit(_EIMSK , INT4_bp  );                                    } break;
  case toIntNum(Interrupt::EXTERNAL_INT5                  ): { util::setBit(_EIMSK , INT5_bp  );                                    } break;
  case toIntNum(Interrupt::EXTERNAL_INT6                  ): { util::setBit(_EIMSK , INT6_bp  );                                    } break;
  case toIntNum(Interrupt::EXTERNAL_INT7                  ): { util::setBit(_EIMSK , INT7_bp  );                                    } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0                ): { util::setBit(_PCICR, PCIE0_bp  ); util::setBit(_PCMSK0, PCINT0_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT1                ): { util::setBit(_PCICR, PCIE0_bp  ); util::setBit(_PCMSK0, PCINT1_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT2                ): { util::setBit(_PCICR, PCIE0_bp  ); util::setBit(_PCMSK0, PCINT2_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT3                ): { util::setBit(_PCICR, PCIE0_bp  ); util::setBit(_PCMSK0, PCINT3_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT4                ): { util::setBit(_PCICR, PCIE0_bp  ); util::setBit(_PCMSK0, PCINT4_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT5                ): { util::setBit(_PCICR, PCIE0_bp  ); util::setBit(_PCMSK0, PCINT5_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT6                ): { util::setBit(_PCICR, PCIE0_bp  ); util::setBit(_PCMSK0, PCINT6_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT7                ): { util::setBit(_PCICR, PCIE0_bp  ); util::setBit(_PCMSK0, PCINT7_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT8                ): { util::setBit(_PCICR, PCIE1_bp  ); util::setBit(_PCMSK1, PCINT8_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT9                ): { util::setBit(_PCICR, PCIE1_bp  ); util::setBit(_PCMSK1, PCINT9_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT10               ): { util::setBit(_PCICR, PCIE1_bp  ); util::setBit(_PCMSK1, PCINT10_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT11               ): { util::setBit(_PCICR, PCIE1_bp  ); util::setBit(_PCMSK1, PCINT11_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT12               ): { util::setBit(_PCICR, PCIE1_bp  ); util::setBit(_PCMSK1, PCINT12_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT13               ): { util::setBit(_PCICR, PCIE1_bp  ); util::setBit(_PCMSK1, PCINT13_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT14               ): { util::setBit(_PCICR, PCIE1_bp  ); util::setBit(_PCMSK1, PCINT14_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT15               ): { util::setBit(_PCICR, PCIE1_bp  ); util::setBit(_PCMSK1, PCINT15_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT16               ): { util::setBit(_PCICR, PCIE2_bp  ); util::setBit(_PCMSK2, PCINT16_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT17               ): { util::setBit(_PCICR, PCIE2_bp  ); util::setBit(_PCMSK2, PCINT17_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT18               ): { util::setBit(_PCICR, PCIE2_bp  ); util::setBit(_PCMSK2, PCINT18_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT19               ): { util::setBit(_PCICR, PCIE2_bp  ); util::setBit(_PCMSK2, PCINT19_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT20               ): { util::setBit(_PCICR, PCIE2_bp  ); util::setBit(_PCMSK2, PCINT20_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT21               ): { util::setBit(_PCICR, PCIE2_bp  ); util::setBit(_PCMSK2, PCINT21_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT22               ): { util::setBit(_PCICR, PCIE2_bp  ); util::setBit(_PCMSK2, PCINT22_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT23               ): { util::setBit(_PCICR, PCIE2_bp  ); util::setBit(_PCMSK2, PCINT23_bp); } break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                 ): { util::setBit(_WDTCSR, WDIE_bp  );                                    } break;
  case toIntNum(Interrupt::TIMER2_COMPARE_A               ): { util::setBit(_TIMSK2, OCIE2A_bp);                                    } break;
  case toIntNum(Interrupt::TIMER2_COMPARE_B               ): { util::setBit(_TIMSK2, OCIE2B_bp);                                    } break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW                ): { util::setBit(_TIMSK2, TOIE2_bp );                                    } break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                 ): { util::setBit(_TIMSK1, ICIE1_bp );                                    } break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A               ): { util::setBit(_TIMSK1, OCIE1A_bp);                                    } break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B               ): { util::setBit(_TIMSK1, OCIE1B_bp);                                    } break;
  case toIntNum(Interrupt::TIMER1_COMPARE_C               ): { util::setBit(_TIMSK1, OCIE1C_bp);                                    } break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW                ): { util::setBit(_TIMSK1, TOIE1_bp );                                    } break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A               ): { util::setBit(_TIMSK0, OCIE0A_bp);                                    } break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B               ): { util::setBit(_TIMSK0, OCIE0B_bp);                                    } break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW                ): { util::setBit(_TIMSK0, TOIE0_bp );                                    } break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   ): { util::setBit(_SPCR  , SPIE_bp  );                                    } break;
  case toIntNum(Interrupt::USART0_RECEIVE_COMPLETE        ): { util::setBit(_UCSR0B, RXCIE0_bp);                                    } break;
  case toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY): { util::setBit(_UCSR0B, UDRIE0_bp);                                    } break;
  case toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE       ): { util::setBit(_UCSR0B, TXCIE0_bp);                                    } break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR              ): { util::setBit(_ACSR  , ACIE_bp  );                                    } break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER       ): { util::setBit(_ADCSRA, ADIE_bp  );                                    } break;
  case toIntNum(Interrupt::EEPROM_READY                   ): { util::setBit(_EECR  , EERIE_bp );                                    } break;
  case toIntNum(Interrupt::TIMER3_CAPTURE                 ): { util::setBit(_TIMSK3, ICIE3_bp );                                    } break;
  case toIntNum(Interrupt::TIMER3_COMPARE_A               ): { util::setBit(_TIMSK3, OCIE3A_bp);                                    } break;
  case toIntNum(Interrupt::TIMER3_COMPARE_B               ): { util::setBit(_TIMSK3, OCIE3B_bp);                                    } break;
  case toIntNum(Interrupt::TIMER3_COMPARE_C               ): { util::setBit(_TIMSK3, OCIE3C_bp);                                    } break;
  case toIntNum(Interrupt::TIMER3_OVERFLOW                ): { util::setBit(_TIMSK3, TOIE3_bp );                                    } break;
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ): { util::setBit(_UCSR1B, RXCIE1_bp);                                    } break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY): { util::setBit(_UCSR1B, UDRIE1_bp);                                    } break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ): { util::setBit(_UCSR1B, TXCIE1_bp);                                    } break;
  case toIntNum(Interrupt::TWO_WIRE_INT                   ): { util::setBit(_TWCR  , TWIE_bp  );                                    } break;
  case toIntNum(Interrupt::SPM_READY                      ): { util::setBit(_SPMCSR, SPMIE_bp );                                    } break;
  case toIntNum(Interrupt::TIMER4_CAPTURE                 ): { util::setBit(_TIMSK4, ICIE4_bp );                                    } break;
  case toIntNum(Interrupt::TIMER4_COMPARE_A               ): { util::setBit(_TIMSK4, OCIE4A_bp);                                    } break;
  case toIntNum(Interrupt::TIMER4_COMPARE_B               ): { util::setBit(_TIMSK4, OCIE4B_bp);                                    } break;
  case toIntNum(Interrupt::TIMER4_COMPARE_C               ): { util::setBit(_TIMSK4, OCIE4C_bp);                                    } break;
  case toIntNum(Interrupt::TIMER4_OVERFLOW                ): { util::setBit(_TIMSK4, TOIE4_bp );                                    } break;
  case toIntNum(Interrupt::TIMER5_CAPTURE                 ): { util::setBit(_TIMSK5, ICIE5_bp );                                    } break;
  case toIntNum(Interrupt::TIMER5_COMPARE_A               ): { util::setBit(_TIMSK5, OCIE5A_bp);                                    } break;
  case toIntNum(Interrupt::TIMER5_COMPARE_B               ): { util::setBit(_TIMSK5, OCIE5B_bp);                                    } break;
  case toIntNum(Interrupt::TIMER5_COMPARE_C               ): { util::setBit(_TIMSK5, OCIE5C_bp);                                    } break;
  case toIntNum(Interrupt::TIMER5_OVERFLOW                ): { util::setBit(_TIMSK5, TOIE5_bp );                                    } break;
  case toIntNum(Interrupt::USART2_RECEIVE_COMPLETE        ): { util::setBit(_UCSR2B, RXCIE2_bp);                                    } break;
  case toIntNum(Interrupt::USART2_UART_DATA_REGISTER_EMPTY): { util::setBit(_UCSR2B, UDRIE2_bp);                                    } break;
  case toIntNum(Interrupt::USART2_TRANSMIT_COMPLETE       ): { util::setBit(_UCSR2B, TXCIE2_bp);                                    } break;
  case toIntNum(Interrupt::USART3_RECEIVE_COMPLETE        ): { util::setBit(_UCSR3B, RXCIE3_bp);                                    } break;
  case toIntNum(Interrupt::USART3_UART_DATA_REGISTER_EMPTY): { util::setBit(_UCSR3B, UDRIE3_bp);                                    } break;
  case toIntNum(Interrupt::USART3_TRANSMIT_COMPLETE       ): { util::setBit(_UCSR3B, TXCIE3_bp);                                    } break;
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                         ): asm volatile("sei");                                                     break;
#endif
  default                                                  : /* DO NOTHING */                                                         break;
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case toIntNum(Interrupt::EXTERNAL_INT0                  ): { util::clrBit(_EIMSK , INT0_bp  );                                           } break;
  case toIntNum(Interrupt::EXTERNAL_INT1                  ): { util::clrBit(_EIMSK , INT1_bp  );                                           } break;
  case toIntNum(Interrupt::EXTERNAL_INT2                  ): { util::clrBit(_EIMSK , INT2_bp  );                                           } break;
  case toIntNum(Interrupt::EXTERNAL_INT3                  ): { util::clrBit(_EIMSK , INT3_bp  );                                           } break;
  case toIntNum(Interrupt::EXTERNAL_INT4                  ): { util::clrBit(_EIMSK , INT4_bp  );                                           } break;
  case toIntNum(Interrupt::EXTERNAL_INT5                  ): { util::clrBit(_EIMSK , INT5_bp  );                                           } break;
  case toIntNum(Interrupt::EXTERNAL_INT6                  ): { util::clrBit(_EIMSK , INT6_bp  );                                           } break;
  case toIntNum(Interrupt::EXTERNAL_INT7                  ): { util::clrBit(_EIMSK , INT7_bp  );                                           } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0                ): {                                          util::clrBit(_PCMSK0, PCINT0_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT1                ): {                                          util::clrBit(_PCMSK0, PCINT1_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT2                ): {                                          util::clrBit(_PCMSK0, PCINT2_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT3                ): {                                          util::clrBit(_PCMSK0, PCINT3_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT4                ): {                                          util::clrBit(_PCMSK0, PCINT4_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT5                ): {                                          util::clrBit(_PCMSK0, PCINT5_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT6                ): {                                          util::clrBit(_PCMSK0, PCINT6_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT7                ): {                                          util::clrBit(_PCMSK0, PCINT7_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT8                ): {                                          util::clrBit(_PCMSK1, PCINT8_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT9                ): {                                          util::clrBit(_PCMSK1, PCINT9_bp);  } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT10               ): {                                          util::clrBit(_PCMSK1, PCINT10_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT11               ): {                                          util::clrBit(_PCMSK1, PCINT11_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT12               ): {                                          util::clrBit(_PCMSK1, PCINT12_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT13               ): {                                          util::clrBit(_PCMSK1, PCINT13_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT14               ): {                                          util::clrBit(_PCMSK1, PCINT14_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT15               ): {                                          util::clrBit(_PCMSK1, PCINT15_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT16               ): {                                          util::clrBit(_PCMSK2, PCINT16_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT17               ): {                                          util::clrBit(_PCMSK2, PCINT17_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT18               ): {                                          util::clrBit(_PCMSK2, PCINT18_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT19               ): {                                          util::clrBit(_PCMSK2, PCINT19_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT20               ): {                                          util::clrBit(_PCMSK2, PCINT20_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT21               ): {                                          util::clrBit(_PCMSK2, PCINT21_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT22               ): {                                          util::clrBit(_PCMSK2, PCINT22_bp); } break;
  case toIntNum(Interrupt::PIN_CHANGE_INT23               ): {                                          util::clrBit(_PCMSK2, PCINT23_bp); } break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                 ): { util::clrBit(_WDTCSR, WDIE_bp  );                                           } break;
  case toIntNum(Interrupt::TIMER2_COMPARE_A               ): { util::clrBit(_TIMSK2, OCIE2A_bp);                                           } break;
  case toIntNum(Interrupt::TIMER2_COMPARE_B               ): { util::clrBit(_TIMSK2, OCIE2B_bp);                                           } break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW                ): { util::clrBit(_TIMSK2, TOIE2_bp );                                           } break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                 ): { util::clrBit(_TIMSK1, ICIE1_bp );                                           } break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A               ): { util::clrBit(_TIMSK1, OCIE1A_bp);                                           } break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B               ): { util::clrBit(_TIMSK1, OCIE1B_bp);                                           } break;
  case toIntNum(Interrupt::TIMER1_COMPARE_C               ): { util::clrBit(_TIMSK1, OCIE1C_bp);                                           } break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW                ): { util::clrBit(_TIMSK1, TOIE1_bp );                                           } break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A               ): { util::clrBit(_TIMSK0, OCIE0A_bp);                                           } break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B               ): { util::clrBit(_TIMSK0, OCIE0B_bp);                                           } break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW                ): { util::clrBit(_TIMSK0, TOIE0_bp );                                           } break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   ): { util::clrBit(_SPCR  , SPIE_bp  );                                           } break;
  case toIntNum(Interrupt::USART0_RECEIVE_COMPLETE        ): { util::clrBit(_UCSR0B, RXCIE0_bp);                                           } break;
  case toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY): { util::clrBit(_UCSR0B, UDRIE0_bp);                                           } break;
  case toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE       ): { util::clrBit(_UCSR0B, TXCIE0_bp);                                           } break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR              ): { util::clrBit(_ACSR  , ACIE_bp  );                                           } break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER       ): { util::clrBit(_ADCSRA, ADIE_bp  );                                           } break;
  case toIntNum(Interrupt::EEPROM_READY                   ): { util::clrBit(_EECR  , EERIE_bp );                                           } break;
  case toIntNum(Interrupt::TIMER3_CAPTURE                 ): { util::clrBit(_TIMSK3, ICIE3_bp );                                           } break;
  case toIntNum(Interrupt::TIMER3_COMPARE_A               ): { util::clrBit(_TIMSK3, OCIE3A_bp);                                           } break;
  case toIntNum(Interrupt::TIMER3_COMPARE_B               ): { util::clrBit(_TIMSK3, OCIE3B_bp);                                           } break;
  case toIntNum(Interrupt::TIMER3_COMPARE_C               ): { util::clrBit(_TIMSK3, OCIE3C_bp);                                           } break;
  case toIntNum(Interrupt::TIMER3_OVERFLOW                ): { util::clrBit(_TIMSK3, TOIE3_bp );                                           } break;
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ): { util::clrBit(_UCSR1B, RXCIE1_bp);                                           } break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY): { util::clrBit(_UCSR1B, UDRIE1_bp);                                           } break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ): { util::clrBit(_UCSR1B, TXCIE1_bp);                                           } break;
  case toIntNum(Interrupt::TWO_WIRE_INT                   ): { util::clrBit(_TWCR  , TWIE_bp  );                                           } break;
  case toIntNum(Interrupt::SPM_READY                      ): { util::clrBit(_SPMCSR, SPMIE_bp );                                           } break;
  case toIntNum(Interrupt::TIMER4_CAPTURE                 ): { util::clrBit(_TIMSK4, ICIE4_bp );                                           } break;
  case toIntNum(Interrupt::TIMER4_COMPARE_A               ): { util::clrBit(_TIMSK4, OCIE4A_bp);                                           } break;
  case toIntNum(Interrupt::TIMER4_COMPARE_B               ): { util::clrBit(_TIMSK4, OCIE4B_bp);                                           } break;
  case toIntNum(Interrupt::TIMER4_COMPARE_C               ): { util::clrBit(_TIMSK4, OCIE4C_bp);                                           } break;
  case toIntNum(Interrupt::TIMER4_OVERFLOW                ): { util::clrBit(_TIMSK4, TOIE4_bp );                                           } break;
  case toIntNum(Interrupt::TIMER5_CAPTURE                 ): { util::clrBit(_TIMSK5, ICIE5_bp );                                           } break;
  case toIntNum(Interrupt::TIMER5_COMPARE_A               ): { util::clrBit(_TIMSK5, OCIE5A_bp);                                           } break;
  case toIntNum(Interrupt::TIMER5_COMPARE_B               ): { util::clrBit(_TIMSK5, OCIE5B_bp);                                           } break;
  case toIntNum(Interrupt::TIMER5_COMPARE_C               ): { util::clrBit(_TIMSK5, OCIE5C_bp);                                           } break;
  case toIntNum(Interrupt::TIMER5_OVERFLOW                ): { util::clrBit(_TIMSK5, TOIE5_bp );                                           } break;
  case toIntNum(Interrupt::USART2_RECEIVE_COMPLETE        ): { util::clrBit(_UCSR2B, RXCIE2_bp);                                           } break;
  case toIntNum(Interrupt::USART2_UART_DATA_REGISTER_EMPTY): { util::clrBit(_UCSR2B, UDRIE2_bp);                                           } break;
  case toIntNum(Interrupt::USART2_TRANSMIT_COMPLETE       ): { util::clrBit(_UCSR2B, TXCIE2_bp);                                           } break;
  case toIntNum(Interrupt::USART3_RECEIVE_COMPLETE        ): { util::clrBit(_UCSR3B, RXCIE3_bp);                                           } break;
  case toIntNum(Interrupt::USART3_UART_DATA_REGISTER_EMPTY): { util::clrBit(_UCSR3B, UDRIE3_bp);                                           } break;
  case toIntNum(Interrupt::USART3_TRANSMIT_COMPLETE       ): { util::clrBit(_UCSR3B, TXCIE3_bp);                                           } break;
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                         ): asm volatile("cli");                                                            break;
#endif
  default                                                  : /* DO NOTHING */                                                                break;
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

} /* ATMEGA640_1280_2560 */

} /* hal */

} /* snowfox */

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

#if defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega2560) || defined(MCU_TYPE_atmega1280) || defined(MCU_TYPE_atmega640) )

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace snowfox::hal::interface;
using namespace snowfox::hal::ATMEGA640_1280_2560;

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

ISR(INT2_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::EXTERNAL_INT2)]);
}

ISR(INT3_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::EXTERNAL_INT3)]);
}

ISR(INT4_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::EXTERNAL_INT4)]);
}

ISR(INT5_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::EXTERNAL_INT5)]);
}

ISR(INT6_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::EXTERNAL_INT6)]);
}

ISR(INT7_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::EXTERNAL_INT7)]);
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
  executeCallbackIfValid(isr[toIntNum(Interrupt::PIN_CHANGE_INT15)]);
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

ISR(TIMER1_COMPC_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER1_COMPARE_C)]);
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

ISR(USART0_RX_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART0_RECEIVE_COMPLETE)]);
}

ISR(USART0_UDRE_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY)]);
}

ISR(USART0_TX_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE)]);
}

ISR(ANALOG_COMP_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::ANALOG_COMPARATOR)]);
}

ISR(ADC_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER)]);
}

ISR(EE_READY_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::EEPROM_READY)]);
}

ISR(TIMER3_CAPT_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER3_CAPTURE)]);
}

ISR(TIMER3_COMPA_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER3_COMPARE_A)]);
}

ISR(TIMER3_COMPB_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER3_COMPARE_B)]);
}

ISR(TIMER3_COMPC_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER3_COMPARE_C)]);
}

ISR(TIMER3_OVF_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER3_OVERFLOW)]);
}

ISR(USART1_RX_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART1_RECEIVE_COMPLETE)]);
}

ISR(USART1_UDRE_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY)]);
}

ISR(USART1_TX_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE)]);
}

ISR(TWI_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TWO_WIRE_INT)]);
}

ISR(SPM_READY_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::SPM_READY)]);
}

ISR(TIMER4_CAPT_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER4_CAPTURE)]);
}

ISR(TIMER4_COMPA_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER4_COMPARE_A)]);
}

ISR(TIMER4_COMPB_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER4_COMPARE_B)]);
}

ISR(TIMER4_COMPC_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER4_COMPARE_C)]);
}

ISR(TIMER4_OVF_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER4_OVERFLOW)]);
}

ISR(TIMER5_CAPT_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER5_CAPTURE)]);
}

ISR(TIMER5_COMPA_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER5_COMPARE_A)]);
}

ISR(TIMER5_COMPB_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER5_COMPARE_B)]);
}

ISR(TIMER5_COMPC_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER5_COMPARE_C)]);
}

ISR(TIMER5_OVF_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::TIMER5_OVERFLOW)]);
}

ISR(USART2_RX_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART2_RECEIVE_COMPLETE)]);
}

ISR(USART2_UDRE_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART2_UART_DATA_REGISTER_EMPTY)]);
}

ISR(USART2_TX_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART2_TRANSMIT_COMPLETE)]);
}

ISR(USART3_RX_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART3_RECEIVE_COMPLETE)]);
}

ISR(USART3_UDRE_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART3_UART_DATA_REGISTER_EMPTY)]);
}

ISR(USART3_TX_vect)
{
  executeCallbackIfValid(isr[toIntNum(Interrupt::USART3_TRANSMIT_COMPLETE)]);
}

#endif /* defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega2560) || defined(MCU_TYPE_atmega1280) || defined(MCU_TYPE_atmega640) ) */
