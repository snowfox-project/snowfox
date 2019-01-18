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

#ifndef INCLUDE_SNOWFOX_COMSTACK_CANOPEN_NODESTATE_H_
#define INCLUDE_SNOWFOX_COMSTACK_CANOPEN_NODESTATE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace comstack
{

namespace canopen
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class NodeState : uint16_t {
  Initialisation = 0x00,
  Disconnected   = 0x01,
  Connecting     = 0x02,
  Preparing      = 0x02,
  Stopped        = 0x04,
  Operational    = 0x05,
  PreOperational = 0x7F,
  Unknown        = 0x0F
};

/**************************************************************************************
 * CONSTEXPR FUNCTIONS
 **************************************************************************************/

constexpr uint16_t toValue(NodeState const node_state)
{
  return static_cast<uint16_t>(node_state);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* canopen */

} /* comstack */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_COMSTACK_CANOPEN_NODESTATE_H_ */
