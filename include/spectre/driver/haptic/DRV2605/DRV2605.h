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

#ifndef INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605_DRV2605_H_
#define INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605_DRV2605_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/interface/Driver.h>

#include <spectre/driver/haptic/DRV2605/interface/DRV2605_ControlInterface.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace haptic
{

namespace DRV2605
{

/**************************************************************************************
 * CLASS DECLARATION DRV2605
 **************************************************************************************/

class DRV2605 : public interface::Driver
{

public:

           DRV2605(DRV2605_ControlInterface & ctrl);
  virtual ~DRV2605();


  virtual bool open (                                                   ) override;
  virtual bool read (uint8_t        * buffer, uint32_t const   num_bytes) override;
  virtual bool write(uint8_t  const * buffer, uint32_t const   num_bytes) override;
  virtual bool ioctl(uint32_t const   cmd,    void           * arg      ) override;
  virtual bool close(                                                   ) override;

private:

  DRV2605_ControlInterface & _ctrl;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* DRV2605 */

} /* haptic */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605_DRV2605_H_ */
