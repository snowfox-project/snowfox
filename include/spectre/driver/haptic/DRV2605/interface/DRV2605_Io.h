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

enum class Register : uint8_t
{
  STATUS            = 0x00,
  MODE              = 0x01,
  RTP               = 0x02,
  LIB               = 0x03,
  WAVESEQ1          = 0x04,
  WAVESEQ2          = 0x05,
  WAVESEQ3          = 0x06,
  WAVESEQ4          = 0x07,
  WAVESEQ5          = 0x08,
  WAVESEQ6          = 0x09,
  WAVESEQ7          = 0x0A,
  WAVESEQ8          = 0x0B,
  GO                = 0x0C,
  OVERDRIVE         = 0x0D,
  SUSTAINOFFSETPOS  = 0x0E,
  SUSTAINOFFSETNEG  = 0x0F,
  BREAKTIME         = 0x10,
  AUDIOCTRL         = 0x11,
  AUDMINLVL         = 0x12,
  AUDMAXLVL         = 0x13,
  AUDMINDRIVE       = 0x14,
  AUDMAXDRIVE       = 0X15,
  RATEDVOLT         = 0x16,
  OVERDRIVECLAMP    = 0x17,
  COMPRESULT        = 0x18,
  BACKEMF           = 0x19,
  FEEDBACK          = 0x1A,
  CONTROL1          = 0x1B,
  CONTROL2          = 0x1C,
  CONTROL3          = 0x1D,
  CONTROL4          = 0x1E,
  CONTROL5          = 0x1F,
  OLP               = 0x20,
  VBATMONITOR       = 0x21,
  LRARESPERIOD      = 0x22
};

/**************************************************************************************
 * CLASS DECLARATION DRV2605
 **************************************************************************************/

class DRV2605_Io
{

public:

           DRV2605_Io() { }
  virtual ~DRV2605_Io() { }


  virtual bool readSingleRegister (Register const reg, uint8_t       * data) = 0;
  virtual bool writeSingleRegister(Register const reg, uint8_t const   data) = 0;

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
