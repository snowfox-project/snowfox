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
 * This code is tailored for usage with the AVR-Development Module with
 * 128K Bytes external SRAM "AL-ERAM128_CAN V2.0" and the RA6963 based
 * 128 x 64 GLCD module with the Farnell ordering number 2675708
 **************************************************************************************/

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>

#include <spectre/hal/avr/AT90CAN128/Delay.h>
#include <spectre/hal/avr/AT90CAN128/DigitalOutPin.h>
#include <spectre/hal/avr/AT90CAN128/DigitalInOutPort.h>

#include <spectre/driver/glcd/RA6963/RA6963.h>
#include <spectre/driver/glcd/RA6963/RA6963_Data.h>
#include <spectre/driver/glcd/RA6963/RA6963_Control.h>
#include <spectre/driver/glcd/RA6963/RA6963_IoGpio8Bit.h>

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint16_t const WIDTH    = 128;
static uint16_t const HEIGTH   =  64;

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
  /* HAL ******************************************************************************/

  AT90CAN128::Delay             delay;

  AT90CAN128::DigitalOutPin     wr (&DDRF, &PORTF, 3);      /* PF3 */
  AT90CAN128::DigitalOutPin     rd (&DDRF, &PORTF, 2);      /* PF2 */
  AT90CAN128::DigitalOutPin     ce (&DDRF, &PORTF, 1);      /* PF1 */
  AT90CAN128::DigitalOutPin     c_d(&DDRF, &PORTF, 0);      /* PF0 */
  AT90CAN128::DigitalOutPin     rst(&DDRG, &PORTG, 1);      /* PG1 */
  AT90CAN128::DigitalOutPin     fs (&DDRG, &PORTG, 0);      /* PG0 */

  AT90CAN128::DigitalInOutPort  data(&DDRE, &PORTE, &PINE); /* PE  */

  /* DRIVER ***************************************************************************/

  glcd::RA6963::RA6963_IoGpio8Bit ra6963_io     (delay, wr, rd, ce, c_d, rst, fs, data);
  glcd::RA6963::RA6963_Data       ra6963_data   (ra6963_io);
  glcd::RA6963::RA6963_Control    ra6963_control(ra6963_data);
  glcd::RA6963::RA6963            ra6963        (ra6963_control);

  /* APPLICATION **********************************************************************/

  ra6963.open();

  uint16_t gfx_area = WIDTH / 8;
  ra6963.ioctl(glcd::RA6963::IOCTL_SET_GFX_AREA, static_cast<void *>(&gfx_area));

  for(;;) { }

  ra6963.close();

  return 0;
}
