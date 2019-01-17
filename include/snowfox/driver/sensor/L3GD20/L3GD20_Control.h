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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_L3GD20_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_L3GD20_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/L3GD20/interface/L3GD20_Control.h>

#include <snowfox/driver/sensor/L3GD20/interface/L3GD20_Io.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace L3GD20
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class L3GD20_Control : public interface::L3GD20_Control
{

public:

           L3GD20_Control(interface::L3GD20_Io & io);
  virtual ~L3GD20_Control();


  /* L3GD20 Interface */

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


  /* L3GD20 Configuration Interface */

  virtual bool enablePower                  () override;
  virtual bool disableAllAxis               () override;
  virtual bool enableBlockDataUpdate        () override;

  virtual bool setOutputDataRateAndBandwith (interface::OutputDataRateAndBandwith const output_data_rate_and_bandwidth) override;
  virtual bool setFullScaleRange            (interface::FullScaleRange            const full_scale_range              ) override;

  virtual bool enableXYZAxis                () override;
  virtual bool enableXAxis                  () override;
  virtual bool enableYAxis                  () override;
  virtual bool enableZAxis                  () override;


private:

  interface::L3GD20_Io & _io;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* L3GD20 */

} /* sensor */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_L3GD20_H_ */
