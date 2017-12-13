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

#ifndef INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605CONFIGURATIONINTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605CONFIGURATIONINTERFACE_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <stdbool.h>

#include <spectre/driver/haptic/DRV2605/Constants.h>

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

class ConfigurationInterface
{

public:

           ConfigurationInterface() { }
  virtual ~ConfigurationInterface() { }


  virtual bool reset              (                                                                           ) = 0;
  virtual bool setStandby         (                                                                           ) = 0;
  virtual bool clrStandby         (                                                                           ) = 0;
  virtual bool setMode            (eDRV2605ModeSelect               const   mode                              ) = 0;
  virtual bool setWaveformLibrary (eDRV2605WaveformLibrarySelect    const   library                           ) = 0;
  virtual bool setWaveform        (eDRV2605WaveformSequencerSelect  const   sequencer, uint8_t const waveform ) = 0;
  virtual bool setActuator        (eDRV2605ActuatorSelect           const   actuator                          ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* DRV2605 */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605CONFIGURATIONINTERFACE_H_ */
