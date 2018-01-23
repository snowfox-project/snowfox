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

#include <spectre/driver/haptic/DRV2605/interface/DRV2605_ControlInterface.h>
#include <spectre/driver/haptic/DRV2605/interface/DRV2605_RegisterInterface.h>

#include <spectre/hal/interface/delay/Delay.h>

#include <spectre/driver/interface/Debug.h>

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

class DRV2605_Control : public DRV2605_ControlInterface
{

public:

           DRV2605_Control(DRV2605_RegisterInterface & io, hal::interface::Delay & delay);
  virtual ~DRV2605_Control();


  virtual bool reset              (                                                                   ) override;
  virtual bool setStandby         (                                                                   ) override;
  virtual bool clrStandby         (                                                                   ) override;
  virtual bool setMode            (ModeSelect               const   mode                              ) override;
  virtual bool setWaveformLibrary (WaveformLibrarySelect    const   library                           ) override;
  virtual bool setWaveform        (WaveformSequencerSelect  const   sequencer, uint8_t const waveform ) override;
  virtual bool setActuator        (ActuatorSelect           const   actuator                          ) override;
  virtual bool setGo              (                                                                   ) override;
  virtual bool clrGo              (                                                                   ) override;


          void debug_dumpAllRegs  (driver::interface::Debug                & debug_interface);

private:

  DRV2605_RegisterInterface & _io;
  hal::interface::Delay     & _delay;

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