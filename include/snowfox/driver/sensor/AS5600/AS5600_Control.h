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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/AS5600/interface/AS5600_Control.h>

#include <snowfox/driver/sensor/AS5600/interface/AS5600_Io.h>

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

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AS5600_Control final : public interface::AS5600_Control
{

public:

           AS5600_Control(interface::AS5600_Io & io);
  virtual ~AS5600_Control();


  /* AS5600 Interface */

  virtual bool readAngle    (uint16_t * angle    ) override;
  virtual bool readAngleRaw (uint16_t * angle_raw) override;

  virtual bool readStatus   (uint8_t  * status   ) override;
  virtual bool readAGC      (uint8_t  * agc      ) override;
  virtual bool readMagnitude(uint16_t * mag      ) override;


  /* AS5600 Configuration Interface */

  virtual bool setPowerMode           (interface::PowerMode           const power_mode           ) override;
  virtual bool setHysteresis          (interface::Hysteresis          const hysteresis           ) override;
  virtual bool setOutputStage         (interface::OutputStage         const output_stage         ) override;
  virtual bool setPwmFrequency        (interface::PwmFrequency        const pwm_frequency        ) override;
  virtual bool setSlowFilter          (interface::SlowFilter          const slow_filter          ) override;
  virtual bool setFastFilterThreshold (interface::FastFilterThreshold const fast_filter_threshold) override;
  virtual bool enableWatchog          (                                                          ) override;
  virtual bool disableWatchog         (                                                          ) override;

  virtual bool setAngularStartPosition(uint16_t                       const   angle_start        ) override;
  virtual bool setAngularStopPosition (uint16_t                       const   angle_stop         ) override;
  virtual bool setMaximumAngle        (uint16_t                       const   angle_max          ) override;


  static bool  isMagnetTooStrong      (uint8_t                        const   status             );
  static bool  isMagnetTooWeak        (uint8_t                        const   status             );
  static bool  isMagnetDetected       (uint8_t                        const   status             );


private:

  interface::AS5600_Io & _io;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AS5600 */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_H_ */
