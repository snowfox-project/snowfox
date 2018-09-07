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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/blox/hal/avr/common/ATMEGA640_1280_2560/ExternalInterruptController.h>

#include <spectre/hal/avr/common/ATMEGA640_1280_2560/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

namespace ATMEGA640_1280_2560
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

ExternalInterruptController::ExternalInterruptController(volatile uint8_t                    * eicra,
                                                         volatile uint8_t                    * eicrb,
                                                         volatile uint8_t                    * pcmsk0,
                                                         volatile uint8_t                    * pcmsk1,
                                                         volatile uint8_t                    * pcmsk2,
                                                         hal::interface::InterruptController & int_ctrl)
: _ext_int_ctrl         (eicra, eicrb, pcmsk0, pcmsk1, pcmsk2, int_ctrl),
  _eint0_event_callback (_ext_int_ctrl),
  _eint1_event_callback (_ext_int_ctrl),
  _eint2_event_callback (_ext_int_ctrl),
  _eint3_event_callback (_ext_int_ctrl),
  _eint4_event_callback (_ext_int_ctrl),
  _eint5_event_callback (_ext_int_ctrl),
  _eint6_event_callback (_ext_int_ctrl),
  _eint7_event_callback (_ext_int_ctrl),
  _pcint0_event_callback(_ext_int_ctrl),
  _pcint1_event_callback(_ext_int_ctrl),
  _pcint2_event_callback(_ext_int_ctrl)
{
  int_ctrl.registerInterruptCallback(hal::ATMEGA640_1280_2560::toIntNum(hal::ATMEGA640_1280_2560::Interrupt::EXTERNAL_INT0  ), &_eint0_event_callback );
  int_ctrl.registerInterruptCallback(hal::ATMEGA640_1280_2560::toIntNum(hal::ATMEGA640_1280_2560::Interrupt::EXTERNAL_INT1  ), &_eint1_event_callback );
  int_ctrl.registerInterruptCallback(hal::ATMEGA640_1280_2560::toIntNum(hal::ATMEGA640_1280_2560::Interrupt::EXTERNAL_INT2  ), &_eint2_event_callback );
  int_ctrl.registerInterruptCallback(hal::ATMEGA640_1280_2560::toIntNum(hal::ATMEGA640_1280_2560::Interrupt::EXTERNAL_INT3  ), &_eint3_event_callback );
  int_ctrl.registerInterruptCallback(hal::ATMEGA640_1280_2560::toIntNum(hal::ATMEGA640_1280_2560::Interrupt::EXTERNAL_INT4  ), &_eint4_event_callback );
  int_ctrl.registerInterruptCallback(hal::ATMEGA640_1280_2560::toIntNum(hal::ATMEGA640_1280_2560::Interrupt::EXTERNAL_INT5  ), &_eint5_event_callback );
  int_ctrl.registerInterruptCallback(hal::ATMEGA640_1280_2560::toIntNum(hal::ATMEGA640_1280_2560::Interrupt::EXTERNAL_INT6  ), &_eint6_event_callback );
  int_ctrl.registerInterruptCallback(hal::ATMEGA640_1280_2560::toIntNum(hal::ATMEGA640_1280_2560::Interrupt::EXTERNAL_INT7  ), &_eint7_event_callback );
  int_ctrl.registerInterruptCallback(hal::ATMEGA640_1280_2560::toIntNum(hal::ATMEGA640_1280_2560::Interrupt::PIN_CHANGE_INT0), &_pcint0_event_callback);
  int_ctrl.registerInterruptCallback(hal::ATMEGA640_1280_2560::toIntNum(hal::ATMEGA640_1280_2560::Interrupt::PIN_CHANGE_INT1), &_pcint1_event_callback);
  int_ctrl.registerInterruptCallback(hal::ATMEGA640_1280_2560::toIntNum(hal::ATMEGA640_1280_2560::Interrupt::PIN_CHANGE_INT2), &_pcint2_event_callback);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA640_1280_2560 */

} /* blox */

} /* spectre */
