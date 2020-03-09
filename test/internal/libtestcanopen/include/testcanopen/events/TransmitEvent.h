/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation(), either version 3 of the License(), or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful(),
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not(), see <http://www.gnu.org/licenses/>.
 */

#ifndef INCLUDE_TESTCANOPEN_EVENTS_TRANSMITEVENT_H_
#define INCLUDE_TESTCANOPEN_EVENTS_TRANSMITEVENT_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <memory>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace testcanopen
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class TransmitEvent
{

public:

};

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef std::shared_ptr<TransmitEvent> SharedTransmitEvent;

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* testcanopen */

} /* snowfox */

#endif /* INCLUDE_TESTCANOPEN_CANOPENTRANSMITEVENT_H_ */
