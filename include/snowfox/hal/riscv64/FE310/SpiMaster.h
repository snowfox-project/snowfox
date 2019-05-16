/**
 * Snowfox is a modular RTOS with extensive IO support.
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

#ifndef INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_SPIMASTER_H_
#define INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_SPIMASTER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/interface/spi/SpiMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace hal
{

namespace FE310
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class SpiMaster : public interface::SpiMaster
{

public:

           SpiMaster(volatile uint32_t * spix_sckmode,
                     volatile uint32_t * spix_fmt);
  virtual ~SpiMaster();


  /* SPI Master Control Interface */

  virtual uint8_t exchange(uint8_t const data) override;


  /* SPI Master Configuration Interface */

  virtual void setSpiMode     (interface::SpiMode     const spi_mode     ) override;
  virtual void setSpiBitOrder (interface::SpiBitOrder const spi_bit_order) override;
  virtual void setSpiPrescaler(uint32_t               const spi_prescaler) override;

private:

  volatile uint32_t * _spix_sckmode,
                    * _spix_fmt;

  enum class SpiProtocol
  {
    Single, Dual, Quad
  };

  void setSpiProtocol(SpiProtocol const spi_protocol);
  
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* FE310 */

} /* hal */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_HAL_SIFIVE_FE310_SPIMASTER_H_ */
