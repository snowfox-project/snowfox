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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_AD7151_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_AD7151_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/sensor/AD7151/interface/AD7151_Interface.h>
#include <spectre/driver/sensor/AD7151/interface/AD7151_ConfigurationInterface.h>
#include <spectre/driver/sensor/AD7151/interface/AD7151_IO_Interface.h>

#include <spectre/driver/interface/Debug.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace AD7151
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AD7151 : public AD7151_Interface,
               public AD7151_ConfigurationInterface
{

public:

   AD7151(AD7151_IO_Interface & io);
  ~AD7151();


  /* AD7151 Interface */

  virtual bool startSingleConversion        (                                 ) override;
  virtual bool checkIfConversionIsComplete  (bool     * is_conversion_complete) override;
  virtual bool readConversionResult         (uint16_t * raw_data              ) override;


  /* AD7151 Configuration Interface */

  virtual bool setCapacitiveInputRange      (CapacitiveInputRangeSelect const sel) override;


          void debug_dumpAllRegs            (driver::interface::Debug & debug_interface);

private:

  AD7151_IO_Interface & _io;

  bool readSingleRegister   (RegisterSelect const reg_sel, uint8_t        * data);
  bool writeSingleRegister  (RegisterSelect const reg_sel, uint8_t const    data);

  void debug_dumpSingleReg  (driver::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AD7151 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_AD7151_H_ */
