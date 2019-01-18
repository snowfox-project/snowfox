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

#ifndef INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_RFM9X_IOSPI_H_
#define INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_RFM9X_IOSPI_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/lora/RFM9x/interface/RFM9x_Io.h>

#include <snowfox/hal/interface/gpio/DigitalOutPin.h>
#include <snowfox/hal/interface/spi/SpiMasterControl.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace lora
{

namespace RFM9x
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class RFM9x_IoSpi : public interface::RFM9x_Io
{

public:

           RFM9x_IoSpi(hal::interface::SpiMasterControl & spi_master, hal::interface::DigitalOutPin & cs);
  virtual ~RFM9x_IoSpi();


  virtual void readRegister  (interface::Register const reg, uint8_t       * data                      ) override;
  virtual void readRegister  (interface::Register const reg, uint8_t       * data, uint16_t const bytes) override;
  virtual void writeRegister (interface::Register const reg, uint8_t const   data                      ) override;
  virtual void writeRegister (interface::Register const reg, uint8_t const * data, uint16_t const bytes) override;

private:

  hal::interface::SpiMasterControl & _spi_master;
  hal::interface::DigitalOutPin    & _cs;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_RFM9X_IOSPI_H_ */
