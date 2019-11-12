/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2019 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SNOWFOX_DRIVER_HAPTIC_DRV2605_H_
#define INCLUDE_SNOWFOX_DRIVER_HAPTIC_DRV2605_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/haptic/DRV2605/interface/DRV2605_Control.h>

#include <snowfox/hal/interface/delay/Delay.h>

#include <snowfox/driver/haptic/DRV2605/interface/DRV2605_Io.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
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

class DRV2605_Control final : public interface::DRV2605_Control
{

public:

           DRV2605_Control(interface::DRV2605_Io & io, hal::interface::Delay & delay);
  virtual ~DRV2605_Control();


  virtual bool reset              (                                                                       ) override final;
  virtual bool setStandby         (                                                                       ) override final;
  virtual bool clrStandby         (                                                                       ) override final;
  virtual bool setMode            (interface::Mode               const   mode                             ) override final;
  virtual bool setWaveformLibrary (interface::WaveformLibrary    const   library                          ) override final;
  virtual bool setWaveform        (interface::WaveformSequencer  const   sequencer, uint8_t const waveform) override final;
  virtual bool setActuator        (interface::Actuator           const   actuator                         ) override final;
  virtual bool setGo              (                                                                       ) override final;
  virtual bool clrGo              (                                                                       ) override final;


private:

  interface::DRV2605_Io & _io;
  hal::interface::Delay & _delay;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* DRV2605 */

} /* haptic */

} /* driver */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_DRIVER_HAPTIC_DRV2605_H_ */
