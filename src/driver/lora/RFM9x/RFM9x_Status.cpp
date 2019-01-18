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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/lora/RFM9x/RFM9x_Status.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
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

RFM9x_Status::RFM9x_Status(interface::RFM9x_Io & io)
: _io(io)
{

}

RFM9x_Status::~RFM9x_Status()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

int16_t RFM9x_Status::getCurrentRssi()
{
  uint8_t reg_rssi_value_content = 0;

  _io.readRegister(interface::Register::RSSI_VALUE, &reg_rssi_value_content);

  int16_t const current_rssi_dbm = -137 + reg_rssi_value_content;

  return current_rssi_dbm;
}

int16_t RFM9x_Status::getLastPacketRssi()
{
  uint8_t reg_packet_rssi_content = 0;

  _io.readRegister(interface::Register::PKT_RSSI_VALUE, &reg_packet_rssi_content);

  int16_t const last_packet_rssi_dbm = -137 + reg_packet_rssi_content;

  return last_packet_rssi_dbm;
}

int8_t RFM9x_Status::getLastPacketSnr()
{
  int8_t reg_packet_snr_content = 0;

  _io.readRegister(interface::Register::PKT_SNR_VALUE, reinterpret_cast<uint8_t *>(&reg_packet_snr_content));

  int8_t last_packet_snr = reg_packet_snr_content / 4;

  return last_packet_snr;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* snowfox */
