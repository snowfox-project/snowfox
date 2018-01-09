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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_AS5600_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_AS5600_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/sensor/AS5600/interface/AS5600_Interface.h>
#include <spectre/driver/sensor/AS5600/interface/AS5600_ConfigurationInterface.h>
#include <spectre/driver/sensor/AS5600/interface/AS5600_IO_Interface.h>

#include <stdint.h>
#include <stdbool.h>

#include <spectre/driver/interface/Debug.h>

#include <spectre/hal/interface/i2c/I2CMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
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

class AS5600 : public AS5600_Interface,
               public AS5600_ConfigurationInterface
{

public:

           AS5600(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master);
  virtual ~AS5600();


  /* AS5600 Interface */

  virtual bool readAngle    (uint16_t * angle    ) override;
  virtual bool readAngleRaw (uint16_t * angle_raw) override;

  virtual bool readStatus   (uint8_t  * status   ) override;
  virtual bool readAGC      (uint8_t  * agc      ) override;
  virtual bool readMagnitude(uint16_t * mag      ) override;


  /* AS5600 Configuration Interface */

  virtual bool setPowerMode           (PowerModeSelect     const   sel        ) override;
  virtual bool setHysteresis          (HysteresisSelect    const   sel        ) override;
  virtual bool setOutputStage         (OutputStageSelect   const   sel        ) override;
  virtual bool setPWMFrequency        (PWMFrequencySelect  const   sel        ) override;
  virtual bool setSlowFilter          (SlowFilterSelect    const   sel        ) override;
  virtual bool setFastFilterThreshold (FastFilterThreshold const   sel        ) override;
  virtual bool enableWatchog          (                                       ) override;
  virtual bool disableWatchog         (                                       ) override;

  virtual bool setAngularStartPosition(uint16_t            const   angle_start) override;
  virtual bool setAngularStopPosition (uint16_t            const   angle_stop ) override;
  virtual bool setMaximumAngle        (uint16_t            const   angle_max  ) override;


  static bool  isMagnetTooStrong      (uint8_t             const   status     );
  static bool  isMagnetTooWeak        (uint8_t             const   status     );
  static bool  isMagnetDetected       (uint8_t             const   status     );

         void  debug_dumpAllRegs      (driver::interface::Debug & debug_interface);

private:

  uint8_t                     _i2c_address;
  hal::interface::I2CMaster & _i2c_master;

  bool readSingleRegister   (uint8_t const reg_addr, uint8_t       * data);
  bool writeSingleRegister  (uint8_t const reg_addr, uint8_t const    data);
  bool readMultipleRegister (uint8_t const reg_addr, uint8_t       * data, uint16_t const num_bytes);
  bool writeMultipleRegister(uint8_t const reg_addr, uint8_t const * data, uint16_t const num_bytes);

  void debug_dumpSingleReg  (driver::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AS5600 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_AS5600_H_ */
