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

#include <spectre/hal/avr/common/ATxxxx/EINT7.h>

#if defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_at90can32 ) || defined(MCU_TYPE_at90can64 ) || defined(MCU_TYPE_at90can128) )
#include <spectre/hal/avr/common/AT90CAN32_64_128/InterruptController.h>
#endif
#if defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega2560) || defined(MCU_TYPE_atmega1280) || defined(MCU_TYPE_atmega640 ) )
#include <spectre/hal/avr/common/ATMEGA640_1280_2560/InterruptController.h>
#endif

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATxxxx
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* EICRA */
#define ISC71_bm (1<<7)
#define ISC70_bm (1<<6)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

EINT7::EINT7(volatile uint8_t * eicrb, interface::InterruptController & int_ctrl)
: _EICRB                      (eicrb   ),
  _int_ctrl                   (int_ctrl),
  _external_interrupt_callback(0       )
{

}

EINT7::~EINT7()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void EINT7::setTriggerMode(interface::TriggerMode const trigger_mode)
{
  *_EICRB &= ~(ISC71_bm | ISC70_bm);

  switch(trigger_mode)
  {
  case interface::TriggerMode::Any        : *_EICRB |=            ISC70_bm; break;
  case interface::TriggerMode::Low        : *_EICRB |= 0;                   break;
  case interface::TriggerMode::High       : /* Not supported */             break;
  case interface::TriggerMode::RisingEdge : *_EICRB |= ISC71_bm | ISC70_bm; break;
  case interface::TriggerMode::FallingEdge: *_EICRB |= ISC71_bm;            break;
  }
}

void EINT7::enable()
{
#if defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_at90can32 ) || defined(MCU_TYPE_at90can64 ) || defined(MCU_TYPE_at90can128) )
  uint8_t const int_num = AT90CAN32_64_128::toIntNum(AT90CAN32_64_128::Interrupt::EXTERNAL_INT7);
#endif
#if defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega2560) || defined(MCU_TYPE_atmega1280) || defined(MCU_TYPE_atmega640 ) )
  uint8_t const int_num = ATMEGA640_1280_2560::toIntNum(ATMEGA640_1280_2560::Interrupt::EXTERNAL_INT7);
#endif
  _int_ctrl.enableInterrupt(int_num);
}

void EINT7::disable()
{
#if defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_at90can32 ) || defined(MCU_TYPE_at90can64 ) || defined(MCU_TYPE_at90can128) )
  uint8_t const int_num = AT90CAN32_64_128::toIntNum(AT90CAN32_64_128::Interrupt::EXTERNAL_INT7);
#endif
#if defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega2560) || defined(MCU_TYPE_atmega1280) || defined(MCU_TYPE_atmega640 ) )
  uint8_t const int_num = ATMEGA640_1280_2560::toIntNum(ATMEGA640_1280_2560::Interrupt::EXTERNAL_INT7);
#endif
  _int_ctrl.disableInterrupt(int_num);
}

void EINT7::registerExternalInterruptCallback(interface::ExternalInterruptCallback * external_interrupt_callback)
{
  _external_interrupt_callback = external_interrupt_callback;
}

void EINT7::ISR_onExternalInterruptEvent()
{
  if(_external_interrupt_callback)
  {
    _external_interrupt_callback->onExternalEventCallback();
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */
