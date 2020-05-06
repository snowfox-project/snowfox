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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <vireg/Version.h>

/**************************************************************************************
 * CHECKS
 **************************************************************************************/

static_assert(snowfox::vireg::Version::Major >= 1, "Minimum requirement for 'libvireg' v1.0.0");
static_assert(snowfox::vireg::Version::Minor >= 0, "Minimum requirement for 'libvireg' v1.0.0");
static_assert(snowfox::vireg::Version::Patch >= 0, "Minimum requirement for 'libvireg' v1.0.0");
