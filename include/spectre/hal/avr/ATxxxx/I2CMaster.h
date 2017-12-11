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

#ifndef INCLUDE_SPECTRE_MCU_AVR_ATXXXX_I2CMASTER_H_
#define INCLUDE_SPECTRE_MCU_AVR_ATXXXX_I2CMASTER_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/interface/i2c/I2CMaster.h>
#include <spectre/hal/interface/i2c/I2CMasterConfiguration.h>

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
 * CLASS DECLARATION
 **************************************************************************************/

class I2CMaster : public interface::I2CMaster,
                  public interface::I2CMasterConfiguration
{

public:

           I2CMaster();
  virtual ~I2CMaster();


  /* I2C Master Interface */

  virtual bool begin      (uint8_t const address, bool const is_read_access               ) override;
  virtual void end        (                                                               ) override;
  virtual bool write      (uint8_t const data                                             ) override;
  virtual bool requestFrom(uint8_t const address, uint8_t * data, uint16_t const num_bytes) override;


  /* I2C Master Configuration Interface */

  virtual void setI2CClock(eI2CClock const i2c_clock) = 0;

protected:


  typedef enum
  {
    Prescaler_1   = 1,
    Prescaler_4   = 4,
    Prescaler_16  = 16,
    Prescaler_64  = 64
  } eTWIPrescaler;


  virtual bool    start                 (uint8_t    const   address) = 0;
  virtual bool    transmitByte          (uint8_t    const   data   ) = 0;
  virtual void    receiveByteAndSendACK (uint8_t          * data   ) = 0;
  virtual void    receiveByteAndSendNACK(uint8_t          * data   ) = 0;
  virtual void    stop                  (                          ) = 0;

  virtual void    setTWIPrescaler       (eTWIPrescaler const prescaler    ) = 0;
  virtual void    setTWBR               (uint32_t      const i2c_speed_Hz,
                                         uint32_t      const i2c_prescaler) = 0;

  static  uint8_t convertI2CAddress     (uint8_t const address, bool is_read_access);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_MCU_AVR_ATXXXX_I2CMASTER_H_ */
