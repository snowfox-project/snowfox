/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation(), either version 3 of the License(), or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful(),
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not(), see <http://www.gnu.org/licenses/>.
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <catch.hpp>

#include <testutil/hal/Register.hpp>
#include <hal/avr/util/InterruptControllerTestUtil.h>

#include <hal/avr/ATMEGA328P/RegisterResetValueList.h>

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

namespace test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("ATMEGA328P::InterruptController - interrupts are enabled via 'enableInterrupt' and disabled via 'clrInterrupt'", "[ATMEGA328P::InterruptController]")
{
  Register<uint8_t> EIMSK   (EIMSK_RESET_VALUE , "EIMSK" ),
                    PCICR   (PCICR_RESET_VALUE , "PCICR" ),
                    WDTCSR  (WDTCSR_RESET_VALUE, "WDTCSR"),
                    TIMSK0  (TIMSK0_RESET_VALUE, "TIMSK0"),
                    TIMSK1  (TIMSK1_RESET_VALUE, "TIMSK1"),
                    TIMSK2  (TIMSK2_RESET_VALUE, "TIMSK2"),
                    UCSR0B  (UCSR0B_RESET_VALUE, "UCSR0B"),
                    SPCR    (SPCR_RESET_VALUE  , "SPCR"  ),
                    TWCR    (TWCR_RESET_VALUE  , "TWCR"  ),
                    EECR    (EECR_RESET_VALUE  , "EECR"  ),
                    SPMCSR  (SPMCSR_RESET_VALUE, "SPMCSR"),
                    ACSR    (ACSR_RESET_VALUE  , "ACSR"  ),
                    ADCSRA  (ADCSRA_RESET_VALUE, "ADCSRA");

  ATMEGA328P::InterruptController int_ctrl(EIMSK (),
                                           PCICR (),
                                           WDTCSR(),
                                           TIMSK0(),
                                           TIMSK1(),
                                           TIMSK2(),
                                           UCSR0B(),
                                           SPCR  (),
                                           TWCR  (),
                                           EECR  (),
                                           SPMCSR(),
                                           ACSR  (),
                                           ADCSRA());

  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT0                 ), "EXTERNAL_INT0",                  EIMSK,  0);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT1                 ), "EXTERNAL_INT1",                  EIMSK,  1);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::PIN_CHANGE_INT0               ), "PIN_CHANGE_INT0",                PCICR,  0);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::PIN_CHANGE_INT1               ), "PIN_CHANGE_INT1",                PCICR,  1);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::PIN_CHANGE_INT2               ), "PIN_CHANGE_INT2",                PCICR,  2);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::WATCHDOG_TIMER                ), "WATCHDOG_TIMER",                 WDTCSR, 6);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER2_COMPARE_A              ), "TIMER2_COMPARE_A",               TIMSK2, 1);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER2_COMPARE_B              ), "TIMER2_COMPARE_B",               TIMSK2, 2);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER2_OVERFLOW               ), "TIMER2_OVERFLOW",                TIMSK2, 0);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_CAPTURE                ), "TIMER1_CAPTURE",                 TIMSK1, 5);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_COMPARE_A              ), "TIMER1_COMPARE_A",               TIMSK1, 1);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_COMPARE_B              ), "TIMER1_COMPARE_B",               TIMSK1, 2);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_OVERFLOW               ), "TIMER1_OVERFLOW",                TIMSK1, 0);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER0_COMPARE_A              ), "TIMER0_COMPARE_A",               TIMSK0, 1);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER0_COMPARE_B              ), "TIMER0_COMPARE_B",               TIMSK0, 2);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER0_OVERFLOW               ), "TIMER0_OVERFLOW",                TIMSK0, 0);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE  ), "SPI_SERIAL_TRANSFER_COMPLETE",   SPCR,   7);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART_RECEIVE_COMPLETE        ), "USART_RECEIVE_COMPLETE",         UCSR0B, 7);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART_UART_DATA_REGISTER_EMPTY), "USART_UART_DATA_REGISTER_EMPTY", UCSR0B, 5);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART_TRANSMIT_COMPLETE       ), "USART_TRANSMIT_COMPLETE",        UCSR0B, 6);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::ANALOG_COMPARATOR             ), "ANALOG_COMPARATOR",              ACSR,   3);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER      ), "ANALOG_DIGITAL_CONVERTER",       ADCSRA, 3);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EEPROM_READY                  ), "EEPROM_READY",                   EECR,   3);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TWO_WIRE_INT                  ), "TWO_WIRE_INT",                   TWCR,   0);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::SPM_READY                     ), "SPM_READY",                      SPMCSR, 7);

}

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

} /* test */

} /* ATMEGA328P */

} /* hal */

} /* spectre */
