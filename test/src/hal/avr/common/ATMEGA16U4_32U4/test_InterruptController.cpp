/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation()(), either version 3 of the License()(), or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful()(),
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not()(), see <http://www.gnu.org/licenses/>.
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <sstream>

#include <catch2/catch.hpp>

#include <test/hal/avr/util/InterruptControllerTestUtil.h>

#include <snowfox/hal/avr/common/ATMEGA16U4_32U4/InterruptController.h>

#include <vireg/VirtualRegister.hpp>
#include <vireg/VirtualRegisterLoader.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace ATMEGA16U4_32U4
{

namespace test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("ATMEGA16U4_32U4::InterruptController - interrupts are enabled via 'enableInterrupt' and disabled via 'disableInterrupt'", "[ATMEGA16U4_32U4::InterruptController]")
{
  vireg::VirtualRegisterMap vregmap = vireg::VirtualRegisterLoader::load("json/hal/avr/ATMEGA16U4_32U4.json");

  vireg::Vireg8 EIMSK  = vregmap.get<vireg::Vireg8>("EIMSK" );
  vireg::Vireg8 PCICR  = vregmap.get<vireg::Vireg8>("PCICR" );
  vireg::Vireg8 PCMSK0 = vregmap.get<vireg::Vireg8>("PCMSK0");
  vireg::Vireg8 WDTCSR = vregmap.get<vireg::Vireg8>("WDTCSR");
  vireg::Vireg8 TIMSK0 = vregmap.get<vireg::Vireg8>("TIMSK0");
  vireg::Vireg8 TIMSK1 = vregmap.get<vireg::Vireg8>("TIMSK1");
  vireg::Vireg8 TIMSK3 = vregmap.get<vireg::Vireg8>("TIMSK3");
  vireg::Vireg8 TIMSK4 = vregmap.get<vireg::Vireg8>("TIMSK4");
  vireg::Vireg8 TCCR4D = vregmap.get<vireg::Vireg8>("TCCR4D");
  vireg::Vireg8 UCSR1B = vregmap.get<vireg::Vireg8>("UCSR1B");
  vireg::Vireg8 SPCR   = vregmap.get<vireg::Vireg8>("SPCR"  );
  vireg::Vireg8 TWCR   = vregmap.get<vireg::Vireg8>("TWCR"  );
  vireg::Vireg8 EECR   = vregmap.get<vireg::Vireg8>("EECR"  );
  vireg::Vireg8 SPMCSR = vregmap.get<vireg::Vireg8>("SPMCSR");
  vireg::Vireg8 ACSR   = vregmap.get<vireg::Vireg8>("ACSR"  );
  vireg::Vireg8 ADCSRA = vregmap.get<vireg::Vireg8>("ADCSRA");

  ATMEGA16U4_32U4::InterruptController int_ctrl(EIMSK->ptr (),
                                                PCICR->ptr (),
                                                PCMSK0->ptr(),
                                                WDTCSR->ptr(),
                                                TIMSK0->ptr(),
                                                TIMSK1->ptr(),
                                                TIMSK3->ptr(),
                                                TIMSK4->ptr(),
                                                TCCR4D->ptr(),
                                                UCSR1B->ptr(),
                                                SPCR->ptr  (),
                                                TWCR->ptr  (),
                                                EECR->ptr  (),
                                                SPMCSR->ptr(),
                                                ACSR->ptr  (),
                                                ADCSRA->ptr());

  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT0                  ), "EXTERNAL_INT0",                   *EIMSK,  0);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT1                  ), "EXTERNAL_INT1",                   *EIMSK,  1);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT2                  ), "EXTERNAL_INT2",                   *EIMSK,  2);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT3                  ), "EXTERNAL_INT3",                   *EIMSK,  3);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT6                  ), "EXTERNAL_INT6",                   *EIMSK,  6);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::WATCHDOG_TIMER                 ), "WATCHDOG_TIMER",                  *WDTCSR, 6);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_CAPTURE                 ), "TIMER1_CAPTURE",                  *TIMSK1, 5);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_COMPARE_A               ), "TIMER1_COMPARE_A",                *TIMSK1, 1);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_COMPARE_B               ), "TIMER1_COMPARE_B",                *TIMSK1, 2);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_COMPARE_C               ), "TIMER1_COMPARE_C",                *TIMSK1, 3);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_OVERFLOW                ), "TIMER1_OVERFLOW",                 *TIMSK1, 0);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER0_COMPARE_A               ), "TIMER0_COMPARE_A",                *TIMSK0, 1);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER0_COMPARE_B               ), "TIMER0_COMPARE_B",                *TIMSK0, 2);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER0_OVERFLOW                ), "TIMER0_OVERFLOW",                 *TIMSK0, 0);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   ), "SPI_SERIAL_TRANSFER_COMPLETE",    *SPCR,   7);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ), "USART1_RECEIVE_COMPLETE",         *UCSR1B, 7);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY), "USART1_UART_DATA_REGISTER_EMPTY", *UCSR1B, 5);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ), "USART1_TRANSMIT_COMPLETE",        *UCSR1B, 6);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::ANALOG_COMPARATOR              ), "ANALOG_COMPARATOR",               *ACSR,   3);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER       ), "ANALOG_DIGITAL_CONVERTER",        *ADCSRA, 3);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EEPROM_READY                   ), "EEPROM_READY",                    *EECR,   3);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_CAPTURE                 ), "TIMER3_CAPTURE",                  *TIMSK3, 5);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_COMPARE_A               ), "TIMER3_COMPARE_A",                *TIMSK3, 1);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_COMPARE_B               ), "TIMER3_COMPARE_B",                *TIMSK3, 2);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_COMPARE_C               ), "TIMER3_COMPARE_C",                *TIMSK3, 3);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_OVERFLOW                ), "TIMER3_OVERFLOW",                 *TIMSK3, 0);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TWO_WIRE_INT                   ), "TWO_WIRE_INT",                    *TWCR,   0);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::SPM_READY                      ), "SPM_READY",                       *SPMCSR, 7);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER4_COMPARE_A               ), "TIMER4_COMPARE_A",                *TIMSK4, 6);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER4_COMPARE_B               ), "TIMER4_COMPARE_B",                *TIMSK4, 5);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER4_COMPARE_D               ), "TIMER4_COMPARE_D",                *TIMSK4, 7);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER4_OVERFLOW                ), "TIMER4_OVERFLOW",                 *TIMSK4, 2);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER4_FAULT_PROTECTION        ), "TIMER4_FAULT_PROTECTION",         *TCCR4D, 7);

  avr::doTestEnableDisablePinChangeInterrupt(int_ctrl, toIntNum(Interrupt::PIN_CHANGE_INT0),  "PIN_CHANGE_INT0",  *PCICR, 0, "PCMSK0", *PCMSK0, 0);
  avr::doTestEnableDisablePinChangeInterrupt(int_ctrl, toIntNum(Interrupt::PIN_CHANGE_INT1),  "PIN_CHANGE_INT1",  *PCICR, 0, "PCMSK0", *PCMSK0, 1);
  avr::doTestEnableDisablePinChangeInterrupt(int_ctrl, toIntNum(Interrupt::PIN_CHANGE_INT2),  "PIN_CHANGE_INT2",  *PCICR, 0, "PCMSK0", *PCMSK0, 2);
  avr::doTestEnableDisablePinChangeInterrupt(int_ctrl, toIntNum(Interrupt::PIN_CHANGE_INT3),  "PIN_CHANGE_INT3",  *PCICR, 0, "PCMSK0", *PCMSK0, 3);
  avr::doTestEnableDisablePinChangeInterrupt(int_ctrl, toIntNum(Interrupt::PIN_CHANGE_INT4),  "PIN_CHANGE_INT4",  *PCICR, 0, "PCMSK0", *PCMSK0, 4);
  avr::doTestEnableDisablePinChangeInterrupt(int_ctrl, toIntNum(Interrupt::PIN_CHANGE_INT5),  "PIN_CHANGE_INT5",  *PCICR, 0, "PCMSK0", *PCMSK0, 5);
  avr::doTestEnableDisablePinChangeInterrupt(int_ctrl, toIntNum(Interrupt::PIN_CHANGE_INT6),  "PIN_CHANGE_INT6",  *PCICR, 0, "PCMSK0", *PCMSK0, 6);
  avr::doTestEnableDisablePinChangeInterrupt(int_ctrl, toIntNum(Interrupt::PIN_CHANGE_INT7),  "PIN_CHANGE_INT7",  *PCICR, 0, "PCMSK1", *PCMSK0, 7);
}

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

} /* test */

} /* ATMEGA16U4_32U4 */

} /* hal */

} /* snowfox */
