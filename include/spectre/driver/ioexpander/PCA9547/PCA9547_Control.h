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

#ifndef INCLUDE_SPECTRE_DRIVER_IOEXPANDER_PCA9547_H_
#define INCLUDE_SPECTRE_DRIVER_IOEXPANDER_PCA9547_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/ioexpander/PCA9547/interface/PCA9547_Control.h>
#include <spectre/driver/ioexpander/PCA9547/interface/PCA9547_Io.h>

#include <stdint.h>

#include <spectre/debug/interface/Debug.h>

#include <spectre/hal/interface/i2c/I2CMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace ioexpander
{

namespace PCA9547
{

/**************************************************************************************
 * CLASS DECLARATION PCA9547
 **************************************************************************************/

class PCA9547_Control : public interface::PCA9547_Control
{

public:

           PCA9547_Control(interface::PCA9547_Io & io);
  virtual ~PCA9547_Control();


  /* PCA9547 Interface */

  virtual bool setChannel(interface::I2cChannel const   sel) override;
  virtual bool getChannel(interface::I2cChannel       * sel) override;


          void debug_dumpAllRegs(debug::interface::Debug & debug_interface);

private:

  interface::PCA9547_Io & _io;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* PCA9547 */

} /* ioexpander */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_IOEXPANDER_PCA9547_H_ */
