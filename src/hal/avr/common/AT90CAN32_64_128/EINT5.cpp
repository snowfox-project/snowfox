/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 Alexander Entinger / LXRobotics GmbH
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

#include <spectre/hal/avr/common/AT90CAN32_64_128/EINT5.h>

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

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* EICRA */
#define ISC51_bm (1<<3)
#define ISC50_bm (1<<2)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

EINT5::EINT5(volatile uint8_t * eicrb, interface::InterruptController & int_ctrl)
: _EICRB                      (eicrb   ),
  _int_ctrl                   (int_ctrl),
  _external_interrupt_callback(0       )
{

}

EINT5::~EINT5()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void EINT5::setTriggerMode(interface::TriggerMode const trigger_mode)
{
  *_EICRB &= ~(ISC51_bm | ISC50_bm);

  switch(trigger_mode)
  {
  case interface::TriggerMode::Any        : *_EICRB |=            ISC50_bm; break;
  case interface::TriggerMode::Low        : *_EICRB |= 0;                   break;
  case interface::TriggerMode::High       : /* Not supported */             break;
  case interface::TriggerMode::RisingEdge : *_EICRB |= ISC51_bm | ISC50_bm; break;
  case interface::TriggerMode::FallingEdge: *_EICRB |= ISC51_bm;            break;
  }
}

void EINT5::enable()
{
  _int_ctrl.enableInterrupt(toIntNum(Interrupt::EXTERNAL_INT5));
}

void EINT5::disable()
{
  _int_ctrl.disableInterrupt(toIntNum(Interrupt::EXTERNAL_INT5));
}

void EINT5::registerExternalInterruptCallback(interface::ExternalInterruptCallback * external_interrupt_callback)
{
  _external_interrupt_callback = external_interrupt_callback;
}

void EINT5::ISR_onExternalInterruptEvent()
{
  if(_external_interrupt_callback)
  {
    _external_interrupt_callback->onExternalEventCallback();
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN32_64_128 */

} /* hal */

} /* spectre */
