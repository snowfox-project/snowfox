/**
 * Snowfox is a modular RTOS with extensive IO support.
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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/LSM6DSM/LSM6DSM_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace LSM6DSM
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr DEVICE_RESET_DURATION_ms = 100;

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

LSM6DSM_Control::LSM6DSM_Control(interface::LSM6DSM_Io & io,
                                 hal::interface::Delay & delay)
: _io   (io   ),
  _delay(delay)
{

}

LSM6DSM_Control::~LSM6DSM_Control()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool LSM6DSM_Control::reset() 
{
  if(!_io.writeRegister(interface::Register::CTRL3_C, LSM6DSM_CTRL3_C_REG_SW_RESET_bm)) return false;

  _delay.delay_ms(DEVICE_RESET_DURATION_ms);
  
  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LSM6DSM */

} /* sensor */

} /* driver */

} /* snowfox */
