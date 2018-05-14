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

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/lora/RFM9x/DIO1/RFM9x_Dio1Configuration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace lora
{

namespace RFM9x
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RFM9x_Dio1Configuration::RFM9x_Dio1Configuration(interface::RFM9x_Io & io)
: _io(io)
{

}

RFM9x_Dio1Configuration::~RFM9x_Dio1Configuration()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_Dio1Configuration::setEventSource(interface::Dio1EventSource const event_source)
{
  uint8_t reg_dio_mapping_1_content = 0;

  _io.readRegister(interface::Register::DIO_MAPPING1, &reg_dio_mapping_1_content);

  reg_dio_mapping_1_content &= ~(RFM9x_REG_DIO_MAPPING_1_DIO1_MAPPING_1_bm | RFM9x_REG_DIO_MAPPING_1_DIO1_MAPPING_0_bm);
  reg_dio_mapping_1_content |= static_cast<uint8_t>(event_source);

  _io.writeRegister(interface::Register::DIO_MAPPING1, reg_dio_mapping_1_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */
