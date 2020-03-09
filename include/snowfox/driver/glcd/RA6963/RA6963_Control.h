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

#ifndef INCLUDE_SNOWFOX_DRIVER_GLCD_RA6963_RA6963_CONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_GLCD_RA6963_RA6963_CONTROL_H_

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

#include <snowfox/driver/glcd/RA6963/interface/RA6963_Control.h>

#include <snowfox/driver/glcd/RA6963/interface/RA6963_Data.h>

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

class RA6963_Control final : public interface::RA6963_Control
{

public:

           RA6963_Control(interface::RA6963_Data & data);
  virtual ~RA6963_Control();


  virtual void setGfxHomeAddress(uint16_t const   gfx_home_address                        ) override;
  virtual void setGfxArea       (uint8_t  const   gfx_columns                             ) override;
  virtual void setAddressPointer(uint16_t const   address_pointer                         ) override;
  virtual void write            (uint8_t  const * data,           uint32_t const num_bytes) override;


private:

  interface::RA6963_Data & _data;
  interface::OpMode        _mode;

  void setOperationMode(interface::OpMode const mode    );
  void writeData       (uint8_t           const data_val);
  void writeCommand    (uint8_t           const cmd_val );

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RA6963 */

} /* glcd */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_GLCD_RA6963_RA6963_CONTROL_H_ */
