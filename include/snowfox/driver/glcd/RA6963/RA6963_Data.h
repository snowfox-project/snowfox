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

#ifndef INCLUDE_SNOWFOX_DRIVER_GLCD_RA6963_RA6963_DATA_H_
#define INCLUDE_SNOWFOX_DRIVER_GLCD_RA6963_RA6963_DATA_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/glcd/RA6963/interface/RA6963_Data.h>

#include <snowfox/driver/glcd/RA6963/interface/RA6963_Io.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace glcd
{

namespace RA6963
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class RA6963_Data : public interface::RA6963_Data
{

public:

           RA6963_Data(interface::RA6963_Io & io);
  virtual ~RA6963_Data();


  virtual uint8_t readData    (interface::OpMode const mode                        ) override;
  virtual void    writeData   (interface::OpMode const mode, uint8_t const data_val) override;
  virtual void    writeCommand(interface::OpMode const mode, uint8_t const cmd_val ) override;

private:

  interface::RA6963_Io & _io;

  void waitForReady     (interface::OpMode const mode                      ) const;
  bool isReady          (interface::OpMode const mode, uint8_t const status) const;
  bool isReadyNormalMode(                              uint8_t const status) const;
  bool isReadyAutoMode  (                              uint8_t const status) const;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RA6963 */

} /* glcd */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_GLCD_RA6963_RA6963_DATA_H_ */
