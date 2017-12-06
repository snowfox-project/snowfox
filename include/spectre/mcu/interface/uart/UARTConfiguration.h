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

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace mcu
{

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class UARTConfiguration
{

public:

  typedef enum
  {
    B115200
  } eBaudRate;

  typedef enum
  {
    None,
    Even,
    Odd
  } eParity;

  typedef enum
  {
    _1,
    _2
  } eStopBit;


           UARTConfiguration() { }
  virtual ~UARTConfiguration() { }


  virtual void setBaudRate  (eBaudRate const baud_rate) = 0;
  virtual void setParity    (eParity   const parity   ) = 0;
  virtual void setStopBit   (eStopBit  const stop_bit ) = 0;
  
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface*/

} /* mcu */

} /* spectre */
