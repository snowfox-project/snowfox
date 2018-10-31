/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#include <catch.hpp>

#include <Register.h>

#include <hal/avr/common/AT90CAN32_64_128/RegisterResetValueList.h>

#include <spectre/hal/avr/common/AT90CAN32_64_128/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace AT90CAN32_64_128
{

namespace test
{

/**************************************************************************************
 * PROTOTYPE
 **************************************************************************************/

void doTestEnableDisableInterrupt(interface::InterruptController       & int_ctrl,
                                  uint8_t                        const   int_num,                  /* AT90CAN32_64_128::toIntNum(AT90CAN32_64_128::Interrupt::EXTERNAL_INT0) */
                                  std::string                    const & int_num_name,             /* "EXTERNAL_INT0"                                                        */
                                  Register<uint8_t>                    & int_mask_reg,             /* EIMSK                                                                  */
                                  std::string                    const & int_mask_reg_name,        /* "EIMSK"                                                                */
                                  uint8_t                        const   int_mask_reg_affected_bit /* 0                                                                      */

    )
{
  std::stringstream when_1_ss,
                    then_1_ss,
                    when_2_ss,
                    then_2_ss;

  when_1_ss << "Interrupt "
            << int_num_name
            << " is enabled via 'enableInterrupt'";
  then_1_ss << int_mask_reg_name
            << " bit #"
            << static_cast<size_t>(int_mask_reg_affected_bit)
            << " should be 'set'";
  when_2_ss << "Interrupt "
            << int_num_name
            << " is disabled via 'disableInterrupt'";
  then_2_ss << int_mask_reg_name
            << " bit #"
            << static_cast<size_t>(int_mask_reg_affected_bit)
            << "should be 'clr'";

  WHEN(when_1_ss.str())
  {
    int_ctrl.enableInterrupt(int_num);

    THEN(then_1_ss.str())
    {
      REQUIRE(int_mask_reg.isBitSet(int_mask_reg_affected_bit));

      WHEN(when_2_ss.str())
      {
        int_ctrl.disableInterrupt(int_num);

        THEN(then_2_ss.str())
        {
          REQUIRE(int_mask_reg.isBitClr(int_mask_reg_affected_bit));
        }
      }
    }
  }
}

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("AT90CAN32_64_128::InterruptController - interrupts are enabled via 'enableInterrupt' and disabled via 'disableInterrupt'", "[AT90CAN32_64_128::InterruptController]")
{
  Register<uint8_t> EIMSK   (EIMSK_RESET_VALUE  ),
                    TIMSK2  (TIMSK2_RESET_VALUE ),
                    TIMSK1  (TIMSK1_RESET_VALUE ),
                    TIMSK0  (TIMSK0_RESET_VALUE ),
                    CANGIE  (CANGIE_RESET_VALUE ),
                    SPCR    (SPCR_RESET_VALUE   ),
                    UCSR0B  (UCSR0B_RESET_VALUE ),
                    ACSR    (ACSR_RESET_VALUE   ),
                    ADCSRA  (ADCSRA_RESET_VALUE ),
                    EECR    (EECR_RESET_VALUE   ),
                    TIMSK3  (TIMSK3_RESET_VALUE ),
                    UCSR1B  (UCSR1B_RESET_VALUE ),
                    TWCR    (TWCR_RESET_VALUE   ),
                    SPMCSR  (SPMCSR_RESET_VALUE );

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


  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT0                  ), "EXTERNAL_INT0",                   EIMSK,  "EIMSK",  0);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT1                  ), "EXTERNAL_INT1",                   EIMSK,  "EIMSK",  1);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT2                  ), "EXTERNAL_INT2",                   EIMSK,  "EIMSK",  2);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT3                  ), "EXTERNAL_INT3",                   EIMSK,  "EIMSK",  3);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT4                  ), "EXTERNAL_INT4",                   EIMSK,  "EIMSK",  4);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT5                  ), "EXTERNAL_INT5",                   EIMSK,  "EIMSK",  5);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT6                  ), "EXTERNAL_INT6",                   EIMSK,  "EIMSK",  6);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT7                  ), "EXTERNAL_INT7",                   EIMSK,  "EIMSK",  7);

  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER2_COMPARE                 ), "TIMER2_COMPARE",                  TIMSK2, "TIMSK2", 1);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER2_OVERFLOW                ), "TIMER2_OVERFLOW",                 TIMSK2, "TIMSK2", 0);

  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_CAPTURE                 ), "TIMER1_CAPTURE",                  TIMSK1, "TIMSK1", 5);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_COMPARE_A               ), "TIMER1_COMPARE_A",                TIMSK1, "TIMSK1", 1);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_COMPARE_B               ), "TIMER1_COMPARE_B",                TIMSK1, "TIMSK1", 2);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_COMPARE_C               ), "TIMER1_COMPARE_C",                TIMSK1, "TIMSK1", 3);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_OVERFLOW                ), "TIMER1_OVERFLOW",                 TIMSK1, "TIMSK1", 0);

  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER0_COMPARE                 ), "TIMER0_COMPARE",                  TIMSK0, "TIMSK0", 1);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER0_OVERFLOW                ), "TIMER0_OVERFLOW",                 TIMSK0, "TIMSK0", 0);

  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::CAN_ALL                        ), "CAN_ALL",                         CANGIE, "CANGIE", 7);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::CAN_BUS_OFF                    ), "CAN_BUS_OFF",                     CANGIE, "CANGIE", 6);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::CAN_RECEIVE                    ), "CAN_RECEIVE",                     CANGIE, "CANGIE", 5);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::CAN_TRANSMIT                   ), "CAN_TRANSMIT",                    CANGIE, "CANGIE", 4);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::CAN_FRAME_BUFFER               ), "CAN_FRAME_BUFFER",                CANGIE, "CANGIE", 2);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::CAN_GENERAL_ERROR              ), "CAN_GENERAL_ERROR",               CANGIE, "CANGIE", 1);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::CAN_TIMER_OVERRUN              ), "CAN_TIMER_OVERRUN",               CANGIE, "CANGIE", 0);

  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   ), "SPI_SERIAL_TRANSFER_COMPLETE",    SPCR,   "SPCR",   7);

  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART0_RECEIVE_COMPLETE        ), "USART0_RECEIVE_COMPLETE",         UCSR0B, "UCSR0B", 7);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY), "USART0_UART_DATA_REGISTER_EMPTY", UCSR0B, "UCSR0B", 5);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE       ), "USART0_TRANSMIT_COMPLETE",        UCSR0B, "UCSR0B", 6);

  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::ANALOG_COMPARATOR              ), "ANALOG_COMPARATOR",               ACSR,   "ACSR",   3);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER       ), "ANALOG_DIGITAL_CONVERTER",        ADCSRA, "ADCSRA", 3);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EEPROM_READY                   ), "EEPROM_READY",                    EECR,   "EECR",   3);

  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_CAPTURE                 ), "TIMER3_CAPTURE",                  TIMSK3, "TIMSK3", 5);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_COMPARE_A               ), "TIMER3_COMPARE_A",                TIMSK3, "TIMSK3", 1);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_COMPARE_B               ), "TIMER3_COMPARE_B",                TIMSK3, "TIMSK3", 2);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_COMPARE_C               ), "TIMER3_COMPARE_C",                TIMSK3, "TIMSK3", 3);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_OVERFLOW                ), "TIMER3_OVERFLOW",                 TIMSK3, "TIMSK3", 0);

  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ), "USART1_RECEIVE_COMPLETE",         UCSR1B, "UCSR1B", 7);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY), "USART1_UART_DATA_REGISTER_EMPTY", UCSR1B, "UCSR1B", 5);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ), "USART1_TRANSMIT_COMPLETE",        UCSR1B, "UCSR1B", 6);

  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TWO_WIRE_INT                   ), "TWO_WIRE_INT",                    TWCR,   "TWCR",   0);
  doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::SPM_READY                      ), "SPM_READY",                       SPMCSR, "SPMCSR", 7);

}

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

} /* test */

} /* AT90CAN32_64_128 */

} /* hal */

} /* spectre */
