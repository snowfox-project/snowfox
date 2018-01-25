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

#ifndef INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605_DRV2605_IO_INTERFACE_H_
#define INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605_DRV2605_IO_INTERFACE_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <stdint.h>

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

namespace interface
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef enum
{
  REG_STATUS            = 0x00,
  REG_MODE              = 0x01,
  REG_RTP               = 0x02,
  REG_LIB               = 0x03,
  REG_WAVESEQ1          = 0x04,
  REG_WAVESEQ2          = 0x05,
  REG_WAVESEQ3          = 0x06,
  REG_WAVESEQ4          = 0x07,
  REG_WAVESEQ5          = 0x08,
  REG_WAVESEQ6          = 0x09,
  REG_WAVESEQ7          = 0x0A,
  REG_WAVESEQ8          = 0x0B,
  REG_GO                = 0x0C,
  REG_OVERDRIVE         = 0x0D,
  REG_SUSTAINOFFSETPOS  = 0x0E,
  REG_SUSTAINOFFSETNEG  = 0x0F,
  REG_BREAKTIME         = 0x10,
  REG_AUDIOCTRL         = 0x11,
  REG_AUDMINLVL         = 0x12,
  REG_AUDMAXLVL         = 0x13,
  REG_AUDMINDRIVE       = 0x14,
  REG_AUDMAXDRIVE       = 0X15,
  REG_RATEDVOLT         = 0x16,
  REG_OVERDRIVECLAMP    = 0x17,
  REG_COMPRESULT        = 0x18,
  REG_BACKEMF           = 0x19,
  REG_FEEDBACK          = 0x1A,
  REG_CONTROL1          = 0x1B,
  REG_CONTROL2          = 0x1C,
  REG_CONTROL3          = 0x1D,
  REG_CONTROL4          = 0x1E,
  REG_CONTROL5          = 0x1F,
  REG_OLP               = 0x20,
  REG_VBATMONITOR       = 0x21,
  REG_LRARESPERIOD      = 0x22
} RegisterSelect;

/**************************************************************************************
 * CLASS DECLARATION DRV2605
 **************************************************************************************/

class DRV2605Io
{

public:

           DRV2605Io() { }
  virtual ~DRV2605Io() { }


  virtual bool readSingleRegister (RegisterSelect const reg_sel, uint8_t       * data) = 0;
  virtual bool writeSingleRegister(RegisterSelect const reg_sel, uint8_t const   data) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* DRV2605 */

} /* haptic */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_HAPTIC_DRV2605_DRV2605_IO_INTERFACE_H_ */
