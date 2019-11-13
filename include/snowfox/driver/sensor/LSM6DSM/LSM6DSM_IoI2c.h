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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_LSM6DSM_IO_SPI_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_LSM6DSM_IO_SPI_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/LSM6DSM/interface/LSM6DSM_Io.h>

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

namespace LSM6DSM
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LSM6DSM_IoI2c final : public interface::LSM6DSM_Io
{

public:

           LSM6DSM_IoI2c(uint8_t const i2c_address, hal::interface::I2cMaster & i2c_master);
  virtual ~LSM6DSM_IoI2c();


  virtual bool readRegister (interface::Register const reg, uint8_t       * data                          ) override final;
  virtual bool readRegister (interface::Register const reg, uint8_t       * data, uint16_t const num_bytes) override final;
  virtual bool writeRegister(interface::Register const reg, uint8_t const   data                          ) override final;
  virtual bool writeRegister(interface::Register const reg, uint8_t const * data, uint16_t const num_bytes) override final;

private:

  uint8_t                     _i2c_address;
  hal::interface::I2cMaster & _i2c_master;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LSM6DSM */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_LSM6DSM_IO_SPI_H_ */