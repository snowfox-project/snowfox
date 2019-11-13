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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_AD7151_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_AD7151_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/AD7151/interface/AD7151_Control.h>

#include <snowfox/driver/sensor/AD7151/interface/AD7151_Io.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace AD7151
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AD7151_Control final : public interface::AD7151_Control
{

public:

           AD7151_Control(interface::AD7151_Io & io);
  virtual ~AD7151_Control();


  /* AD7151 Interface */

  virtual bool startSingleConversion        (                                 ) override final;
  virtual bool checkIfConversionIsComplete  (bool     * is_conversion_complete) override final;
  virtual bool readConversionResult         (uint16_t * raw_data              ) override final;


  /* AD7151 Configuration Interface */

  virtual bool setCapacitiveInputRange      (interface::CapacitiveInputRange const capacitive_input_range) override final;

private:

  interface::AD7151_Io & _io;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AD7151 */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_AD7151_H_ */
