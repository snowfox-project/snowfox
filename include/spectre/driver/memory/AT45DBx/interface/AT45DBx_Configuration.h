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

#ifndef INCLUDE_SPECTRE_DRIVER_MEMORY_AT45DBX_INTERFACE_AT45DBX_CONFIGURATION_H_
#define INCLUDE_SPECTRE_DRIVER_MEMORY_AT45DBX_INTERFACE_AT45DBX_CONFIGURATION_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace memory
{

namespace AT45DBx
{

namespace interface
{

/**************************************************************************************
 * DEFINE
 **************************************************************************************/

#define AT45DBx_RDDEVID 0x9F

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AT45DBx_Configuration
{

public:

           AT45DBx_Configuration() { }
  virtual ~AT45DBx_Configuration() { }


  virtual void readDeviceId(uint8_t & dev_id_byte_0, uint8_t & dev_id_byte_1, uint8_t & dev_id_byte_2) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* AT45DBx */

} /* memory */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_MEMORY_AT45DBX_INTERFACE_AT45DBX_CONFIGURATION_H_ */