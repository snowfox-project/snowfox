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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_AS5600_IO_I2C_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_AS5600_IO_I2C_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/AS5600/interface/AS5600_Io.h>

#include <snowfox/hal/interface/i2c/I2cMaster.h>

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

class AS5600_IoI2c : public interface::AS5600_Io
{

public:

           AS5600_IoI2c(uint8_t const i2c_address, hal::interface::I2cMaster & i2c_master);
  virtual ~AS5600_IoI2c();


  virtual bool readRegister (interface::Register const reg, uint8_t       * data, uint16_t const num_bytes) override;
  virtual bool readRegister (interface::Register const reg, uint8_t       * data                          ) override;
  virtual bool writeRegister(interface::Register const reg, uint8_t const * data, uint16_t const num_bytes) override;
  virtual bool writeRegister(interface::Register const reg, uint8_t const   data                          ) override;


private:

  uint8_t                     _i2c_address;
  hal::interface::I2cMaster & _i2c_master;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AS5600 */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_AS5600_AS5600_IO_I2C_H_ */
