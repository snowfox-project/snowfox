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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_BMG160_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_BMG160_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/sensor/BMG160/interface/BMG160_Interface.h>
#include <spectre/driver/sensor/BMG160/interface/BMG160_ConfigurationInterface.h>
#include <spectre/driver/sensor/BMG160/interface/BMG160_IO_Interface.h>

#include <spectre/debug/interface/Debug.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace BMG160
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class BMG160 : public BMG160_Interface,
               public BMG160_ConfigurationInterface
{

public:

           BMG160(BMG160_IO_Interface & io);
  virtual ~BMG160();


  /* BMG160 Interface */

  virtual bool readXYZAxis    (int16_t * raw_x, int16_t * raw_y, int16_t * raw_z) override;
  virtual bool readXAxis      (int16_t * raw_x                                  ) override;
  virtual bool readYAxis      (int16_t * raw_y                                  ) override;
  virtual bool readZAxis      (int16_t * raw_z                                  ) override;
  virtual bool readTemperature(int8_t  * raw_temp                               ) override;


  /* BMG160 Configuration Interface */

  virtual bool setOutputDataRateAndBandwith (OutputDataRateAndBandwithSelect const sel) override;
  virtual bool setFullScale                 (FullScaleSelect                 const sel) override;

          void debug_dumpAllRegs            (debug::interface::Debug & debug_interface);

private:

  BMG160_IO_Interface & _io;

  bool readSingleRegister   (RegisterSelect const reg_sel, uint8_t       * data);
  bool writeSingleRegister  (RegisterSelect const reg_sel, uint8_t const   data);

  void debug_dumpSingleReg  (debug::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* BMG160 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_BMG160_H_ */
