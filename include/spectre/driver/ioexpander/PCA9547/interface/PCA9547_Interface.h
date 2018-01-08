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

#ifndef INCLUDE_SPECTRE_DRIVER_IOEXPANDER_INTERFACE_PCA9547_INTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_IOEXPANDER_INTERFACE_PCA9547_INTERFACE_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <stdbool.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace ioexpander
{

namespace PCA9547
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  I2C_CHANNEL_0   = 0x08,
  I2C_CHANNEL_1   = 0x09,
  I2C_CHANNEL_2   = 0x0A,
  I2C_CHANNEL_3   = 0x0B,
  I2C_CHANNEL_4   = 0x0C,
  I2C_CHANNEL_5   = 0x0D,
  I2C_CHANNEL_6   = 0x0E,
  I2C_CHANNEL_7   = 0x0F,
  I2C_NO_CHANNEL  = 0x00
} I2CChannelSelect;

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class PCA9547_Interface
{

public:

           PCA9547_Interface() { }
  virtual ~PCA9547_Interface() { }


  virtual bool setChannel(I2CChannelSelect const   sel) = 0;
  virtual bool getChannel(I2CChannelSelect       * sel) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* PCA9547 */

} /* ioexpander */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_IOEXPANDER_INTERFACE_PCA9547_INTERFACE_H_ */
