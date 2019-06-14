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

#include <test/hal/avr/util/InterruptControllerTestUtil.h>

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
                                  vireg::VirtualRegister<uint8_t>      & int_mask_reg,               /* EIMSK                                                                  */
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

void doTestEnableDisablePinChangeInterrupt(interface::InterruptController       & int_ctrl,
                                           uint8_t                        const   pcint_num,              // AT90CAN32_64_128::toIntNum(AT90CAN32_64_128::Interrupt::PIN_CHANGE_INT0)
                                           std::string                    const & pcint_name,             // "PIN_CHANGE_INT0
                                           vireg::VirtualRegister<uint8_t>      & pcicr_reg,              // PCICR
                                           uint8_t                        const   pcicr_reg_affected_bit,
                                           std::string                    const & pcmskx_name,            // "PCMSK0"
                                           vireg::VirtualRegister<uint8_t>      & pcmskx_reg,             // PCMSK0
                                           uint8_t                        const   pcmskx_reg_affected_bit)
{
  std::stringstream when_1_ss, then_1a_ss, then_1b_ss,
                    when_2_ss, then_2a_ss, then_2b_ss;

  when_1_ss  << pcint_name << " is enabled via 'enableInterrupt'";
  then_1a_ss << "PCICR bit #" << static_cast<size_t>(pcicr_reg_affected_bit) << " should be 'set'";
  then_1b_ss << pcmskx_name << " bit #" << static_cast<size_t>(pcmskx_reg_affected_bit) << " should be 'set'";
  when_2_ss << pcint_name << " is disabled via 'disableInterrupt'";
  then_2a_ss << "PCICR bit #" << static_cast<size_t>(pcicr_reg_affected_bit) << " should be 'clr'";
  then_2b_ss << pcmskx_name << " bit #" << static_cast<size_t>(pcmskx_reg_affected_bit) << " should be 'set'";
  
  WHEN(when_1_ss.str())
  {
    int_ctrl.enableInterrupt(pcint_num);
    THEN(then_1a_ss.str()) { REQUIRE(pcicr_reg.isBitSet (pcicr_reg_affected_bit )); }
    THEN(then_1b_ss.str()) { REQUIRE(pcmskx_reg.isBitSet(pcmskx_reg_affected_bit)); }
    WHEN(when_2_ss.str())
    {
      int_ctrl.disableInterrupt(pcint_num);
      THEN(then_2a_ss.str()) { REQUIRE(pcicr_reg.isBitSet (pcicr_reg_affected_bit )); }
      THEN(then_2b_ss.str()) { REQUIRE(pcmskx_reg.isBitClr(pcmskx_reg_affected_bit)); }
    }
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* avr */

} /* hal */

} /* snowfox */
