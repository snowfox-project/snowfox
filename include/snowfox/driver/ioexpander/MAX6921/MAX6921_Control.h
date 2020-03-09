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

#ifndef INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MAX6921_MAX6921_CONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MAX6921_MAX6921_CONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/ioexpander/MAX6921/interface/MAX6921_Control.h>

#include <snowfox/driver/ioexpander/MAX6921/interface/MAX6921_Io.h>

#include <snowfox/hal/interface/delay/Delay.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace ioexpander
{

namespace MAX6921
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MAX6921_Control final : public interface::MAX6921_Control
{

public:

           MAX6921_Control(interface::MAX6921_Io & io,
                           hal::interface::Delay & delay);
  virtual ~MAX6921_Control();

  virtual void setSegment(uint8_t const seg_number) override;
  virtual void clrSegment(uint8_t const seg_number) override;
  virtual void write     () override;
  virtual void load      () override;
  virtual void blank     () override;
  virtual void noBlank   () override;

private:

  interface::MAX6921_Io           & _io;
  hal::interface::Delay           & _delay;
  interface::SegmentControlBuffer   _seg_ctrl_buf;

  void initSegCtrlBuf();

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MAX6921 */

} /* ioexpander */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_IOEXPANDER_MAX6921_MAX6921_CONTROL_H_ */