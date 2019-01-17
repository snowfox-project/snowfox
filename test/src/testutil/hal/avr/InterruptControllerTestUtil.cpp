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

#include <testutil/hal/avr/InterruptControllerTestUtil.h>

#include <sstream>

#include <catch2/catch.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace avr
{

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

void doTestEnableDisableInterrupt(interface::InterruptController       & int_ctrl,
                                  uint8_t                        const   int_num,                    /* AT90CAN32_64_128::toIntNum(AT90CAN32_64_128::Interrupt::EXTERNAL_INT0) */
                                  std::string                    const & int_num_name,               /* "EXTERNAL_INT0"                                                        */
                                  vireg::VirtualRegister<uint8_t>                    & int_mask_reg,               /* EIMSK                                                                  */
                                  uint8_t                        const   int_mask_reg_affected_bit)
{
  std::stringstream when_1_ss,
                    then_1_ss,
                    when_2_ss,
                    then_2_ss;

  when_1_ss << "Interrupt "
            << int_num_name
            << " is enabled via 'enableInterrupt'";
  then_1_ss << int_mask_reg.name()
            << " bit #"
            << static_cast<size_t>(int_mask_reg_affected_bit)
            << " should be 'set'";
  when_2_ss << "Interrupt "
            << int_num_name
            << " is disabled via 'disableInterrupt'";
  then_2_ss << int_mask_reg.name()
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
 * NAMESPACE
 **************************************************************************************/

} /* avr */

} /* hal */

} /* snowfox */
