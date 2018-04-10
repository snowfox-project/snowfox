/**
 * lora-sniffer is a LoRa packet sniffer based on the HopeRF RF95.
 * Copyright (C) 2018 Alexander Entinger / LXRobotics GmbH
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

#include <lora-sniffer/SerialWriter.h>

#include <string.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace application
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

SerialWriter::SerialWriter(spectre::driver::interface::Driver & serial)
: _serial(serial)
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void SerialWriter::write(char const * str)
{
  uint16_t const length = strlen(str);

  for(ssize_t bytes_written = 0; bytes_written != length; )
  {
    bytes_written += _serial.write(reinterpret_cast<uint8_t const *>(str) + bytes_written, length - bytes_written);
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* application */
