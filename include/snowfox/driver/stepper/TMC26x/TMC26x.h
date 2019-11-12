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

#ifndef INCLUDE_SNOWFOX_DRIVER_STEPPER_TMC26X_TMC26X_H_
#define INCLUDE_SNOWFOX_DRIVER_STEPPER_TMC26X_TMC26X_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/interface/Driver.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace stepper
{

namespace TMC26x
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class TMC26x final : public driver::interface::Driver
{

public:

           TMC26x();
  virtual ~TMC26x();


  bool    open (                                                  ) override final;
  ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override final;
  ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override final;
  bool    ioctl(uint32_t const   cmd,    void          * arg      ) override final;
  void    close(                                                  ) override final;


};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* TMC26x */

} /* stepper */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_STEPPER_TMC26X_TMC26X_H_ */
