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

#ifndef INCLUDE_SNOWFOX_DRIVER_TLCD_HD44780_HD44780_CONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_TLCD_HD44780_HD44780_CONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/tlcd/HD44780/interface/HD44780_Control.h>

#include <snowfox/driver/tlcd/HD44780/interface/HD44780_Io.h>

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

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class HD44780_Control : public interface::HD44780_Control
{

public:

           HD44780_Control(interface::HD44780_Io & io);
  virtual ~HD44780_Control();


  virtual void turnDisplayOn        () override;
  virtual void turnDisplayOff       () override;
  virtual void enableCursor         () override;
  virtual void disableCursor        () override;
  virtual void turnCursonBlinkingOn () override;
  virtual void turnCursonBlinkingOff() override;

  virtual void clear                () override;
  virtual void home                 () override;


private:

  interface::HD44780_Io & _io;
  uint8_t                 _display_control;


  void writeDisplayControlCommand();

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* HD44780 */

} /* tlcd */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_TLCD_HD44780_HD44780_CONTROL_H_ */
