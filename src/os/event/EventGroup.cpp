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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/os/event/EventGroup.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace os
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

void EventGroup::addEvent(interface::EventConsumer & event)
{
  _event_list.push_back(event);
}

void EventGroup::clearAllEvents()
{
  for(memory::container::ListNode<interface::EventConsumer &> * iter = _event_list.begin();
      iter != _event_list.end();
      iter = iter->next())
  {
    iter->data().clear();
  }
}

bool EventGroup::isEveryEventSet()
{
  for(memory::container::ListNode<interface::EventConsumer &> * iter = _event_list.begin();
      iter != _event_list.end();
      iter = iter->next())
  {
    if(!iter->data().isSet()) return false;
  }

  return true;
}

bool EventGroup::isAnyEventSet()
{
  for(memory::container::ListNode<interface::EventConsumer &> * iter = _event_list.begin();
      iter != _event_list.end();
      iter = iter->next())
  {
    if(iter->data().isSet()) return true;
  }

  return false;
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

} /* spectre */

} /* os */
