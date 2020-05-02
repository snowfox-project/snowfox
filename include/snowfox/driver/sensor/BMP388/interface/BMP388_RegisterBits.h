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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_INTERFACE_BMP388_REGISTERBITS_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_INTERFACE_BMP388_REGISTERBITS_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensor::BMP388::interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class INT_CTRL : uint8_t
{
  DRDY_EN   = 6, /* Enable temperature / pressure data ready interrupt for INT pin and INT_STATUS. */
  FFULL_EN  = 4, /* Enable Fifo full interrupt for INT pin and INT_STATUS. */
  FWTM_EN   = 3, /* Enable FIFO watermark reached interrupt for INT pin and INT_STATUS. */
  INT_LATCH = 2, /* Latching of interrupts for INT pin and INT_STATUS register. */
  INT_LEVEL = 1, /* Level of INT pin: Active Low or Active High */
  INT_OD    = 0  /* Configure output: open-drain or push-pull. */
};

enum class PWR_CTRL : uint8_t
{
  MODE_1   = 5,
  MODE_0   = 4,
  TEMP_EN  = 1,
  PRESS_EN = 0
};

enum class OSR : uint8_t
{
  OSR_T_2 = 5,
  OSR_T_1 = 4,
  OSR_T_0 = 3,
  OSR_P_2 = 2,
  OSR_P_1 = 1,
  OSR_P_0 = 0
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensor::BMP388::interface */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_INTERFACE_BMP388_REGISTERBITS_H_ */
