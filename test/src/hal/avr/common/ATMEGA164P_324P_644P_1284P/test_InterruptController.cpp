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

#include <hal/util/Register.hpp>

#include <hal/avr/common/ATMEGA164P_324P_644P_1284P/RegisterResetValueList.h>

#include <spectre/hal/avr/common/ATMEGA164P_324P_644P_1284P/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA164P_324P_644P_1284P
{

namespace test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("ATMEGA164P_324P_644P_1284P::InterruptController - interrupts are enabled via 'enableInterrupt' and disabled via 'disableInterrupt'", "[ATMEGA164P_324P_644P_1284P::InterruptController]")
{
  Register<uint8_t> EIMSK   (EIMSK_RESET_VALUE  ),
                    PCICR   (PCICR_RESET_VALUE  ),
                    WDTCSR  (WDTCSR_RESET_VALUE ),
                    TIMSK0  (TIMSK0_RESET_VALUE ),
                    TIMSK1  (TIMSK1_RESET_VALUE ),
                    TIMSK2  (TIMSK2_RESET_VALUE ),
                    UCSR0B  (UCSR0B_RESET_VALUE ),
                    UCSR1B  (UCSR1B_RESET_VALUE ),
                    SPCR    (SPCR_RESET_VALUE   ),
                    TWCR    (TWCR_RESET_VALUE   ),
                    EECR    (EECR_RESET_VALUE   ),
                    SPMCSR  (SPMCSR_RESET_VALUE ),
                    ACSR    (ACSR_RESET_VALUE   ),
                    ADCSRA  (ADCSRA_RESET_VALUE );

  ATMEGA164P_324P_644P_1284P::InterruptController int_ctrl(EIMSK (),
                                                           PCICR (),
                                                           WDTCSR(),
                                                           TIMSK0(),
                                                           TIMSK1(),
                                                           TIMSK2(),
                                                           UCSR0B(),
                                                           UCSR1B(),
                                                           SPCR  (),
                                                           TWCR  (),
                                                           EECR  (),
                                                           SPMCSR(),
                                                           ACSR  (),
                                                           ADCSRA());

}

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

} /* test */

} /* ATMEGA164P_324P_644P_1284P */

} /* hal */

} /* spectre */
