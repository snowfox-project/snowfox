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

#ifndef INCLUDE_SPECTRE_UTIL_TYPE_CANFRAME_H_
#define INCLUDE_SPECTRE_UTIL_TYPE_CANFRAME_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace util
{

namespace type
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef struct
{
  uint32_t id;
  uint8_t  dlc,
           data[8];
} __attribute((packed)) CanFrame;

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr CAN_EFF_BITMASK = 0x80000000;
static uint32_t constexpr CAN_RTR_BITMASK = 0x40000000;
static uint32_t constexpr CAN_ERR_BITMASK = 0x20000000;

/**************************************************************************************
 * PROTOTYPES
 **************************************************************************************/

bool     isExtendedId   (util::type::CanFrame const & frame);
bool     isRTR          (util::type::CanFrame const & frame);
bool     isErrorFrame   (util::type::CanFrame const & frame);
uint32_t toCanId        (util::type::CanFrame const & frame);
uint32_t toCanIdExtended(util::type::CanFrame const & frame);

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* util */

} /* type*/

} /* spectre */

#endif /* INCLUDE_SPECTRE_UTIL_TYPE_CANFRAME_H_ */
