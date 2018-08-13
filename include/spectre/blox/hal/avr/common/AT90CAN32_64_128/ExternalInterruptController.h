/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_AT90CAN32_64_128_EXTERNALINTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_AT90CAN32_64_128_EXTERNALINTERRUPTCONTROLLER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/AT90CAN32_64_128/ExternalInterruptController.h>

#include <spectre/hal/interface/interrupt/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

namespace AT90CAN32_64_128
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

class ExternalInterruptController
{

public:

  ExternalInterruptController(volatile uint8_t                    * eicra,
                              volatile uint8_t                    * eicrb,
                              hal::interface::InterruptController & int_ctrl);


  hal::AT90CAN32_64_128::ExternalInterruptController & operator () () { return _ext_int_ctrl; }


private:

  hal::AT90CAN32_64_128::ExternalInterruptController          _ext_int_ctrl;
  hal::AT90CAN32_64_128::EINT0_ExternalInterruptEventCallback _eint0_event_callback;
  hal::AT90CAN32_64_128::EINT1_ExternalInterruptEventCallback _eint1_event_callback;
  hal::AT90CAN32_64_128::EINT2_ExternalInterruptEventCallback _eint2_event_callback;
  hal::AT90CAN32_64_128::EINT3_ExternalInterruptEventCallback _eint3_event_callback;
  hal::AT90CAN32_64_128::EINT4_ExternalInterruptEventCallback _eint4_event_callback;
  hal::AT90CAN32_64_128::EINT5_ExternalInterruptEventCallback _eint5_event_callback;
  hal::AT90CAN32_64_128::EINT6_ExternalInterruptEventCallback _eint6_event_callback;
  hal::AT90CAN32_64_128::EINT7_ExternalInterruptEventCallback _eint7_event_callback;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN32_64_128 */

} /* blox */

} /* spectre */

#endif /* INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_AT90CAN32_64_128_EXTERNALINTERRUPTCONTROLLER_H_ */
