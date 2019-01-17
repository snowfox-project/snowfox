/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2019 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA640_1280_2560_EXTERNALINTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA640_1280_2560_EXTERNALINTERRUPTCONTROLLER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/extint/ExternalInterruptAssembly.h>
#include <spectre/hal/interface/extint/ExternalInterruptConfiguration.h>

#include <spectre/hal/interface/interrupt/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA640_1280_2560
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class ExternalInterrupt : uint8_t
{
  EXTERNAL_INT0,
  EXTERNAL_INT1,
  EXTERNAL_INT2,
  EXTERNAL_INT3,
  EXTERNAL_INT4,
  EXTERNAL_INT5,
  EXTERNAL_INT6,
  EXTERNAL_INT7,
  PIN_CHANGE_INT0,
  PIN_CHANGE_INT1,
  PIN_CHANGE_INT2,
  PIN_CHANGE_INT3,
  PIN_CHANGE_INT4,
  PIN_CHANGE_INT5,
  PIN_CHANGE_INT6,
  PIN_CHANGE_INT7,
  PIN_CHANGE_INT8,
  PIN_CHANGE_INT9,
  PIN_CHANGE_INT10,
  PIN_CHANGE_INT11,
  PIN_CHANGE_INT12,
  PIN_CHANGE_INT13,
  PIN_CHANGE_INT14,
  PIN_CHANGE_INT15,
  PIN_CHANGE_INT16,
  PIN_CHANGE_INT17,
  PIN_CHANGE_INT18,
  PIN_CHANGE_INT19,
  PIN_CHANGE_INT20,
  PIN_CHANGE_INT21,
  PIN_CHANGE_INT22,
  PIN_CHANGE_INT23
};

/**************************************************************************************
 * CONSTEXPR FUNCTIONS
 **************************************************************************************/

constexpr uint8_t toExtIntNum(ExternalInterrupt const external_interrupt)
{
  return static_cast<uint8_t>(external_interrupt);
}

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class ExternalInterruptController : public interface::ExternalInterruptConfiguration,
                                    public interface::ExternalInterruptAssembly
{

public:

           ExternalInterruptController(volatile uint8_t               * eicra,
                                       volatile uint8_t               * eicrb,
                                       interface::InterruptController & int_ctrl);
  virtual ~ExternalInterruptController();


  /* External Interrupt Configuration */

  virtual void setTriggerMode(uint8_t const ext_int_num, interface::TriggerMode const trigger_mode) override;
  virtual void enable        (uint8_t const ext_int_num                                           ) override;
  virtual void disable       (uint8_t const ext_int_num                                           ) override;


  /* External Interrupt Assembly */

  virtual void registerInterruptCallback(uint8_t const ext_int_num, interface::ExternalInterruptCallback * external_interrupt_callback) override;


private:

  volatile uint8_t               * _EICRA,
                                 * _EICRB;
  interface::InterruptController & _int_ctrl;


  static uint8_t converToIntNum(uint8_t const ext_int_num);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA640_1280_2560 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_COMMON_ATMEGA640_1280_2560_EXTERNALINTERRUPTCONTROLLER_H_ */
