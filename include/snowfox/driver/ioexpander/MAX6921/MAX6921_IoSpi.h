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

#ifndef INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MAX6921_MAX6921_IOSPI_H_
#define INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MAX6921_MAX6921_IOSPI_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/ioexpander/MAX6921/interface/MAX6921_Io.h>

#include <snowfox/hal/interface/gpio/DigitalOutPin.h>
#include <snowfox/hal/interface/spi/SpiMasterControl.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::ioexpander::MAX6921
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MAX6921_IoSpi final : public interface::MAX6921_Io
{

public:

           MAX6921_IoSpi(hal::interface::SpiMasterControl & spi_master, 
                         hal::interface::DigitalOutPin    & load,
                         hal::interface::DigitalOutPin    & blank);
  virtual ~MAX6921_IoSpi();


  virtual void write   (interface::SegmentControlBuffer const & seg_ctrl_buf) override;
  virtual void setLoad () override;
  virtual void clrLoad () override;
  virtual void setBlank() override;
  virtual void clrBlank() override;


private:

  hal::interface::SpiMasterControl & _spi_master;
  hal::interface::DigitalOutPin    & _load;
  hal::interface::DigitalOutPin    & _blank;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::ioexpander::MAX6921 */

#endif /* INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MAX6921_MAX6921_IOSPI_H_ */
