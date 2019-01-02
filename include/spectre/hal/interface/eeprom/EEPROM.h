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

#ifndef INCLUDE_SPECTRE_HAL_INTERFACE_EEPROM_EEPROM_H_
#define INCLUDE_SPECTRE_HAL_INTERFACE_EEPROM_EEPROM_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace interface
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

#if defined(MCU_ARCH_avr)
  #define EEPROM_DECLARE(x) __attribute__((section(".eeprom"))) x
#else
  #define EEPROM_DECLARE(x) x
#endif

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class EEPROM
{

public:

           EEPROM() { }
  virtual ~EEPROM() { }


  virtual void read  (uint8_t  * to_ram,    uint8_t  const * from_eeprom) = 0;
  virtual void read  (uint16_t * to_ram,    uint16_t const * from_eeprom) = 0;
  virtual void read  (uint32_t * to_ram,    uint32_t const * from_eeprom) = 0;
  virtual void read  (float    * to_ram,    float    const * from_eeprom) = 0;

  virtual void update(uint8_t  * to_eeprom, uint8_t  const   from_ram   ) = 0;
  virtual void update(uint16_t * to_eeprom, uint16_t const   from_ram   ) = 0;
  virtual void update(uint32_t * to_eeprom, uint32_t const   from_ram   ) = 0;
  virtual void update(float    * to_eeprom, float    const   from_ram   ) = 0;

  virtual void write (uint8_t  * to_eeprom, uint8_t  const   from_ram   ) = 0;
  virtual void write (uint16_t * to_eeprom, uint16_t const   from_ram   ) = 0;
  virtual void write (uint32_t * to_eeprom, uint32_t const   from_ram   ) = 0;
  virtual void write (float    * to_eeprom, float    const   from_ram   ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface*/

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_INTERFACE_EEPROM_EEPROM_H_ */
