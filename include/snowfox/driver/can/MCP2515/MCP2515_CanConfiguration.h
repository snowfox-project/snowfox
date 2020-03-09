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

#ifndef INCLUDE_SNOWFOX_DRIVER_CAN_MCP2515_MCP2515_CANCONFIGURATION_H_
#define INCLUDE_SNOWFOX_DRIVER_CAN_MCP2515_MCP2515_CANCONFIGURATION_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/can/interface/CanConfiguration.h>

#include <snowfox/driver/can/MCP2515/interface/configuration/MCP2515_Configuration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace can
{

namespace MCP2515
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MCP2515_CanConfiguration final : public can::interface::CanConfiguration
{

public:

           MCP2515_CanConfiguration(interface::MCP2515_Configuration & config);
  virtual ~MCP2515_CanConfiguration();


  virtual bool setCanBitRate(can::interface::CanBitRate const can_bit_rate) override;


private:

  interface::MCP2515_Configuration & _config;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_CAN_MCP2515_MCP2515_CANCONFIGURATION_H_ */
