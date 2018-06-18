/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3DSH_INTERFACE_LIS3DSH_CONTROL_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3DSH_INTERFACE_LIS3DSH_CONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/sensor/LIS3DSH/interface/LIS3DSH_Interface.h>
#include <spectre/driver/sensor/LIS3DSH/interface/LIS3DSH_Configuration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace LIS3DSH
{

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LIS3DSH_Control : public LIS3DSH_Interface,
                        public LIS3DSH_Configuration
{

public:

           LIS3DSH_Control() { }
  virtual ~LIS3DSH_Control() { }


  /* LIS3DSH Interface */

  virtual bool checkIfNewDataIsAvailable_XYZ(bool * is_new_data_available_xyz) = 0;
  virtual bool checkIfNewDataIsAvailable_X  (bool * is_new_data_available_x  ) = 0;
  virtual bool checkIfNewDataIsAvailable_Y  (bool * is_new_data_available_y  ) = 0;
  virtual bool checkIfNewDataIsAvailable_Z  (bool * is_new_data_available_z  ) = 0;

  virtual bool checkIfDataOverrun_XYZ       (bool * is_data_overrun_xyz      ) = 0;
  virtual bool checkIfDataOverrun_X         (bool * is_data_overrun_x        ) = 0;
  virtual bool checkIfDataOverrun_Y         (bool * is_data_overrun_y        ) = 0;
  virtual bool checkIfDataOverrun_Z         (bool * is_data_overrun_z        ) = 0;

  virtual bool readXYZAxis                  (int16_t * raw_x, int16_t * raw_y, int16_t * raw_z) = 0;
  virtual bool readXAxis                    (int16_t * raw_x                                  ) = 0;
  virtual bool readYAxis                    (int16_t * raw_y                                  ) = 0;
  virtual bool readZAxis                    (int16_t * raw_z                                  ) = 0;
  virtual bool readTemperature              (int8_t  * raw_temp                               ) = 0;


  /* LIS3DSH Configuration Interface */

  virtual bool setOutputDataRate            (OutputDataRate  const output_data_rate) = 0;
  virtual bool setFullScaleRange            (FullScaleRange  const full_scale_range) = 0;
  virtual bool setFilterBandwidth           (FilterBandwidth const filter_bandwidth) = 0;

  virtual bool enableFIFO                   () = 0;
  virtual bool disableFIFO                  () = 0;
  virtual bool enableBlockDataUpdate        () = 0;

  virtual bool enableXYZAxis                () = 0;
  virtual bool enableXAxis                  () = 0;
  virtual bool enableYAxis                  () = 0;
  virtual bool enableZAxis                  () = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* LIS3DSH */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_LIS3DSH_INTERFACE_LIS3DSH_CONTROL_H_ */
