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

#ifndef INCLUDE_SNOWFOX_DRIVER_TLCD_HD44780_INTERFACE_HD44780_CONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_TLCD_HD44780_INTERFACE_HD44780_CONTROL_H_

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace tlcd
{

namespace HD44780
{

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class HD44780_Control
{

public:

           HD44780_Control() { }
  virtual ~HD44780_Control() { }


  virtual void turnDisplayOn        () = 0;
  virtual void turnDisplayOff       () = 0;
  virtual void enableCursor         () = 0;
  virtual void disableCursor        () = 0;
  virtual void turnCursonBlinkingOn () = 0;
  virtual void turnCursonBlinkingOff() = 0;

  virtual void clear                () = 0;
  virtual void home                 () = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* HD44780 */

} /* tlcd */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_TLCD_HD44780_INTERFACE_HD44780_CONTROL_H_ */
