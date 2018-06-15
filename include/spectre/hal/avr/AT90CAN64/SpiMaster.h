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

#ifndef INCLUDE_SPECTRE_HAL_AVR_AT90CAN64_SPIMASTER_H_
#define INCLUDE_SPECTRE_HAL_AVR_AT90CAN64_SPIMASTER_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/common/ATxxxx/SpiMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace AT90CAN64
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class SpiMaster : public ATxxxx::SpiMaster
{

public:

           SpiMaster(volatile uint8_t * spcr,
                     volatile uint8_t * spsr,
                     volatile uint8_t * spdr) : ATxxxx::SpiMaster(spcr, spsr, spdr) { }
  virtual ~SpiMaster() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN64 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_AT90CAN64_SPIMASTER_H_ */
