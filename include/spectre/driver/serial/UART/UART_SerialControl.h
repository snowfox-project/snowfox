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

#ifndef INCLUDE_SPECTRE_DRIVER_SERIAL_UART_UART_SERIALCONTROL_H_
#define INCLUDE_SPECTRE_DRIVER_SERIAL_UART_UART_SERIALCONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/serial/interface/SerialControl.h>

#include <spectre/hal/interface/uart/UARTControl.h>
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

class UART_SerialControl : public interface::SerialControl
{

public:


           UART_SerialControl(hal::interface::CriticalSection   & crit_sec,
                              memory::container::Queue<uint8_t> & rx_queue,
                              memory::container::Queue<uint8_t> & tx_queue,
                              hal::interface::UARTControl       & uart_ctrl);
  virtual ~UART_SerialControl();


  virtual uint16_t receive (uint8_t       * data, uint16_t const num_bytes) override;
  virtual uint16_t transmit(uint8_t const * data, uint16_t const num_bytes) override;


private:

  hal::interface::CriticalSection   & _crit_sec;
  memory::container::Queue<uint8_t> & _rx_queue,
                                    & _tx_queue;
  hal::interface::UARTControl       & _uart_ctrl;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* UART */

} /* serial */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SERIAL_UART_UART_SERIALCONTROL_H_ */
