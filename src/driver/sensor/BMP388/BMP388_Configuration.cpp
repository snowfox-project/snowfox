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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/BMP388/BMP388_Configuration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace BMP388
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

BMP388_Configuration::BMP388_Configuration(interface::BMP388_Io & io)
: _io{io}
{

}

BMP388_Configuration::~BMP388_Configuration()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void BMP388_Configuration::configPressureOversampling(interface::PressureOversampling const over_sampling)
{
  _io.modifyRegister(interface::Register::OSR,
             util::bm(interface::OSR::OSR_P_2) | util::bm(interface::OSR::OSR_P_1) | util::bm(interface::OSR::OSR_P_0),
             util::to_integer(over_sampling));
}

void BMP388_Configuration::configTemperatureOversampling(interface::TemperatureOversampling const over_sampling)
{
  _io.modifyRegister(interface::Register::OSR,
             util::bm(interface::OSR::OSR_T_2) | util::bm(interface::OSR::OSR_T_1) | util::bm(interface::OSR::OSR_T_0),
             util::to_integer(over_sampling));
}

void BMP388_Configuration::configOutputDataRate(interface::OutputDataRate const odr)
{
  _io.writeRegister(interface::Register::ODR, util::to_integer(odr));
}

void BMP388_Configuration::setIntPinOutputType(interface::IntPinOutputType const type)
{
  _io.modifyRegister(interface::Register::INT_CTRL,
                     util::bm(interface::INT_CTRL::INT_OD),
                     util::to_integer(type));
}

void BMP388_Configuration::enableInterrupt(interface::Interrupt const interrupt)
{
  _io.setBit(interface::Register::INT_CTRL, util::to_integer(interrupt));
}

void BMP388_Configuration::disableInterrupt(interface::Interrupt const interrupt)
{
  _io.clrBit(interface::Register::INT_CTRL, util::to_integer(interrupt));
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* BMP388 */

} /* sensor */

} /* driver */

} /* snowfox */
