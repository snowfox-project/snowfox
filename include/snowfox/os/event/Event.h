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

#ifndef INCLUDE_SNOWFOX_OS_EVENT_H_
#define INCLUDE_SNOWFOX_OS_EVENT_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/os/event/interface/EventProducer.h>
#include <snowfox/os/event/interface/EventConsumer.h>

#include <stdbool.h>

#include <snowfox/hal/interface/locking/CriticalSection.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace os
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class Event : public interface::EventProducer,
              public interface::EventConsumer
{

public:

           Event(hal::interface::CriticalSection & crit_sec);
  virtual ~Event();


  virtual void set  () override;
  virtual void clear() override;
  virtual bool isSet() override;

private:

  bool                              _is_set;
  hal::interface::CriticalSection & _crit_sec;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox */

} /* os */

#endif /* INCLUDE_SNOWFOX_OS_EVENT_H_ */
