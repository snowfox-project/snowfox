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

#ifndef INCLUDE_SPECTRE_COMSTACK_CANOPEN_COBBASEID_H_
#define INCLUDE_SPECTRE_COMSTACK_CANOPEN_COBBASEID_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace comstack
{

namespace canopen
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class CobBaseId : uint16_t
{
  NetworkManagement = 0x000,
  Sync_Emergency    = 0x080,
  TimeStamp         = 0x100,
  TPDO1             = 0x180,
  RPDO1             = 0x200,
  TPDO2             = 0x280,
  RPDO2             = 0x300,
  TPDO3             = 0x380,
  RPDO3             = 0x400,
  TPDO4             = 0x480,
  RPDO4             = 0x500,
  SDO_TX            = 0x580,
  SDO_RX            = 0x600,
  NodeGuard         = 0x700
};

/**************************************************************************************
 * CONSTEXPR FUNCTIONS
 **************************************************************************************/

constexpr uint16_t toValue(CobBaseId const cob_base_id)
{
  return static_cast<uint16_t>(cob_base_id);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* canopen */

} /* comstack */

} /* spectre */

#endif /* INCLUDE_SPECTRE_COMSTACK_CANOPEN_COBBASEID_H_ */
