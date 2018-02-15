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

#ifndef INCLUDE_SPECTRE_DRIVER_SERIAL_UART_UART_TRANSMITBUFFER_H_
#define INCLUDE_SPECTRE_DRIVER_SERIAL_UART_UART_TRANSMITBUFFER_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/serial/interface/SerialTransmitBuffer.h>

#include <spectre/hal/interface/uart/UARTConfiguration.h>
#include <spectre/hal/interface/locking/CriticalSection.h>

#include <spectre/memory/container/Queue.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace serial
{

namespace UART
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class UART_TransmitBuffer : public interface::SerialTransmitBuffer
{

public:

           UART_TransmitBuffer(uint16_t const size, hal::interface::CriticalSection & crit_sec, hal::interface::UARTConfiguration & uart_config);
  virtual ~UART_TransmitBuffer();


  virtual bool isFull                 (                       ) override;
  virtual void putData                (uint8_t const   data   ) override;
  virtual bool onTransmitRegisterEmpty(uint8_t       * tx_data) override;

private:

  memory::container::Queue<uint8_t>   _tx_queue;
  hal::interface::CriticalSection   & _crit_sec;
  hal::interface::UARTConfiguration & _uart_config;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* UART */

} /* serial */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SERIAL_UART_UART_TRANSMITBUFFER_H_ */
