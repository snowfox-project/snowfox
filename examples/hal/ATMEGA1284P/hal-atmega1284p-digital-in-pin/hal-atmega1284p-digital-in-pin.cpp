/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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
 * This example program is tailored for usage with Moteino-Mega-USB
 *
 * Electrical interface:
 *   LED    = D15 = PD7
 *   SWITCH = D0  = PB0
 *
 * Upload via avrdude
 *   avrdude -p atmega1284p -c arduino -e -U flash:w:bin/hal-atmega1284p-digital-in-pin
 **************************************************************************************/

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA1284P/DigitalInPin.h>
#include <spectre/hal/avr/ATMEGA1284P/DigitalOutPin.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre::hal;

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

ATMEGA1284P::DigitalInPin  switch_in(&DDRB, &PORTB, &PINB, PB0);
ATMEGA1284P::DigitalOutPin led_out  (&DDRD, &PORTD, PD7);

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  switch_in.setPullUpMode(interface::PullUpMode::PULL_UP);

  for(;;)
  {
    if  (switch_in.isSet()) led_out.set();
    else                    led_out.clr();
  }

  return 0;
}
