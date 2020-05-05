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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_INTERFACE_LSM6DSM_REGISTER_BITS_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_INTERFACE_LSM6DSM_REGISTER_BITS_H_

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensor::LSM6DSM::interface
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* LSM6DSM_CTRL3_C_REG Bit Definitions ************************************************/
#define LSM6DSM_CTRL3_C_REG_BDU_bm         (1<<6)   /* Block data update                                        */
#define LSM6DSM_CTRL3_C_REG_IF_INC_bm      (1<<2)   /* Register address auto-increment during multi-byte-access */
#define LSM6DSM_CTRL3_C_REG_SW_RESET_bm    (1<<0)   /* Perform a software reset                                 */

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensor::LSM6DSM::interface */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_INTERFACE_LSM6DSM_REGISTER_BITS_H_ */
