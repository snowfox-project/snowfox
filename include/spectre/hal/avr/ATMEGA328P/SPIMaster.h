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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_SPIMASTER_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_SPIMASTER_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/interface/spi/SPIMaster.h>
#include <spectre/hal/interface/spi/SPIMasterConfiguration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA328P
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class SPIMaster : public interface::SPIMaster,
                  public interface::SPIMasterConfiguration
{

public:

           SPIMaster(volatile uint8_t * SPCR,
                     volatile uint8_t * SPSR,
                     volatile uint8_t * SPDR);
  virtual ~SPIMaster();


  /* SPI Master Interface */

  virtual uint8_t exchange(uint8_t const data) override;


  /* SPI Master Configuration Interface */

  virtual void setSpiMode     (interface::SPIMode  const spi_mode     ) override;
  virtual void setSpiPrescaler(uint32_t            const spi_prescaler) override;

private:

  volatile uint8_t * _SPCR,
                   * _SPSR,
                   * _SPDR;

  void enableSPI();

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATMEGA328P_SPIMASTER_H_ */
