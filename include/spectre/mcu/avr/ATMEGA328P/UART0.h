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

#include <spectre/mcu/interface/uart/UARTInterface.h>
#include <spectre/mcu/interface/uart/UARTConfigurationInterface.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace mcu
{

namespace ATMEGA328P
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class UART0 : public interface::UARTInterface,
              public interface::UARTConfigurationInterface
{

public:

           UART0();
  virtual ~UART0();

  /* UART Interface */

  virtual void transmit(uint8_t const   data) override;
  virtual void receive (uint8_t       & data) override;
  
  /* UART Configuration Interface */

  virtual void setBaudRate  (eBaudRate const    baud_rate) override;
  virtual void setParity    (eParity   const    parity   ) override;
  virtual void setStopBit   (eStopBit  const    stop_bit ) override;

private:

  static uint16_t calcBaudRate(uint32_t const f_cpu, uint32_t const baud_rate);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* mcu */

} /* spectre */
