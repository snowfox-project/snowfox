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
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/ATxxxx/EEPROM.h>

#if defined(MCU_ARCH_avr)
#include <avr/eeprom.h>
#else
#include <string.h>
#endif

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATxxxx
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

EEPROM::EEPROM()
{

}

EEPROM::~EEPROM()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void EEPROM::read(uint8_t const * eeprom, uint8_t * val)
{
#if defined(MCU_ARCH_avr)
  *val = eeprom_read_byte(eeprom);
#endif 
}

void EEPROM::update(uint8_t * eeprom, uint8_t const val)
{
#if defined(MCU_ARCH_avr)
  eeprom_update_byte(eeprom, val);
#endif
}

void EEPROM::write(uint8_t * eeprom, uint8_t const val)
{
#if defined(MCU_ARCH_avr)
  eeprom_write_byte(eeprom, val);
#endif
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */
