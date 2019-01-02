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

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA328P/Delay.h>
#include <spectre/hal/avr/ATMEGA328P/DigitalOutPin.h>
#include <spectre/hal/avr/ATMEGA328P/DigitalInOutPort.h>

#include <spectre/driver/tlcd/HD44780/HD44780.h>
#include <spectre/driver/tlcd/HD44780/HD44780_Control.h>
#include <spectre/driver/tlcd/HD44780/HD44780_IoGpio8Bit.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /************************************************************************************
   * HAL
   ************************************************************************************/

  ATMEGA328P::Delay             delay;
  ATMEGA328P::DigitalOutPin     rs    (&DDRB, &PORTB, 2    ); /* PB2   */
  ATMEGA328P::DigitalOutPin     rw    (&DDRB, &PORTB, 1    ); /* PB1   */
  ATMEGA328P::DigitalOutPin     enable(&DDRB, &PORTB, 0    ); /* PB0   */
  ATMEGA328P::DigitalInOutPort  data  (&DDRD, &PORTD, &PIND); /* PD7-0 */


  /************************************************************************************
   * DRIVER
   ************************************************************************************/

  tlcd::HD44780::HD44780_IoGpio8Bit hd44780_io  (delay, rs, rw, enable, data);
  tlcd::HD44780::HD44780_Control    hd44780_ctrl(hd44780_io);
  tlcd::HD44780::HD44780            hd44780     (hd44780_ctrl);

  hd44780.open();
  hd44780.ioctl(tlcd::HD44780::IOCTL_CLEAR_DISPLAY, 0);

  /************************************************************************************
   * APPLICATION
   ************************************************************************************/

  for(;;)
  {
  }

  hd44780.close();

  return 0;
}
