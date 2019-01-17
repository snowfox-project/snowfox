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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_INTERFACE_AS5600_CONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_INTERFACE_AS5600_CONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/AS5600/interface/AS5600_Interface.h>
#include <snowfox/driver/sensor/AS5600/interface/AS5600_ConfigurationInterface.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace AS5600
{

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AS5600_Control
{

public:

           AS5600_Control() { }
  virtual ~AS5600_Control() { }


  /* AS5600 Interface */

  virtual bool readAngle    (uint16_t * angle    ) = 0;
  virtual bool readAngleRaw (uint16_t * angle_raw) = 0;

  virtual bool readStatus   (uint8_t  * status   ) = 0;
  virtual bool readAGC      (uint8_t  * agc      ) = 0;
  virtual bool readMagnitude(uint16_t * mag      ) = 0;


  /* AS5600 Configuration Interface */

  virtual bool setPowerMode           (PowerMode           const power_mode           ) = 0;
  virtual bool setHysteresis          (Hysteresis          const hysteresis           ) = 0;
  virtual bool setOutputStage         (OutputStage         const output_stage         ) = 0;
  virtual bool setPwmFrequency        (PwmFrequency        const pwm_frequency        ) = 0;
  virtual bool setSlowFilter          (SlowFilter          const slow_filter          ) = 0;
  virtual bool setFastFilterThreshold (FastFilterThreshold const fast_filter_threshold) = 0;
  virtual bool enableWatchog          (                                               ) = 0;
  virtual bool disableWatchog         (                                               ) = 0;

  virtual bool setAngularStartPosition(uint16_t            const angle_start          ) = 0;
  virtual bool setAngularStopPosition (uint16_t            const angle_stop           ) = 0;
  virtual bool setMaximumAngle        (uint16_t            const angle_max            ) = 0;


};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* AS5600 */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_INTERFACE_AS5600_CONTROL_H_ */
