/**
 * Spectre is a modular RTOS with extensive IO support.
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

#include <spectre/driver/tlcd/HD44780/HD44780_Control.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace tlcd
{

namespace HD44780
{

/**************************************************************************************
 * DEFINE
 **************************************************************************************/

/* Flags for command DisplayControl ***************************************************/
#define DISPLAY_CONTROL_DISPLAY_ON_bm (1<<2)
#define DISPLAY_CONTROL_CURSON_ON_bm  (1<<1)
#define DISPLAY_CONTROL_BLINK_ON_bm   (1<<0)

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class HD44780Command : uint8_t
{
  ClearDisplay   = 0x01,
  ReturnHome     = 0x02,
  EntryModeSet   = 0x04,
  DisplayControl = 0x08,
  CurDispShift   = 0x10,
  FunctionSet    = 0x20,
  SetCGRAMAddr   = 0x40,
  SetDDRAMAddr   = 0x80
};

/**************************************************************************************
 * INLINE FUNCTIONS
 **************************************************************************************/

inline uint8_t toCmd(HD44780Command const cmd) { return static_cast<uint8_t>(cmd); }

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

HD44780_Control::HD44780_Control(interface::HD44780_Io & io)
: _io             (io),
  _display_control(0 )
{

}

HD44780_Control::~HD44780_Control()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void HD44780_Control::turnDisplayOn()
{
  _display_control |= DISPLAY_CONTROL_DISPLAY_ON_bm;
  writeDisplayControlCommand();
}

void HD44780_Control::turnDisplayOff()
{
  _display_control &= ~DISPLAY_CONTROL_DISPLAY_ON_bm;
  writeDisplayControlCommand();
}

void HD44780_Control::enableCursor()
{
  _display_control |= DISPLAY_CONTROL_CURSON_ON_bm;
  writeDisplayControlCommand();
}

void HD44780_Control::disableCursor()
{
  _display_control &= ~DISPLAY_CONTROL_CURSON_ON_bm;
  writeDisplayControlCommand();
}

void HD44780_Control::turnCursonBlinkingOn()
{
  _display_control |= DISPLAY_CONTROL_BLINK_ON_bm;
  writeDisplayControlCommand();

}

void HD44780_Control::turnCursonBlinkingOff()
{
  _display_control &= ~DISPLAY_CONTROL_BLINK_ON_bm;
  writeDisplayControlCommand();
}

void HD44780_Control::clear()
{
  _io.writeCommand(toCmd(HD44780Command::ClearDisplay));
}

void HD44780_Control::home()
{
  _io.writeCommand(toCmd(HD44780Command::ReturnHome));
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void HD44780_Control::writeDisplayControlCommand()
{
  _io.writeCommand(toCmd(HD44780Command::DisplayControl) | _display_control);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* HD44780 */

} /* tlcd */

} /* driver */

} /* spectre */
