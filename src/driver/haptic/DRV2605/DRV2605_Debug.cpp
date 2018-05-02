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

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/haptic/DRV2605/DRV2605_Debug.h>

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
 * CONSTANTS
 **************************************************************************************/

FLASH_DECLARE(static char const STATUS          [] = "STATUS            = ");
FLASH_DECLARE(static char const MODE            [] = "MODE              = ");
FLASH_DECLARE(static char const RTP             [] = "RTP               = ");
FLASH_DECLARE(static char const LIB             [] = "LIB               = ");
FLASH_DECLARE(static char const WAVESEQ1        [] = "WAVESEQ1          = ");
FLASH_DECLARE(static char const WAVESEQ2        [] = "WAVESEQ2          = ");
FLASH_DECLARE(static char const WAVESEQ3        [] = "WAVESEQ3          = ");
FLASH_DECLARE(static char const WAVESEQ4        [] = "WAVESEQ4          = ");
FLASH_DECLARE(static char const WAVESEQ5        [] = "WAVESEQ5          = ");
FLASH_DECLARE(static char const WAVESEQ6        [] = "WAVESEQ6          = ");
FLASH_DECLARE(static char const WAVESEQ7        [] = "WAVESEQ7          = ");
FLASH_DECLARE(static char const WAVESEQ8        [] = "WAVESEQ8          = ");
FLASH_DECLARE(static char const GO              [] = "GO                = ");
FLASH_DECLARE(static char const OVERDRIVE       [] = "OVERDRIVE         = ");
FLASH_DECLARE(static char const SUSTAINOFFSETPOS[] = "SUSTAINOFFSETPOS  = ");
FLASH_DECLARE(static char const SUSTAINOFFSETNEG[] = "SUSTAINOFFSETNEG  = ");
FLASH_DECLARE(static char const BREAKTIME       [] = "BREAKTIME         = ");
FLASH_DECLARE(static char const AUDIOCTRL       [] = "AUDIOCTRL         = ");
FLASH_DECLARE(static char const AUDMINLVL       [] = "AUDMINLVL         = ");
FLASH_DECLARE(static char const AUDMAXLVL       [] = "AUDMAXLVL         = ");
FLASH_DECLARE(static char const AUDMINDRIVE     [] = "AUDMINDRIVE       = ");
FLASH_DECLARE(static char const AUDMAXDRIVE     [] = "AUDMAXDRIVE       = ");
FLASH_DECLARE(static char const RATEDVOLT       [] = "RATEDVOLT         = ");
FLASH_DECLARE(static char const OVERDRIVECLAMP  [] = "OVERDRIVECLAMP    = ");
FLASH_DECLARE(static char const COMPRESULT      [] = "COMPRESULT        = ");
FLASH_DECLARE(static char const BACKEMF         [] = "BACKEMF           = ");
FLASH_DECLARE(static char const FEEDBACK        [] = "FEEDBACK          = ");
FLASH_DECLARE(static char const CONTROL1        [] = "CONTROL1          = ");
FLASH_DECLARE(static char const CONTROL2        [] = "CONTROL2          = ");
FLASH_DECLARE(static char const CONTROL3        [] = "CONTROL3          = ");
FLASH_DECLARE(static char const CONTROL4        [] = "CONTROL4          = ");
FLASH_DECLARE(static char const CONTROL5        [] = "CONTROL5          = ");
FLASH_DECLARE(static char const OLP             [] = "OLP               = ");
FLASH_DECLARE(static char const VBATMONITOR     [] = "VBATMONITOR       = ");
FLASH_DECLARE(static char const LRARESPERIOD    [] = "LRARESPERIOD      = ");

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void DRV2605_Debug::debug_dumpAllRegs(debug::interface::Debug & debug_interface, hal::interface::Flash & flash, interface::DRV2605_Io & io)
{
  debug_dumpSingleReg(debug_interface, flash, io, STATUS          , interface::Register::STATUS          );
  debug_dumpSingleReg(debug_interface, flash, io, MODE            , interface::Register::MODE            );
  debug_dumpSingleReg(debug_interface, flash, io, RTP             , interface::Register::RTP             );
  debug_dumpSingleReg(debug_interface, flash, io, LIB             , interface::Register::LIB             );
  debug_dumpSingleReg(debug_interface, flash, io, WAVESEQ1        , interface::Register::WAVESEQ1        );
  debug_dumpSingleReg(debug_interface, flash, io, WAVESEQ2        , interface::Register::WAVESEQ2        );
  debug_dumpSingleReg(debug_interface, flash, io, WAVESEQ3        , interface::Register::WAVESEQ3        );
  debug_dumpSingleReg(debug_interface, flash, io, WAVESEQ4        , interface::Register::WAVESEQ4        );
  debug_dumpSingleReg(debug_interface, flash, io, WAVESEQ5        , interface::Register::WAVESEQ5        );
  debug_dumpSingleReg(debug_interface, flash, io, WAVESEQ6        , interface::Register::WAVESEQ6        );
  debug_dumpSingleReg(debug_interface, flash, io, WAVESEQ7        , interface::Register::WAVESEQ7        );
  debug_dumpSingleReg(debug_interface, flash, io, WAVESEQ8        , interface::Register::WAVESEQ8        );
  debug_dumpSingleReg(debug_interface, flash, io, GO              , interface::Register::GO              );
  debug_dumpSingleReg(debug_interface, flash, io, OVERDRIVE       , interface::Register::OVERDRIVE       );
  debug_dumpSingleReg(debug_interface, flash, io, SUSTAINOFFSETPOS, interface::Register::SUSTAINOFFSETPOS);
  debug_dumpSingleReg(debug_interface, flash, io, SUSTAINOFFSETNEG, interface::Register::SUSTAINOFFSETNEG);
  debug_dumpSingleReg(debug_interface, flash, io, BREAKTIME       , interface::Register::BREAKTIME       );
  debug_dumpSingleReg(debug_interface, flash, io, AUDIOCTRL       , interface::Register::AUDIOCTRL       );
  debug_dumpSingleReg(debug_interface, flash, io, AUDMINLVL       , interface::Register::AUDMINLVL       );
  debug_dumpSingleReg(debug_interface, flash, io, AUDMAXLVL       , interface::Register::AUDMAXLVL       );
  debug_dumpSingleReg(debug_interface, flash, io, AUDMINDRIVE     , interface::Register::AUDMINDRIVE     );
  debug_dumpSingleReg(debug_interface, flash, io, AUDMAXDRIVE     , interface::Register::AUDMAXDRIVE     );
  debug_dumpSingleReg(debug_interface, flash, io, RATEDVOLT       , interface::Register::RATEDVOLT       );
  debug_dumpSingleReg(debug_interface, flash, io, OVERDRIVECLAMP  , interface::Register::OVERDRIVECLAMP  );
  debug_dumpSingleReg(debug_interface, flash, io, COMPRESULT      , interface::Register::COMPRESULT      );
  debug_dumpSingleReg(debug_interface, flash, io, BACKEMF         , interface::Register::BACKEMF         );
  debug_dumpSingleReg(debug_interface, flash, io, FEEDBACK        , interface::Register::FEEDBACK        );
  debug_dumpSingleReg(debug_interface, flash, io, CONTROL1        , interface::Register::CONTROL1        );
  debug_dumpSingleReg(debug_interface, flash, io, CONTROL2        , interface::Register::CONTROL2        );
  debug_dumpSingleReg(debug_interface, flash, io, CONTROL3        , interface::Register::CONTROL3        );
  debug_dumpSingleReg(debug_interface, flash, io, CONTROL4        , interface::Register::CONTROL4        );
  debug_dumpSingleReg(debug_interface, flash, io, CONTROL5        , interface::Register::CONTROL5        );
  debug_dumpSingleReg(debug_interface, flash, io, OLP             , interface::Register::OLP             );
  debug_dumpSingleReg(debug_interface, flash, io, VBATMONITOR     , interface::Register::VBATMONITOR     );
  debug_dumpSingleReg(debug_interface, flash, io, LRARESPERIOD    , interface::Register::LRARESPERIOD    );
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void DRV2605_Debug::debug_dumpSingleReg(debug::interface::Debug & debug_interface, hal::interface::Flash & flash, interface::DRV2605_Io & io, char const * msg, interface::Register const reg)
{
  char    msg_ram[32];
  uint8_t reg_content = 0;

  flash.readStringFromFlash(msg_ram, msg);
  io.readRegister(reg, &reg_content);

  debug_interface.print("%s%02X\n\r", msg_ram, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* DRV2605 */

} /* haptic */

} /* driver */

} /* spectre */
