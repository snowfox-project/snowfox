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
 * INCLUDES
 **************************************************************************************/

#include <catch.hpp>

#include <Register.h>
#include <hal/avr/ATMEGA328P/RegisterResetValueList.h>

#include <spectre/hal/avr/ATMEGA328P/SPIMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA328P
{

namespace test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("ATMEGA328P::SPIMaster - ", "[ATMEGA328P::SPIMaster]")
{
  Register<uint8_t> SPCR(SPCR_RESET_VALUE),
                    SPSR(SPSR_RESET_VALUE),
                    SPDR(SPDR_RESET_VALUE);

  ATMEGA328P::SPIMaster spi_master(SPCR(), SPSR(), SPDR());
}

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

} /* test */

} /* ATMEGA328P */

} /* hal */

} /* spectre */
