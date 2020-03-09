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

#ifndef INCLUDE_SNOWFOX_DRIVER_GLCD_RA6963_RA6963_IO_GPIO_8BIT_H_
#define INCLUDE_SNOWFOX_DRIVER_GLCD_RA6963_RA6963_IO_GPIO_8BIT_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/glcd/RA6963/interface/RA6963_Io.h>

#include <snowfox/hal/interface/delay/Delay.h>
#include <snowfox/hal/interface/gpio/DigitalOutPin.h>
#include <snowfox/hal/interface/gpio/DigitalInOutPort.h>

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

class RA6963_IoGpio8Bit final : public interface::RA6963_Io
{

public:

           RA6963_IoGpio8Bit(hal::interface::Delay                     & delay,
                             hal::interface::DigitalOutPin             & wr,
                             hal::interface::DigitalOutPin             & rd,
                             hal::interface::DigitalOutPin             & ce,
                             hal::interface::DigitalOutPin             & c_d,
                             hal::interface::DigitalOutPin             & rst,
                             hal::interface::DigitalOutPin             & fs,
                             hal::interface::DigitalInOutPort<uint8_t> & data);
  virtual ~RA6963_IoGpio8Bit();


  virtual void    reset       (                      ) override;
  virtual uint8_t readStatus  (                      ) override;
  virtual uint8_t readData    (                      ) override;
  virtual void    writeData   (uint8_t const data_val) override;
  virtual void    writeCommand(uint8_t const cmd_val ) override;

private:

  hal::interface::Delay                     & _delay;

  hal::interface::DigitalOutPin             & _wr,
                                            & _rd,
                                            & _ce,
                                            & _c_d,
                                            & _rst,
                                            & _fs;

  hal::interface::DigitalInOutPort<uint8_t> & _data;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RA6963 */

} /* glcd */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_GLCD_RA6963_RA6963_IO_GPIO_8BIT_H_ */
