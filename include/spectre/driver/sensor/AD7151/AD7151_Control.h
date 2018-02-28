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

#include <spectre/driver/sensor/AD7151/interface/AD7151_Control.h>

#include <spectre/debug/interface/Debug.h>

#include <spectre/driver/sensor/AD7151/interface/AD7151_Io.h>

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

class AD7151_Control : public interface::AD7151_Control
{

public:

           AD7151_Control(interface::AD7151_IO_Interface & io);
  virtual ~AD7151_Control();


  /* AD7151 Interface */

  virtual bool startSingleConversion        (                                 ) override;
  virtual bool checkIfConversionIsComplete  (bool     * is_conversion_complete) override;
  virtual bool readConversionResult         (uint16_t * raw_data              ) override;


  /* AD7151 Configuration Interface */

  virtual bool setCapacitiveInputRange      (interface::CapacitiveInputRangeSelect const sel) override;


          void debug_dumpAllRegs            (debug::interface::Debug & debug_interface);

private:

  interface::AD7151_IO_Interface & _io;

  bool readSingleRegister   (interface::Register const reg, uint8_t        * data);
  bool writeSingleRegister  (interface::Register const reg, uint8_t const    data);

  void debug_dumpSingleReg  (debug::interface::Debug & debug_interface, char const * msg, interface::Register const reg);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AD7151 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_AD7151_H_ */
