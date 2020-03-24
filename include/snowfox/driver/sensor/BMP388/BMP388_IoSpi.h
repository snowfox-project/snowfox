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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_IO_SPI_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_IO_SPI_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/BMP388/interface/BMP388_Io.h>

#include <snowfox/hal/interface/gpio/DigitalOutPin.h>
#include <snowfox/hal/interface/spi/SpiMasterControl.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace BMP388
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class BMP388_IoSpi : public interface::BMP388_Io
{

public:

           BMP388_IoSpi(hal::interface::SpiMasterControl & spi_master, hal::interface::DigitalOutPin & cs);
  virtual ~BMP388_IoSpi();


  virtual void readRegister (interface::Register const reg, uint8_t       * data, uint16_t const num_bytes) override;
  virtual void writeRegister(interface::Register const reg, uint8_t const * data, uint16_t const num_bytes) override;


private:

  hal::interface::SpiMasterControl & _spi_master;
  hal::interface::DigitalOutPin    & _cs;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* BMP388 */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_IO_SPI_H_ */
