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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3MDL_LIS3MDL_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3MDL_LIS3MDL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/sensor/LIS3MDL/interface/LIS3MDL_Control.h>

#include <spectre/debug/interface/Debug.h>

#include <spectre/driver/sensor/LIS3MDL/interface/LIS3MDL_Io.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace LIS3MDL
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LIS3MDL_Control : public interface::LIS3MDL_Control
{

public:

           LIS3MDL_Control(interface::LIS3MDL_Io & io);
  virtual ~LIS3MDL_Control();


  /* LIS3MDL Interface */

  virtual bool checkIfNewDataIsAvailable_XYZ(bool * is_new_data_available_xyz) override;
  virtual bool checkIfNewDataIsAvailable_X  (bool * is_new_data_available_x  ) override;
  virtual bool checkIfNewDataIsAvailable_Y  (bool * is_new_data_available_y  ) override;
  virtual bool checkIfNewDataIsAvailable_Z  (bool * is_new_data_available_z  ) override;

  virtual bool checkIfDataOverrun_XYZ       (bool * is_data_overrun_xyz      ) override;
  virtual bool checkIfDataOverrun_X         (bool * is_data_overrun_x        ) override;
  virtual bool checkIfDataOverrun_Y         (bool * is_data_overrun_y        ) override;
  virtual bool checkIfDataOverrun_Z         (bool * is_data_overrun_z        ) override;

  virtual bool readXYZAxis                  (int16_t * raw_x, int16_t * raw_y, int16_t * raw_z) override;
  virtual bool readXAxis                    (int16_t * raw_x                                  ) override;
  virtual bool readYAxis                    (int16_t * raw_y                                  ) override;
  virtual bool readZAxis                    (int16_t * raw_z                                  ) override;
  virtual bool readTemperature              (int16_t * raw_temp                               ) override;


  /* LIS3MDL Configuration Interface */

  virtual bool setOperativeMode_XY          (interface::OperativeMode_XY        const sel) override;
  virtual bool setOperativeMode_Z           (interface::OperativeMode_Z         const sel) override;
  virtual bool setOutputDataRate            (interface::OutputDataRateSelection const sel) override;
  virtual bool setFullScale                 (interface::FullScaleRangeSelect    const sel) override;
  virtual bool setConversionMode            (interface::ConversionMode          const sel) override;
  virtual bool enableTemperatureSensor      (                                            ) override;
  virtual bool enableBlockDataUpdate        (                                            ) override;


          void debug_dumpAllRegs            (debug::interface::Debug & debug_interface);

private:

  interface::LIS3MDL_Io & _io;

  void debug_dumpSingleReg  (debug::interface::Debug & debug_interface, char const * msg, interface::Register const reg);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS3MDL */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3MDL_LIS3MDL_H_ */
