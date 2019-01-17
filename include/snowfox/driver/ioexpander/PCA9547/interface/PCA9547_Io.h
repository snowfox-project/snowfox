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

#ifndef INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_PCA9547_INTERFACE_PCA9547_IO_INTERFACE_H_
#define INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_PCA9547_INTERFACE_PCA9547_IO_INTERFACE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

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
 * CLASS DECLARATION
 **************************************************************************************/

class PCA9547_Io
{

public:

           PCA9547_Io() { }
  virtual ~PCA9547_Io() { }


  virtual bool readControlRegister (uint8_t        * data) = 0;
  virtual bool writeControlRegister(uint8_t const    data) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* PCA9547 */

} /* ioexpander */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_PCA9547_INTERFACE_PCA9547_IO_INTERFACE_H_ */
