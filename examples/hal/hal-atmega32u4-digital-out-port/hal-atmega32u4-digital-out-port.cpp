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
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA32U4/Delay.h>
#include <spectre/hal/avr/ATMEGA32U4/DigitalOutPort.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre::hal;

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

ATMEGA32U4::Delay          delay;
ATMEGA32U4::DigitalOutPort out_port(&DDRB, &PORTB);

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  for(;;)
  {
    out_port.set(0xCA); delay.delay_ms(100);
    out_port.set(0xFF); delay.delay_ms(100);
    out_port.set(0xEE); delay.delay_ms(100);
  }

  return 0;
}
