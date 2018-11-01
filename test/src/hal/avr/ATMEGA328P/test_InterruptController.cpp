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

#include <hal/util/Register.h>
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
  Register<uint8_t> EIMSK   (EIMSK_RESET_VALUE  ),
                    PCICR   (PCICR_RESET_VALUE  ),
                    WDTCSR  (WDTCSR_RESET_VALUE ),
                    TIMSK0  (TIMSK0_RESET_VALUE ),
                    TIMSK1  (TIMSK1_RESET_VALUE ),
                    TIMSK2  (TIMSK2_RESET_VALUE ),
                    UCSR0B  (UCSR0B_RESET_VALUE ),
                    SPCR    (SPCR_RESET_VALUE   ),
                    TWCR    (TWCR_RESET_VALUE   ),
                    EECR    (EECR_RESET_VALUE   ),
                    SPMCSR  (SPMCSR_RESET_VALUE ),
                    ACSR    (ACSR_RESET_VALUE   ),
                    ADCSRA  (ADCSRA_RESET_VALUE );

  ATMEGA328P::InterruptController int_ctrl(EIMSK(), PCICR(), WDTCSR(), TIMSK0(), TIMSK1(), TIMSK2(), UCSR0B(), SPCR(), TWCR(), EECR(), SPMCSR(), ACSR(), ADCSRA());

  /************************************************************************************/

  WHEN("Interrupt EXTERNAL_INT0 is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::EXTERNAL_INT0));
    THEN("EIMSK bit #0 should be set")
    {
      REQUIRE(EIMSK.isBitSet(0));
      WHEN("Interrupt EXTERNAL_INT0 is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::EXTERNAL_INT0));
        THEN("EIMSK bit #0 should be clr")
        {
          REQUIRE(EIMSK.isBitClr(0));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt EXTERNAL_INT1 is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::EXTERNAL_INT1));
    THEN("EIMSK bit #1 should be set")
    {
      REQUIRE(EIMSK.isBitSet(1));
      WHEN("Interrupt EXTERNAL_INT1 is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::EXTERNAL_INT1));
        THEN("EIMSK bit #1 should be clr")
        {
          REQUIRE(EIMSK.isBitClr(1));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt PIN_CHANGE_INT0 is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::PIN_CHANGE_INT0));
    THEN("PCICR bit #0 should be set")
    {
      REQUIRE(PCICR.isBitSet(0));
      WHEN("Interrupt PIN_CHANGE_INT0 is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::PIN_CHANGE_INT0));
        THEN("PCICR bit #0 should be clr")
        {
          REQUIRE(PCICR.isBitClr(0));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt PIN_CHANGE_INT1 is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::PIN_CHANGE_INT1));
    THEN("PCICR bit #1 should be set")
    {
      REQUIRE(PCICR.isBitSet(1));
      WHEN("Interrupt PIN_CHANGE_INT1 is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::PIN_CHANGE_INT1));
        THEN("PCICR bit #1 should be clr")
        {
          REQUIRE(PCICR.isBitClr(1));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt PIN_CHANGE_INT2 is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::PIN_CHANGE_INT2));
    THEN("PCICR bit #2 should be set")
    {
      REQUIRE(PCICR.isBitSet(2));
      WHEN("Interrupt PIN_CHANGE_INT2 is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::PIN_CHANGE_INT2));
        THEN("PCICR bit #2 should be clr")
        {
          REQUIRE(PCICR.isBitClr(2));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt WATCHDOG_TIMER is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::WATCHDOG_TIMER));
    THEN("WDTCSR bit #6 should be set")
    {
      REQUIRE(WDTCSR.isBitSet(6));
      WHEN("Interrupt WATCHDOG_TIMER is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::WATCHDOG_TIMER));
        THEN("WDTCSR bit #6 should be clr")
        {
          REQUIRE(WDTCSR.isBitClr(6));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt TIMER2_COMPARE_A is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER2_COMPARE_A));
    THEN("TIMSK2 bit #1 should be set")
    {
      REQUIRE(TIMSK2.isBitSet(1));
      WHEN("Interrupt TIMER2_COMPARE_A is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER2_COMPARE_A));
        THEN("TIMSK2 bit #1 should be clr")
        {
          REQUIRE(TIMSK2.isBitClr(1));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt TIMER2_COMPARE_B is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER2_COMPARE_B));
    THEN("TIMSK2 bit #2 should be set")
    {
      REQUIRE(TIMSK2.isBitSet(2));
      WHEN("Interrupt TIMER2_COMPARE_B is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER2_COMPARE_B));
        THEN("TIMSK2 bit #2 should be clr")
        {
          REQUIRE(TIMSK2.isBitClr(2));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt TIMER2_OVERFLOW is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER2_OVERFLOW));
    THEN("TIMSK2 bit #0 should be set")
    {
      REQUIRE(TIMSK2.isBitSet(0));
      WHEN("Interrupt TIMER2_OVERFLOW is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER2_OVERFLOW));
        THEN("TIMSK2 bit #0 should be clr")
        {
          REQUIRE(TIMSK2.isBitClr(0));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt TIMER1_CAPTURE is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER1_CAPTURE));
    THEN("TIMSK1 bit #5 should be set")
    {
      REQUIRE(TIMSK1.isBitSet(5));
      WHEN("Interrupt TIMER1_CAPTURE is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER1_CAPTURE));
        THEN("TIMSK1 bit #5 should be clr")
        {
          REQUIRE(TIMSK1.isBitClr(5));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt TIMER1_COMPARE_A is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER1_COMPARE_A));
    THEN("TIMSK1 bit #1 should be set")
    {
      REQUIRE(TIMSK1.isBitSet(1));
      WHEN("Interrupt TIMER1_COMPARE_A is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER1_COMPARE_A));
        THEN("TIMSK1 bit #1 should be clr")
        {
          REQUIRE(TIMSK1.isBitClr(1));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt TIMER1_COMPARE_B is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER1_COMPARE_B));
    THEN("TIMSK1 bit #2 should be set")
    {
      REQUIRE(TIMSK1.isBitSet(2));
      WHEN("Interrupt TIMER1_COMPARE_B is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER1_COMPARE_B));
        THEN("TIMSK1 bit #2 should be clr")
        {
          REQUIRE(TIMSK1.isBitClr(2));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt TIMER1_OVERFLOW is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER1_OVERFLOW));
    THEN("TIMSK1 bit #0 should be set")
    {
      REQUIRE(TIMSK1.isBitSet(0));
      WHEN("Interrupt TIMER1_OVERFLOW is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER1_OVERFLOW));
        THEN("TIMSK1 bit #0 should be clr")
        {
          REQUIRE(TIMSK1.isBitClr(0));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt TIMER0_COMPARE_A is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER0_COMPARE_A));
    THEN("TIMSK0 bit #1 should be set")
    {
      REQUIRE(TIMSK0.isBitSet(1));
      WHEN("Interrupt TIMER0_COMPARE_A is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER0_COMPARE_A));
        THEN("TIMSK0 bit #1 should be clr")
        {
          REQUIRE(TIMSK0.isBitClr(1));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt TIMER0_COMPARE_B is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER0_COMPARE_B));
    THEN("TIMSK0 bit #2 should be set")
    {
      REQUIRE(TIMSK0.isBitSet(2));
      WHEN("Interrupt TIMER0_COMPARE_B is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER0_COMPARE_B));
        THEN("TIMSK0 bit #2 should be clr")
        {
          REQUIRE(TIMSK0.isBitClr(2));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt TIMER0_OVERFLOW is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER0_OVERFLOW));
    THEN("TIMSK0 bit #0 should be set")
    {
      REQUIRE(TIMSK0.isBitSet(0));
      WHEN("Interrupt TIMER2_OVERFLOW is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TIMER0_OVERFLOW));
        THEN("TIMSK0 bit #0 should be clr")
        {
          REQUIRE(TIMSK0.isBitClr(0));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt SPI_SERIAL_TRANSFER_COMPLETE is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::SPI_SERIAL_TRANSFER_COMPLETE));
    THEN("SPCR bit #7 should be set")
    {
      REQUIRE(SPCR.isBitSet(7));
      WHEN("Interrupt SPI_SERIAL_TRANSFER_COMPLETE is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::SPI_SERIAL_TRANSFER_COMPLETE));
        THEN("SPCR bit #7 should be clr")
        {
          REQUIRE(SPCR.isBitClr(7));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt USART_RECEIVE_COMPLETE is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::USART_RECEIVE_COMPLETE));
    THEN("UCSR0B bit #7 should be set")
    {
      REQUIRE(UCSR0B.isBitSet(7));
      WHEN("Interrupt USART_RECEIVE_COMPLETE is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::USART_RECEIVE_COMPLETE));
        THEN("UCSR0B bit #7 should be clr")
        {
          REQUIRE(UCSR0B.isBitClr(7));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt USART_UART_DATA_REGISTER_EMPTY is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::USART_UART_DATA_REGISTER_EMPTY));
    THEN("UCSR0B bit #5 should be set")
    {
      REQUIRE(UCSR0B.isBitSet(5));
      WHEN("Interrupt USART_UART_DATA_REGISTER_EMPTY is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::USART_UART_DATA_REGISTER_EMPTY));
        THEN("UCSR0B bit #5 should be clr")
        {
          REQUIRE(UCSR0B.isBitClr(5));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt USART_TRANSMIT_COMPLETE is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::USART_TRANSMIT_COMPLETE));
    THEN("UCSR0B bit #6 should be set")
    {
      REQUIRE(UCSR0B.isBitSet(6));
      WHEN("Interrupt USART_TRANSMIT_COMPLETE is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::USART_TRANSMIT_COMPLETE));
        THEN("UCSR0B bit #6 should be clr")
        {
          REQUIRE(UCSR0B.isBitClr(6));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt ANALOG_DIGITAL_CONVERTER is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::ANALOG_DIGITAL_CONVERTER));
    THEN("ADCSRA bit #3 should be set")
    {
      REQUIRE(ADCSRA.isBitSet(3));
      WHEN("Interrupt ANALOG_DIGITAL_CONVERTER is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::ANALOG_DIGITAL_CONVERTER));
        THEN("ADCSRA bit #3 should be clr")
        {
          REQUIRE(ADCSRA.isBitClr(3));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt EEPROM_READY is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::EEPROM_READY));
    THEN("EECR bit #3 should be set")
    {
      REQUIRE(EECR.isBitSet(3));
      WHEN("Interrupt EEPROM_READY is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::EEPROM_READY));
        THEN("EECR bit #3 should be clr")
        {
          REQUIRE(EECR.isBitClr(3));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt ANALOG_COMPARATOR is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::ANALOG_COMPARATOR));
    THEN("ACSR bit #3 should be set")
    {
      REQUIRE(ACSR.isBitSet(3));
      WHEN("Interrupt ANALOG_COMPARATOR is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::ANALOG_COMPARATOR));
        THEN("ACSR bit #3 should be clr")
        {
          REQUIRE(ACSR.isBitClr(3));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt TWO_WIRE_INT is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TWO_WIRE_INT));
    THEN("TWCR bit #0 should be set")
    {
      REQUIRE(TWCR.isBitSet(0));
      WHEN("Interrupt TWO_WIRE_INT is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::TWO_WIRE_INT));
        THEN("TWCR bit #0 should be clr")
        {
          REQUIRE(TWCR.isBitClr(0));
        }
      }
    }
  }

  /************************************************************************************/

  WHEN("Interrupt SPM_READY is enabled via 'enableInterrupt")
  {
    int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::SPM_READY));
    THEN("SPMCSR bit #7 should be set")
    {
      REQUIRE(SPMCSR.isBitSet(7));
      WHEN("Interrupt SPM_READY is disabled via 'disableInterrupt")
      {
        int_ctrl.disableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::SPM_READY));
        THEN("SPMCSR bit #7 should be clr")
        {
          REQUIRE(SPMCSR.isBitClr(7));
        }
      }
    }
  }

}

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

} /* test */

} /* ATMEGA328P */

} /* hal */

} /* spectre */
