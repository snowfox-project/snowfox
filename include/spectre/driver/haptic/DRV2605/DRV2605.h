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

#ifndef INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605_H_
#define INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <stdint.h>

#include <spectre/debug/interface/Debug.h>

#include <spectre/hal/interface/delay/Delay.h>
#include <spectre/hal/interface/i2c/I2CMaster.h>

#include <spectre/driver/haptic/DRV2605/Constants.h>
#include <spectre/driver/haptic/DRV2605/Interface.h>
#include <spectre/driver/haptic/DRV2605/ConfigurationInterface.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace DRV2605
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class DRV2605 : public Interface,
                public ConfigurationInterface
{

public:

           DRV2605(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master, hal::interface::Delay & delay);
  virtual ~DRV2605();


  /* DRV2605 Interface */

  virtual bool setGo              (                                                                           ) override;
  virtual bool clrGo              (                                                                           ) override;


  /* DRV2605 Configuration Interface */

  virtual bool reset              (                                                                           ) override;
  virtual bool setStandby         (                                                                           ) override;
  virtual bool clrStandby         (                                                                           ) override;
  virtual bool setMode            (eDRV2605ModeSelect               const   mode                              ) override;
  virtual bool setWaveformLibrary (eDRV2605WaveformLibrarySelect    const   library                           ) override;
  virtual bool setWaveform        (eDRV2605WaveformSequencerSelect  const   sequencer, uint8_t const waveform ) override;
  virtual bool setActuator        (eDRV2605ActuatorSelect           const   actuator                          ) override;


          void debug_dumpAllRegs  (debug::interface::Debug                & debug_interface);

private:

  uint8_t                     _i2c_address;
  hal::interface::I2CMaster & _i2c_master;
  hal::interface::Delay     & _delay;

  bool readSingleRegister   (uint8_t const reg_addr, uint8_t       * data);
  bool writeSingleRegister  (uint8_t const reg_addr, uint8_t const   data);

  void debug_dumpSingleReg  (debug::interface::Debug & debug_interface, char const * msg, eDRV2605RegisterSelect const reg_sel);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* DRV2605 */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605_H_ */
