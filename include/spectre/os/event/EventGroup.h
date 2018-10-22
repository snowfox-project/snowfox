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

#ifndef INCLUDE_SPECTRE_OS_EVENTGROUP_H_
#define INCLUDE_SPECTRE_OS_EVENTGROUP_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/os/event/interface/EventConsumer.h>

#include <spectre/util/container/List.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace os
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class EventGroup
{

public:

   EventGroup();
  ~EventGroup();


  void addEvent       (interface::EventConsumer & event);
  void clearAllEvents ();
  bool isEveryEventSet();
  bool isAnyEventSet  ();

private:

  util::container::List<interface::EventConsumer &> _event_list;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* spectre */

} /* os */

#endif /* INCLUDE_SPECTRE_OS_EVENTGROUP_H_ */
