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

#include <lora-sniffer/SerialReader.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace application
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

SerialReader::SerialReader(spectre::driver::interface::Driver & serial)
: _serial(serial)
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool SerialReader::readUntil(char const key, char * msg_buf, uint16_t const num_bytes)
{
  uint16_t bytes_read     = 0;
  char     last_byte_read = 0;

  do
  {
    if(readByte(last_byte_read))
    {
      msg_buf[bytes_read] = last_byte_read;
      bytes_read++;
    }
  } while(last_byte_read != key && bytes_read < num_bytes);

  if(bytes_read < num_bytes)
  {
    msg_buf[bytes_read] = '\0';
    return true;
  }
  else
  {
    return false;
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

bool SerialReader::readByte(char & byte)
{
  uint8_t buf = 0;
  bool const success = _serial.read(&buf, 1) == 1;
  byte = static_cast<char>(buf);
  return success;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* application */
