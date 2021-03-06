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

#ifndef INCLUDE_SNOWFOX_DRIVER_TLCD_HD44780_IOGPIO8BIT_H_
#define INCLUDE_SNOWFOX_DRIVER_TLCD_HD44780_IOGPIO8BIT_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/tlcd/HD44780/interface/HD44780_Io.h>

#include <snowfox/hal/interface/delay/Delay.h>
#include <snowfox/hal/interface/gpio/DigitalOutPin.h>
#include <snowfox/hal/interface/gpio/DigitalInOutPort.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::tlcd::HD44780
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class HD44780_IoGpio8Bit final : public interface::HD44780_Io
{

public:

           HD44780_IoGpio8Bit(hal::interface::Delay                     & delay,
                              hal::interface::DigitalOutPin             & rs,
                              hal::interface::DigitalOutPin             & rw,
                              hal::interface::DigitalOutPin             & enable,
                              hal::interface::DigitalInOutPort<uint8_t> & data);
  virtual ~HD44780_IoGpio8Bit();


  virtual uint8_t readStatus  (                      ) override;
  virtual void    writeData   (uint8_t const data_val) override;
  virtual void    writeCommand(uint8_t const cmd_val ) override;


private:


  hal::interface::Delay                     & _delay;
  hal::interface::DigitalOutPin             & _rs,
                                            & _rw,
                                            & _enable;
  hal::interface::DigitalInOutPort<uint8_t> & _data;


};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::tlcd::HD44780 */

#endif /* INCLUDE_SNOWFOX_DRIVER_TLCD_HD44780_IOGPIO8BIT_H_ */
