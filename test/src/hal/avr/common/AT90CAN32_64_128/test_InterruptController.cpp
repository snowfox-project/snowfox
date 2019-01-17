/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2019 Alexander Entinger / LXRobotics GmbH
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

#include <catch2/catch.hpp>

#include <testutil/hal/avr/InterruptControllerTestUtil.h>

#include <hal/avr/common/AT90CAN32_64_128/RegisterResetValueList.h>

#include <snowfox/hal/avr/common/AT90CAN32_64_128/InterruptController.h>
#include "../../../../../vireg/include/vireg/VirtualRegister.hpp"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace AT90CAN32_64_128
{

namespace test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("AT90CAN32_64_128::InterruptController - interrupts are enabled via 'enableInterrupt' and disabled via 'disableInterrupt'", "[AT90CAN32_64_128::InterruptController]")
{
  vireg::VirtualRegister<uint8_t> EIMSK   (EIMSK_RESET_VALUE , "EIMSK" ),
                    TIMSK2  (TIMSK2_RESET_VALUE, "TIMSK2"),
                    TIMSK1  (TIMSK1_RESET_VALUE, "TIMSK1"),
                    TIMSK0  (TIMSK0_RESET_VALUE, "TIMSK0"),
                    CANGIE  (CANGIE_RESET_VALUE, "CANGIE"),
                    SPCR    (SPCR_RESET_VALUE  , "SPCR"  ),
                    UCSR0B  (UCSR0B_RESET_VALUE, "UCSR0B"),
                    ACSR    (ACSR_RESET_VALUE  , "ACSR"  ),
                    ADCSRA  (ADCSRA_RESET_VALUE, "ADCSRA"),
                    EECR    (EECR_RESET_VALUE  , "EECR"  ),
                    TIMSK3  (TIMSK3_RESET_VALUE, "TIMSK3"),
                    UCSR1B  (UCSR1B_RESET_VALUE, "UCSR1B"),
                    TWCR    (TWCR_RESET_VALUE  , "TWCR"  ),
                    SPMCSR  (SPMCSR_RESET_VALUE, "SPMCSR");

  AT90CAN32_64_128::InterruptController int_ctrl(EIMSK (),
                                                 TIMSK0(),
                                                 TIMSK1(),
                                                 TIMSK2(),
                                                 TIMSK3(),
                                                 UCSR0B(),
                                                 UCSR1B(),
                                                 CANGIE(),
                                                 SPCR  (),
                                                 TWCR  (),
                                                 EECR  (),
                                                 SPMCSR(),
                                                 ACSR  (),
                                                 ADCSRA());

  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT0                  ), "EXTERNAL_INT0",                   EIMSK,  0);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT1                  ), "EXTERNAL_INT1",                   EIMSK,  1);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT2                  ), "EXTERNAL_INT2",                   EIMSK,  2);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT3                  ), "EXTERNAL_INT3",                   EIMSK,  3);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT4                  ), "EXTERNAL_INT4",                   EIMSK,  4);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT5                  ), "EXTERNAL_INT5",                   EIMSK,  5);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT6                  ), "EXTERNAL_INT6",                   EIMSK,  6);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT7                  ), "EXTERNAL_INT7",                   EIMSK,  7);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER2_COMPARE                 ), "TIMER2_COMPARE",                  TIMSK2, 1);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER2_OVERFLOW                ), "TIMER2_OVERFLOW",                 TIMSK2, 0);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_CAPTURE                 ), "TIMER1_CAPTURE",                  TIMSK1, 5);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_COMPARE_A               ), "TIMER1_COMPARE_A",                TIMSK1, 1);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_COMPARE_B               ), "TIMER1_COMPARE_B",                TIMSK1, 2);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_COMPARE_C               ), "TIMER1_COMPARE_C",                TIMSK1, 3);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_OVERFLOW                ), "TIMER1_OVERFLOW",                 TIMSK1, 0);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER0_COMPARE                 ), "TIMER0_COMPARE",                  TIMSK0, 1);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER0_OVERFLOW                ), "TIMER0_OVERFLOW",                 TIMSK0, 0);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::CAN_ALL                        ), "CAN_ALL",                         CANGIE, 7);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::CAN_TIMER_OVERRUN              ), "CAN_TIMER_OVERRUN",               CANGIE, 0);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   ), "SPI_SERIAL_TRANSFER_COMPLETE",    SPCR,   7);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART0_RECEIVE_COMPLETE        ), "USART0_RECEIVE_COMPLETE",         UCSR0B, 7);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY), "USART0_UART_DATA_REGISTER_EMPTY", UCSR0B, 5);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE       ), "USART0_TRANSMIT_COMPLETE",        UCSR0B, 6);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::ANALOG_COMPARATOR              ), "ANALOG_COMPARATOR",               ACSR,   3);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER       ), "ANALOG_DIGITAL_CONVERTER",        ADCSRA, 3);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EEPROM_READY                   ), "EEPROM_READY",                    EECR,   3);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_CAPTURE                 ), "TIMER3_CAPTURE",                  TIMSK3, 5);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_COMPARE_A               ), "TIMER3_COMPARE_A",                TIMSK3, 1);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_COMPARE_B               ), "TIMER3_COMPARE_B",                TIMSK3, 2);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_COMPARE_C               ), "TIMER3_COMPARE_C",                TIMSK3, 3);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_OVERFLOW                ), "TIMER3_OVERFLOW",                 TIMSK3, 0);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ), "USART1_RECEIVE_COMPLETE",         UCSR1B, 7);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY), "USART1_UART_DATA_REGISTER_EMPTY", UCSR1B, 5);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ), "USART1_TRANSMIT_COMPLETE",        UCSR1B, 6);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TWO_WIRE_INT                   ), "TWO_WIRE_INT",                    TWCR,   0);
  avr::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::SPM_READY                      ), "SPM_READY",                       SPMCSR, 7);
}

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

} /* test */

} /* AT90CAN32_64_128 */

} /* hal */

} /* snowfox */
