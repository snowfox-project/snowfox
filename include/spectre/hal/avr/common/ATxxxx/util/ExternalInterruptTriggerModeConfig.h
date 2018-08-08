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

#ifndef INCLUDE_SPECTRE_HAL_AVR_COMMON_ATXXXX_EXTINTTRIGGERMODEUTIL_H_
#define INCLUDE_SPECTRE_HAL_AVR_COMMON_ATXXXX_EXTINTTRIGGERMODEUTIL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/extint/ExternalInterruptConfiguration.h>

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
 * TYPEDEF
 **************************************************************************************/

enum class ExtInt
{
  EINT0, EINT1, EINT2, EINT3, EINT4, EINT5, EINT6, EINT7
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class ExternalInterruptTriggerModeConfig
{

public:


  static void setTriggerMode(ExtInt const ext_int, interface::TriggerMode const trigger_mode, volatile uint8_t * eicra, volatile uint8_t * eicrb);


private:

  ExternalInterruptTriggerModeConfig() { }
  ExternalInterruptTriggerModeConfig(ExternalInterruptTriggerModeConfig const & other) { }

  static void setTriggerModeEint0(interface::TriggerMode const trigger_mode, volatile uint8_t * eicra);
  static void setTriggerModeEint1(interface::TriggerMode const trigger_mode, volatile uint8_t * eicra);
  static void setTriggerModeEint2(interface::TriggerMode const trigger_mode, volatile uint8_t * eicra);
  static void setTriggerModeEint3(interface::TriggerMode const trigger_mode, volatile uint8_t * eicra);
  static void setTriggerModeEint4(interface::TriggerMode const trigger_mode, volatile uint8_t * eicrb);
  static void setTriggerModeEint5(interface::TriggerMode const trigger_mode, volatile uint8_t * eicrb);
  static void setTriggerModeEint6(interface::TriggerMode const trigger_mode, volatile uint8_t * eicrb);
  static void setTriggerModeEint7(interface::TriggerMode const trigger_mode, volatile uint8_t * eicrb);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_COMMON_ATXXXX_EXTINTTRIGGERMODEUTIL_H_ */
