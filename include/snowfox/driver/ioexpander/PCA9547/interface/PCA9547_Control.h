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

#ifndef INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_INTERFACE_PCA9547_INTERFACE_H_
#define INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_INTERFACE_PCA9547_INTERFACE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace ioexpander
{

namespace PCA9547
{

namespace interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class I2cChannel : uint8_t
{
  CH_0       = 0x08,
  CH_1       = 0x09,
  CH_2       = 0x0A,
  CH_3       = 0x0B,
  CH_4       = 0x0C,
  CH_5       = 0x0D,
  CH_6       = 0x0E,
  CH_7       = 0x0F,
  NO_CHANNEL = 0x00
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class PCA9547_Control
{

public:

           PCA9547_Control() { }
  virtual ~PCA9547_Control() { }


  virtual bool setChannel(I2cChannel const   sel) = 0;
  virtual bool getChannel(I2cChannel       * sel) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* PCA9547 */

} /* ioexpander */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_INTERFACE_PCA9547_INTERFACE_H_ */
