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

#ifndef TEST_INCLUDE_HAL_AVR_UTIL_INTERRUPTCONTROLLERTESTUTIL_H_
#define TEST_INCLUDE_HAL_AVR_UTIL_INTERRUPTCONTROLLERTESTUTIL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <string>

#include <snowfox/hal/interface/interrupt/InterruptController.h>

#include <testutil/Register.hpp>

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
 * PROTOTYPES
 **************************************************************************************/

void doTestEnableDisableInterrupt(interface::InterruptController       & int_ctrl,
                                  uint8_t                        const   int_num,                    /* AT90CAN32_64_128::toIntNum(AT90CAN32_64_128::Interrupt::EXTERNAL_INT0) */
                                  std::string                    const & int_num_name,               /* "EXTERNAL_INT0"                                                        */
                                  Register<uint8_t>                    & int_mask_reg,               /* EIMSK                                                                  */
                                  uint8_t                        const   int_mask_reg_affected_bit); /* 0                                                                      */

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* avr */

} /* hal */

} /* snowfox */

#endif /* TEST_INCLUDE_HAL_AVR_UTIL_INTERRUPTCONTROLLERTESTUTIL_H_ */
