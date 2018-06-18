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

#ifndef INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_MCP2515_IOSPI_H_
#define INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_MCP2515_IOSPI_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/can/MCP2515/interface/MCP2515_Io.h>

#include <spectre/hal/interface/spi/SPIMaster.h>
#include <spectre/hal/interface/gpio/DigitalOutPin.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace can
{

namespace MCP2515
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MCP2515_IoSpi : public interface::MCP2515_Io
{

public:

           MCP2515_IoSpi(hal::interface::SPIMaster & spi_master, hal::interface::DigitalOutPin & cs);
  virtual ~MCP2515_IoSpi();


  virtual void    reset   () override;
  virtual uint8_t status  () override;

  virtual void    loadTx0 (uint8_t const * tx_buf) override;
  virtual void    loadTx1 (uint8_t const * tx_buf) override;
  virtual void    loadTx2 (uint8_t const * tx_buf) override;
  virtual void    readRx0 (uint8_t       * rx_buf) override;
  virtual void    readRx1 (uint8_t       * rx_buf) override;

  virtual void    requestToTransmitTx0() override;
  virtual void    requestToTransmitTx1() override;
  virtual void    requestToTransmitTx2() override;

  virtual void    readRegister  (interface::Register const reg, uint8_t       * data                    ) override;
  virtual void    writeRegister (interface::Register const reg, uint8_t const   data                    ) override;
  virtual void    modifyRegister(interface::Register const reg, uint8_t const   data, uint8_t const mask) override;

private:

  hal::interface::SPIMaster     & _spi_master;
  hal::interface::DigitalOutPin & _cs;

  void loadTxX(uint8_t const instruction, uint8_t const * tx_buf);
  void loadRxX(uint8_t const instruction, uint8_t       * rx_buf);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* MCP2515 */

} /* can */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_CAN_MCP2515_MCP2515_IOSPI_H_ */
