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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/BMP388/interface/BMP388_Control.h>
#include <snowfox/driver/sensor/BMP388/interface/BMP388_Configuration.h>

#include <snowfox/driver/interface/Driver.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensor::BMP388
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

union SensorData
{
  struct __attribute__((packed))
  {
    float pressure_hpa;
    float temperature_deg;
  } data;
  uint8_t buf[sizeof(data)];
};

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_SET_PRESSURE_OVERSAMPLING    = 0; /* Arg: interface::PressureOversampling * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_TEMPERATURE_OVERSAMPLING = 1; /* Arg: interface::TemperatureOversampling * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_OUTPUT_DATA_RATE         = 2; /* Arg: interface::OutputDataRate * -> uint8_t *  */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class BMP388 final : public driver::interface::Driver
{

public:

           BMP388(interface::BMP388_Configuration & config,
                  interface::BMP388_Control       & control);
  virtual ~BMP388();


  virtual bool    open (                                                  ) override;
  virtual ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override;
  virtual ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override;
  virtual bool    ioctl(uint32_t const   cmd,    void          * arg      ) override;
  virtual void    close(                                                  ) override;


private:

  interface::BMP388_Configuration & _config;
  interface::BMP388_Control       & _control;

  SensorData _sensor_data;

  interface::QuantizedCalibrationData _quant_calib_data;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensor::BMP388 */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_BMP388_H_ */
