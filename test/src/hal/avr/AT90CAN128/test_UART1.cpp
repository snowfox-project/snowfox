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

#include <Register.h>
#include <hal/avr/AT90CAN128/RegisterResetValueList.h>

#include <spectre/hal/avr/AT90CAN128/UART1.h>
#include <spectre/hal/avr/AT90CAN128/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace AT90CAN128
{

namespace test
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t const F_CPU_Hz = F_CPU;

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("AT90CAN128::UART1 - TODO", "[AT90CAN128::UART1]")
{
  Register<uint8_t>  EIMSK  (EIMSK_RESET_VALUE  ),
                     TIMSK2 (TIMSK2_RESET_VALUE ),
                     TIMSK1 (TIMSK1_RESET_VALUE ),
                     TIMSK0 (TIMSK0_RESET_VALUE ),
                     CANGIE (CANGIE_RESET_VALUE ),
                     SPCR   (SPCR_RESET_VALUE   ),
                     UCSR0B (UCSR0B_RESET_VALUE ),
                     ACSR   (ACSR_RESET_VALUE   ),
                     ADCSRA (ADCSRA_RESET_VALUE ),
                     EECR   (EECR_RESET_VALUE   ),
                     TIMSK3 (TIMSK3_RESET_VALUE ),
                     UDR1   (UDR1_RESET_VALUE   ),
                     UCSR1A (UCSR1A_RESET_VALUE ),
                     UCSR1B (UCSR1B_RESET_VALUE ),
                     UCSR1C (UCSR1C_RESET_VALUE ),
                     TWCR   (TWCR_RESET_VALUE   ),
                     SPMCSR (SPMCSR_RESET_VALUE );
  Register<uint16_t> UBRR1  (UBRR1_RESET_VALUE  );

  AT90CAN128::InterruptController int_ctrl(EIMSK(), TIMSK2(), TIMSK1(), TIMSK0(), CANGIE(), SPCR(), UCSR0B(), ACSR(), ADCSRA(), EECR(), TIMSK3(), UCSR1B(), TWCR(), SPMCSR());
  AT90CAN128::UART1               uart1   (UDR1(), UCSR1A(), UCSR1B(), UCSR1C(), UBRR1(), int_ctrl, F_CPU_Hz);

  /* TODO */
}

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

} /* test */

} /* AT90CAN128 */

} /* hal */

} /* spectre */
