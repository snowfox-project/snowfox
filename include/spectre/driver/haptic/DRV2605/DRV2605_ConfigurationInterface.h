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

#ifndef INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605_DRV2605_CONFIGURATIONINTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605_DRV2605_CONFIGURATIONINTERFACE_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

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
 * DEFINES
 **************************************************************************************/

/* DRV2605_REG_MODE Bit Definitions ***************************************************/
#define DRV2605_REG_MODE_DEV_RESET_bm       (1<<7)
#define DRV2605_REG_MODE_STANDBY_bm         (1<<6)
#define DRV2605_REG_MODE_2_bm               (1<<2)
#define DRV2605_REG_MODE_1_bm               (1<<1)
#define DRV2605_REG_MODE_0_bm               (1<<0)

/* DRV2605_REG_LIB Bit Definitions ****************************************************/
#define DRV2605_REG_LIB_LIBRARY_SEL_2_bm    (1<<2)
#define DRV2605_REG_LIB_LIBRARY_SEL_1_bm    (1<<1)
#define DRV2605_REG_LIB_LIBRARY_SEL_0_bm    (1<<0)

/* DRV2605_REG_GO Bit Definitions *****************************************************/
#define DRV2605_REG_GO_GO_bm                (1<<0)

/* DRV2605_REG_FEEDBACK Bit Definitions ***********************************************/
#define DRV2605_REG_FEEDBACK_N_ERM_LRA_bm   (1<<7)

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  INTERNAL_TRIGGER        = 0,
  EXTERNAL_TRIGGER_EDGE   =                                                 DRV2605_REG_MODE_0_bm,
  EXTERNAL_TRIGGER_LEVEL  =                         DRV2605_REG_MODE_1_bm,
  PWM_OR_ANALOG           =                         DRV2605_REG_MODE_1_bm | DRV2605_REG_MODE_0_bm,
  AUDIO_TO_VIBE           = DRV2605_REG_MODE_2_bm,
  REAL_TIME_PLAYBACK      = DRV2605_REG_MODE_2_bm |                         DRV2605_REG_MODE_0_bm,
  DIAGNOSTICS             = DRV2605_REG_MODE_2_bm | DRV2605_REG_MODE_1_bm,
  AUTO_CALIBRATION        = DRV2605_REG_MODE_2_bm | DRV2605_REG_MODE_1_bm | DRV2605_REG_MODE_0_bm
} ModeSelect;

typedef enum
{
  LIB_NONE    = 0,
  LIB_ERM_A   =                                                                       DRV2605_REG_LIB_LIBRARY_SEL_0_bm,
  LIB_ERM_B   =                                    DRV2605_REG_LIB_LIBRARY_SEL_1_bm,
  LIB_ERM_C   =                                    DRV2605_REG_LIB_LIBRARY_SEL_1_bm | DRV2605_REG_LIB_LIBRARY_SEL_0_bm,
  LIB_ERM_D   = DRV2605_REG_LIB_LIBRARY_SEL_2_bm,
  LIB_ERM_E   = DRV2605_REG_LIB_LIBRARY_SEL_2_bm |                                    DRV2605_REG_LIB_LIBRARY_SEL_0_bm,
  LIB_LRA     = DRV2605_REG_LIB_LIBRARY_SEL_2_bm | DRV2605_REG_LIB_LIBRARY_SEL_1_bm,
  LIB_ERM_F   = DRV2605_REG_LIB_LIBRARY_SEL_2_bm | DRV2605_REG_LIB_LIBRARY_SEL_1_bm | DRV2605_REG_LIB_LIBRARY_SEL_0_bm
} WaveformLibrarySelect;

typedef enum
{
  WAVEFORM_SEQUENCER_1 = 0,
  WAVEFORM_SEQUENCER_2 = 1,
  WAVEFORM_SEQUENCER_3 = 2,
  WAVEFORM_SEQUENCER_4 = 3,
  WAVEFORM_SEQUENCER_5 = 4,
  WAVEFORM_SEQUENCER_6 = 5,
  WAVEFORM_SEQUENCER_7 = 6,
  WAVEFORM_SEQUENCER_8 = 7
} WaveformSequencerSelect;

typedef enum
{
  ERM = 0,
  LRA = DRV2605_REG_FEEDBACK_N_ERM_LRA_bm
} ActuatorSelect;

/**************************************************************************************
 * CLASS DECLARATION ConfigurationInterface
 **************************************************************************************/

class DRV2605_ConfigurationInterface
{

public:

           DRV2605_ConfigurationInterface() { }
  virtual ~DRV2605_ConfigurationInterface() { }


  virtual bool reset              (                                                                   ) = 0;
  virtual bool setStandby         (                                                                   ) = 0;
  virtual bool clrStandby         (                                                                   ) = 0;
  virtual bool setMode            (ModeSelect               const   mode                              ) = 0;
  virtual bool setWaveformLibrary (WaveformLibrarySelect    const   library                           ) = 0;
  virtual bool setWaveform        (WaveformSequencerSelect  const   sequencer, uint8_t const waveform ) = 0;
  virtual bool setActuator        (ActuatorSelect           const   actuator                          ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* DRV2605 */

} /* haptic */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605_DRV2605_CONFIGURATIONINTERFACE_H_ */
