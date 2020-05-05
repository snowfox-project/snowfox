/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#ifndef INTERFACE_I2C_MASTER_CONFIGURATION_H_
#define INTERFACE_I2C_MASTER_CONFIGURATION_H_

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class I2cClock
{
  F_100_kHz,   /* Standard mode  */
  F_400_kHz,   /* Fast mode      */
  F_1000_kHz   /* Fast mode plus */
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class I2cMasterConfiguration
{

public:

           I2cMasterConfiguration() { }
  virtual ~I2cMasterConfiguration() { }


  virtual void setI2cClock(I2cClock const i2c_clock) = 0;
  
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::interface*/

#endif /* INTERFACE_I2C_MASTER_CONFIGURATION_H_ */
