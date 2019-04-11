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

#include <snowfox/hal/interface/spi/SpiMaster.h>
#include <snowfox/hal/interface/gpio/DigitalOutPin.h>

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

class LSM6DSM_IoSpi : public interface::LSM6DSM_Io
{

public:

           LSM6DSM_IoSpi(hal::interface::SpiMasterControl & spi_master, hal::interface::DigitalOutPin & cs);
  virtual ~LSM6DSM_IoSpi();


  virtual void readRegister (interface::Register const reg, uint8_t       * data                          ) override;
  virtual void readRegister (interface::Register const reg, uint8_t       * data, uint16_t const num_bytes) override;
  virtual void writeRegister(interface::Register const reg, uint8_t const   data                          ) override;
  virtual void writeRegister(interface::Register const reg, uint8_t const * data, uint16_t const num_bytes) override;

private:

  hal::interface::SpiMasterControl & _spi_master;
  hal::interface::DigitalOutPin    & _cs;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LSM6DSM */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_LSM6DSM_IO_SPI_H_ */