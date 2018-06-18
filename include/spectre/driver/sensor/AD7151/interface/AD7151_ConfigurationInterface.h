/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_AD7151_INTERFACE_AD7151_CONFIGURATIONINTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_AD7151_INTERFACE_AD7151_CONFIGURATIONINTERFACE_H_

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

namespace driver
{

namespace sensor
{

namespace AD7151
{

namespace interface
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* AD7151_SETUP_REG Bit Definitions ***************************************************/
#define AD7151_SETUP_REG_RNG_H_bm                 (1<<7)
#define AD7151_SETUP_REG_RNG_L_bm                 (1<<6)
#define AD7151_SETUP_REG_HYST_bm                  (1<<4)
#define AD7151_SETUP_REG_THRESHOLD_SETTING_3_bm   (1<<3)
#define AD7151_SETUP_REG_THRESHOLD_SETTING_2_bm   (1<<2)
#define AD7151_SETUP_REG_THRESHOLD_SETTING_1_bm   (1<<1)
#define AD7151_SETUP_REG_THRESHOLD_SETTING_0_bm   (1<<0)

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class CapacitiveInputRange : uint8_t
{
  RANGE_2_0_pF = 0,
  RANGE_0_5_pF =                             AD7151_SETUP_REG_RNG_L_bm,
  RANGE_1_0_pF = AD7151_SETUP_REG_RNG_H_bm,
  RANGE_4_0_pF = AD7151_SETUP_REG_RNG_H_bm | AD7151_SETUP_REG_RNG_L_bm
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AD7151_ConfigurationInterface
{

public:

           AD7151_ConfigurationInterface() { }
  virtual ~AD7151_ConfigurationInterface() { }


  virtual bool setCapacitiveInputRange(CapacitiveInputRange const capacitive_input_range) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* AD7151 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_AD7151_INTERFACE_AD7151_CONFIGURATIONINTERFACE_H_ */
