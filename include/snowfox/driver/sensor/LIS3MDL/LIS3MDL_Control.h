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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS3MDL_LIS3MDL_CONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS3MDL_LIS3MDL_CONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/LIS3MDL/interface/LIS3MDL_Control.h>

#include <snowfox/driver/sensor/LIS3MDL/interface/LIS3MDL_Io.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
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

class LIS3MDL_Control final : public interface::LIS3MDL_Control
{

public:

           LIS3MDL_Control(interface::LIS3MDL_Io & io);
  virtual ~LIS3MDL_Control();


  /* LIS3MDL Interface */

  virtual bool checkIfNewDataIsAvailable_XYZ(bool * is_new_data_available_xyz) override final;
  virtual bool checkIfNewDataIsAvailable_X  (bool * is_new_data_available_x  ) override final;
  virtual bool checkIfNewDataIsAvailable_Y  (bool * is_new_data_available_y  ) override final;
  virtual bool checkIfNewDataIsAvailable_Z  (bool * is_new_data_available_z  ) override final;

  virtual bool checkIfDataOverrun_XYZ       (bool * is_data_overrun_xyz      ) override final;
  virtual bool checkIfDataOverrun_X         (bool * is_data_overrun_x        ) override final;
  virtual bool checkIfDataOverrun_Y         (bool * is_data_overrun_y        ) override final;
  virtual bool checkIfDataOverrun_Z         (bool * is_data_overrun_z        ) override final;

  virtual bool readXYZAxis                  (int16_t * raw_x, int16_t * raw_y, int16_t * raw_z) override final;
  virtual bool readXAxis                    (int16_t * raw_x                                  ) override final;
  virtual bool readYAxis                    (int16_t * raw_y                                  ) override final;
  virtual bool readZAxis                    (int16_t * raw_z                                  ) override final;
  virtual bool readTemperature              (int16_t * raw_temp                               ) override final;


  /* LIS3MDL Configuration Interface */

  virtual bool setOperationMode_XY          (interface::OperationMode_XY const operation_mode_xy) override final;
  virtual bool setOperationMode_Z           (interface::OperationMode_Z  const operation_mode_z ) override final;
  virtual bool setOutputDataRate            (interface::OutputDataRate   const output_data_rate ) override final;
  virtual bool setFullScaleRange            (interface::FullScaleRange   const full_scale_range ) override final;
  virtual bool setConversionMode            (interface::ConversionMode   const conversion_mode  ) override final;
  virtual bool enableTemperatureSensor      (                                                   ) override final;
  virtual bool enableBlockDataUpdate        (                                                   ) override final;


private:

  interface::LIS3MDL_Io & _io;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS3MDL */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_LIS3MDL_LIS3MDL_CONTROL_H_ */
