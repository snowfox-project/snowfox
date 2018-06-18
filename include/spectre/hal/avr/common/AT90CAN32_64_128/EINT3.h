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

#ifndef INCLUDE_SPECTRE_HAL_AVR_COMMON_AT90CAN32_64_128_EINT3_H_
#define INCLUDE_SPECTRE_HAL_AVR_COMMON_AT90CAN32_64_128_EINT3_H_

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

class EINT3 : public interface::ExternalInterruptConfiguration,
              public interface::ExternalInterruptAssembly
{

public:

           EINT3(volatile uint8_t * eicra, interface::InterruptController & int_ctrl);
  virtual ~EINT3();


  /* External Interrupt Configuration */

  virtual void setTriggerMode(interface::TriggerMode const trigger_mode) override;
  virtual void enable        (                                         ) override;
  virtual void disable       (                                         ) override;


  /* External Interrupt Assembly */

  virtual void registerExternalInterruptCallback(interface::ExternalInterruptCallback * external_interrupt_callback) override;


  /* Functions to be called upon execution of a interrupt service routine */

  void ISR_onExternalInterruptEvent();


private:

  volatile uint8_t               * _EICRA;
  interface::InterruptController & _int_ctrl;

  interface::ExternalInterruptCallback * _external_interrupt_callback;

};

/**************************************************************************************/

class EINT3_ExternalInterruptEventCallback : public interface::InterruptCallback
{

public:

           EINT3_ExternalInterruptEventCallback(EINT3 & eint3) : _eint3(eint3) { }
  virtual ~EINT3_ExternalInterruptEventCallback() { }


  virtual void interruptServiceRoutine() override
  {
    _eint3.ISR_onExternalInterruptEvent();
  }

private:

  EINT3 & _eint3;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN32_64_128 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_COMMON_AT90CAN32_64_128_EINT3_H_ */
