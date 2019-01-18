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

#ifndef INCLUDE_SNOWFOX_DRIVER_MEMORY_AT45DBX_AT45DBX_CONFIGURATION_H_
#define INCLUDE_SNOWFOX_DRIVER_MEMORY_AT45DBX_AT45DBX_CONFIGURATION_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/memory/AT45DBx/interface/AT45DBx_Configuration.h>

#include <snowfox/driver/memory/AT45DBx/interface/AT45DBx_Io.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace memory
{

namespace AT45DBx
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AT45DBx_Configuration : public interface::AT45DBx_Configuration
{

public:

           AT45DBx_Configuration(interface::AT45DBx_Io & io);
  virtual ~AT45DBx_Configuration();


  virtual util::jedec::JedecCode readDeviceId() override;


private:

  interface::AT45DBx_Io & _io;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT45DBx */

} /* memory */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_AT45DBX_AT45DBX_CONFIGURATION_H_ */
