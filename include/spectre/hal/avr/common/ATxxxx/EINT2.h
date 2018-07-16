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

#ifndef INCLUDE_SPECTRE_HAL_AVR_COMMON_AT90CAN32_64_128_EINT2_H_
#define INCLUDE_SPECTRE_HAL_AVR_COMMON_AT90CAN32_64_128_EINT2_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/extint/ExternalInterruptAssembly.h>
#include <spectre/hal/interface/extint/ExternalInterruptCallback.h>
#include <spectre/hal/interface/extint/ExternalInterruptConfiguration.h>

#include <spectre/hal/interface/interrupt/InterruptControl.h>
#include <spectre/hal/interface/interrupt/InterruptCallback.h>

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
 * CLASS DECLARATION
 **************************************************************************************/

class EINT2 : public interface::ExternalInterruptConfiguration,
              public interface::ExternalInterruptAssembly
{

public:

           EINT2(volatile uint8_t * eicra, interface::InterruptControl & int_ctrl);
  virtual ~EINT2();


  /* External Interrupt Configuration */

  virtual void setTriggerMode(interface::TriggerMode const trigger_mode) override;
  virtual void enable        (                                         ) override;
  virtual void disable       (                                         ) override;


  /* External Interrupt Assembly */

  virtual void registerExternalInterruptCallback(interface::ExternalInterruptCallback * external_interrupt_callback) override;


  /* Functions to be called upon execution of a interrupt service routine */

  void ISR_onExternalInterruptEvent();


private:

  volatile uint8_t            * _EICRA;
  interface::InterruptControl & _int_ctrl;

  interface::ExternalInterruptCallback * _external_interrupt_callback;

};

/**************************************************************************************/

class EINT2_ExternalInterruptEventCallback : public interface::InterruptCallback
{

public:

           EINT2_ExternalInterruptEventCallback(EINT2 & eint2) : _eint2(eint2) { }
  virtual ~EINT2_ExternalInterruptEventCallback() { }


  virtual void interruptServiceRoutine() override
  {
    _eint2.ISR_onExternalInterruptEvent();
  }

private:

  EINT2 & _eint2;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_COMMON_AT90CAN32_64_128_EINT2_H_ */
