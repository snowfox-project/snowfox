/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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

#ifndef INCLUDE_SPECTRE_COMSTACK_CANOPEN_FRAMEDISPATCHER_H_
#define INCLUDE_SPECTRE_COMSTACK_CANOPEN_FRAMEDISPATCHER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/comstack/canopen/interface/FrameHandler.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace comstack
{

namespace canopen
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class FrameDispatcher
{

public:

  FrameDispatcher(interface::FrameHandler & sync_frame_handler,
                  interface::FrameHandler & pdo_frame_handler,
                  interface::FrameHandler & sdo_frame_handler,
                  interface::FrameHandler & node_guard_frame_handler,
                  interface::FrameHandler & unkown_frame_handler);

  void dispatch(CanFrame const & frame);


private:

  interface::FrameHandler & _sync_frame_handler,
                          & _pdo_frame_handler,
                          & _sdo_frame_handler,
                          & _node_guard_frame_handler,
                          & _unkown_frame_handler;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* canopen */

} /* comstack */

} /* spectre */

#endif /* INCLUDE_SPECTRE_COMSTACK_CANOPEN_FRAMEDISPATCHER_H_ */
