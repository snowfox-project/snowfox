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

#ifndef INCLUDE_SPECTRE_HAL_AVR_INTERFACE_I2C_I2CMASTER_H_
#define INCLUDE_SPECTRE_HAL_AVR_INTERFACE_I2C_I2CMASTER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATxxxx
{

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class I2CMasterMCU
{

public:

           I2CMasterMCU() { }
  virtual ~I2CMasterMCU() { }


  virtual bool start                 (uint8_t const   address                                  ) = 0;
  virtual bool transmitByte          (uint8_t const   data                                     ) = 0;
  virtual void receiveByteAndSendACK (uint8_t       * data                                     ) = 0;
  virtual void receiveByteAndSendNACK(uint8_t       * data                                     ) = 0;
  virtual void stop                  (                                                         ) = 0;

  virtual void setTWIPrescaler       (uint32_t const prescaler                                 ) = 0;
  virtual void setTWBR               (uint32_t const i2c_speed_Hz, uint32_t const i2c_prescaler) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* ATxxxx */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_INTERFACE_I2C_I2CMASTER_H_ */
