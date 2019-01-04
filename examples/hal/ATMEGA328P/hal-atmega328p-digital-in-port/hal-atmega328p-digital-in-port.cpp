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

#include <stdio.h>

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA328P/DigitalInPort.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre::hal;

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

ATMEGA328P::DigitalInPort in_port(&DDRB, &PORTB, &PINB);

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  in_port.setPullUpMode(interface::PullUpMode::PULL_UP);

  for(;;)
  {
    uint8_t const in_port_val = in_port.get();

    char msg[32];
    snprintf(msg, 32, "PORTB = %02X\n", in_port_val);
  }

  return 0;
}
