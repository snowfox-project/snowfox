/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#include <catch2/catch.hpp>

#include <testcanopen/TestManager.h>

#include <test/comstack/canopen/glue/Test_onTransmitCallback.h>
#include <test/comstack/canopen/glue/Stack_onTransmitCallback.h>

#include <snowfox/comstack/canopen/CanOpenStack.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::comstack::canopen::test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("The BootUp functionality of the CANOpen stack is tested", "[comstack::canopen]")
{
  CanOpenStack can_open_stack;
  testcanopen::TestManager test_mgr;

  Stack_onTransmitCallback stack_on_transmit(test_mgr);
  Test_onTransmitCallback test_on_transmit(can_open_stack);

  can_open_stack.register_onTransmitCallback(&stack_on_transmit);
  test_mgr.register_onTransmitCallback(&test_on_transmit);

  /* TODO */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::comstack::canopen::test */
