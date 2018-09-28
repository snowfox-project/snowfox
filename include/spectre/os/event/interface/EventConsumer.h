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

#ifndef INCLUDE_SPECTRE_OS_INTERFACE_EVENTCONSUMER_H_
#define INCLUDE_SPECTRE_OS_INTERFACE_EVENTCONSUMER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdbool.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace os
{

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class EventConsumer
{

public:

           EventConsumer() { }
  virtual ~EventConsumer() { }


  virtual void clear() = 0;
  virtual bool isSet() = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* spectre */

} /* os */

#endif /* INCLUDE_SPECTRE_OS_INTERFACE_EVENTCONSUMER_H_ */
