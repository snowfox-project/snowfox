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

#ifndef INCLUDE_SPECTRE_COMSTACK_CANOPEN_CANFRAME_H_
#define INCLUDE_SPECTRE_COMSTACK_CANOPEN_CANFRAME_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class CanFrame
{

public:

  CanFrame();

  bool isExtendedId() const;
  bool isRTR       () const;
  bool isErrorFrame() const;

private:

  uint32_t _id;
  uint8_t  _dlc,
           _data[8];
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_COMSTACK_CANOPEN_CANFRAME_H_ */
