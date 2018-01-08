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

#include <spectre/driver/haptic/DRV2605/DRV2605_Interface.h>
#include <spectre/driver/haptic/DRV2605/DRV2605_ConfigurationInterface.h>
#include <spectre/driver/haptic/DRV2605/DRV2605_IO_Interface.h>

#include <spectre/driver/interface/Debug.h>
#include <spectre/driver/interface/Delay.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace haptic
{

namespace DRV2605
{

/**************************************************************************************
 * CLASS DECLARATION DRV2605
 **************************************************************************************/

class DRV2605 : public DRV2605_Interface,
                public DRV2605_ConfigurationInterface
{

public:

           DRV2605(DRV2605_IO_Interface & io, driver::interface::Delay & delay);
  virtual ~DRV2605();


  /* DRV2605 Interface */

  virtual bool setGo              (                                                                   ) override;
  virtual bool clrGo              (                                                                   ) override;


  /* DRV2605 Configuration Interface */

  virtual bool reset              (                                                                   ) override;
  virtual bool setStandby         (                                                                   ) override;
  virtual bool clrStandby         (                                                                   ) override;
  virtual bool setMode            (ModeSelect               const   mode                              ) override;
  virtual bool setWaveformLibrary (WaveformLibrarySelect    const   library                           ) override;
  virtual bool setWaveform        (WaveformSequencerSelect  const   sequencer, uint8_t const waveform ) override;
  virtual bool setActuator        (ActuatorSelect           const   actuator                          ) override;


          void debug_dumpAllRegs  (driver::interface::Debug                & debug_interface);

private:

  DRV2605_IO_Interface     & _io;
  driver::interface::Delay & _delay;

  void debug_dumpSingleReg  (driver::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* DRV2605 */

} /* haptic */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605_H_ */
