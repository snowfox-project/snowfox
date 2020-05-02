/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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
 * INCLUDE
 **************************************************************************************/

#include <snowfox/os/event/EventGroup.h>

#include <algorithm>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::os
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

EventGroup::EventGroup()
{

}

EventGroup::~EventGroup()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

void EventGroup::addEvent(interface::EventConsumer * event)
{
  _event_list.push_back(event);
}

void EventGroup::clearAllEvents()
{
  std::for_each(_event_list.begin(),
                _event_list.end(),
                [](interface::EventConsumer * event)
                {
                  event->clear();
                });
}

bool EventGroup::isEveryEventSet()
{
  bool is_every_event_set = true;

  std::for_each(_event_list.begin(),
                _event_list.end(),
                [&is_every_event_set](interface::EventConsumer * event)
                {
                  if(!event->isSet()) {
                    is_every_event_set = false;
                    return;
                  }
                });

  return is_every_event_set;
}

bool EventGroup::isAnyEventSet()
{
  bool is_any_event_set = false;

  std::for_each(_event_list.begin(),
                _event_list.end(),
                [&is_any_event_set](interface::EventConsumer * event)
                {
                  if(event->isSet()) {
                    is_any_event_set = true;
                    return;
                  }
                });

  return is_any_event_set;
}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

void waitAny(EventGroup & event_group)
{
  while(!event_group.isAnyEventSet())
  {
    /* TODO: task_yield / thread_yield */
  }
}


/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::os */
