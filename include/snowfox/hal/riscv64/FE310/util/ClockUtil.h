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

#ifndef INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_UTIL_CLOCK_UTIL_H_
#define INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_UTIL_CLOCK_UTIL_H_

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

namespace hal
{

namespace FE310
{

/**************************************************************************************
 * PROTOTYPES
 **************************************************************************************/

bool findPllParam(uint32_t const pllref_Hz, uint32_t const pllout_Hz, uint8_t & r, uint8_t & f, uint8_t & q);
bool isValidPLLR (uint8_t const pllr);
bool isValidPLLF (uint8_t const pllf);
bool isValidPLLQ (uint8_t const pllq);
bool setPLLR     (volatile uint32_t * PRCI_PLLCFG, uint8_t const pllr);
bool setPLLF     (volatile uint32_t * PRCI_PLLCFG, uint8_t const pllf);
bool setPLLQ     (volatile uint32_t * PRCI_PLLCFG, uint8_t const pllq);

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* FE310 */

} /* hal */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_UTIL_CLOCK_UTIL_H_ */