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

#ifndef INCLUDE_SPECTRE_HAL_AVR_COMMON_AT90CAN32_64_128_EINT7_H_
#define INCLUDE_SPECTRE_HAL_AVR_COMMON_AT90CAN32_64_128_EINT7_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/extint/ExternalInterruptAssembly.h>
#include <spectre/hal/interface/extint/ExternalInterruptCallback.h>
#include <spectre/hal/interface/extint/ExternalInterruptConfiguration.h>

#include <spectre/hal/interface/interrupt/InterruptCallback.h>
#include <spectre/hal/interface/interrupt/InterruptController.h>

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
 * CLASS DECLARATION
 **************************************************************************************/

class EINT7 : public interface::ExternalInterruptConfiguration,
              public interface::ExternalInterruptAssembly
{

public:

           EINT7(volatile uint8_t * eicrb, interface::InterruptController & int_ctrl);
  virtual ~EINT7();


  /* External Interrupt Configuration */

  virtual void setTriggerMode(interface::TriggerMode const trigger_mode) override;
  virtual void enable        (                                         ) override;
  virtual void disable       (                                         ) override;


  /* External Interrupt Assembly */

  virtual void registerExternalInterruptCallback(interface::ExternalInterruptCallback * external_interrupt_callback) override;


  /* Functions to be called upon execution of a interrupt service routine */

  void ISR_onExternalInterruptEvent();


private:

  volatile uint8_t               * _EICRB;
  interface::InterruptController & _int_ctrl;

  interface::ExternalInterruptCallback * _external_interrupt_callback;

};

/**************************************************************************************/

class EINT7_ExternalInterruptEventCallback : public interface::InterruptCallback
{

public:

           EINT7_ExternalInterruptEventCallback(EINT7 & eint7) : _eint7(eint7) { }
  virtual ~EINT7_ExternalInterruptEventCallback() { }


  virtual void interruptServiceRoutine() override
  {
    _eint7.ISR_onExternalInterruptEvent();
  }

private:

  EINT7 & _eint7;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN32_64_128 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_COMMON_AT90CAN32_64_128_EINT7_H_ */
