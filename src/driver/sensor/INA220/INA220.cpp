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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/sensor/INA220/INA220.h>

#include <string.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace INA220
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

INA220::INA220(interface::INA220_Control & ctrl)
: _ctrl(ctrl)
{

}

INA220::~INA220()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool INA220::open()
{
  return true; /* Do nothing */
}

ssize_t INA220::read(uint8_t * buffer, ssize_t const num_bytes)
{
  int16_t shunt_voltage = 0,
          bus_voltage   = 0;

  ssize_t const size = sizeof(shunt_voltage) + sizeof(bus_voltage);

  if(num_bytes < size)                        return -1;
  if(!_ctrl.readShuntVoltage(&shunt_voltage)) return -2;
  if(!_ctrl.readBusVoltage  (&bus_voltage  )) return -3;

  memcpy(buffer,                         &shunt_voltage, sizeof(shunt_voltage));
  memcpy(buffer + sizeof(shunt_voltage), &bus_voltage,   sizeof(bus_voltage  ));

  return size;
}

ssize_t INA220::write(uint8_t const * buffer, ssize_t const num_bytes)
{
  return -1; /* Not supported */
}

bool INA220::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* IOCTL_SET_BUS_VOLTAGE_RANGE ******************************************************/
  case IOCTL_SET_BUS_VOLTAGE_RANGE:
  {
    uint8_t                    const * arg_ptr           = static_cast<uint8_t *>                 (arg     );
    interface::BusVoltageRange const   bus_voltage_range = static_cast<interface::BusVoltageRange>(*arg_ptr);
    return _ctrl.setBusVoltageRange(bus_voltage_range);
  }
  break;
  /* IOCTL_SET_SHUNT_PGA_GAIN *********************************************************/
  case IOCTL_SET_SHUNT_PGA_GAIN:
  {
    uint8_t                 const * arg_ptr        = static_cast<uint8_t *>              (arg     );
    interface::ShuntPgaGain const   shunt_pga_gain = static_cast<interface::ShuntPgaGain>(*arg_ptr);
    return _ctrl.setShuntPgaGain(shunt_pga_gain);
  }
  break;
  /* IOCTL_SET_BUS_ADC_RESOLUTION *****************************************************/
  case IOCTL_SET_BUS_ADC_RESOLUTION:
  {
    uint8_t                     const * arg_ptr            = static_cast<uint8_t *>                  (arg     );
    interface::BusAdcResolution const   bus_adc_resolution = static_cast<interface::BusAdcResolution>(*arg_ptr);
    return _ctrl.setBusAdcResolution(bus_adc_resolution);
  }
  break;
  /* IOCTL_SET_SHUNT_ADC_RESOLUTION ***************************************************/
  case IOCTL_SET_SHUNT_ADC_RESOLUTION:
  {
    uint8_t                       const * arg_ptr              = static_cast<uint8_t *>                    (arg     );
    interface::ShuntAdcResolution const   shunt_adc_resolution = static_cast<interface::ShuntAdcResolution>(*arg_ptr);
    return _ctrl.setShuntAdcResolution(shunt_adc_resolution);
  }
  break;
  /* IOCTL_SET_OPERATING_MODE *********************************************************/
  case IOCTL_SET_OPERATING_MODE:
  {
    uint8_t                  const * arg_ptr        = static_cast<uint8_t *>               (arg     );
    interface::OperatingMode const   operating_mode = static_cast<interface::OperatingMode>(*arg_ptr);
    return _ctrl.setOperatingMode(operating_mode);
  }
  break;
  }

  return false;
}

void INA220::close()
{
  /* Do nothing */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* INA220 */

} /* sensor */

} /* driver */

} /* spectre */
