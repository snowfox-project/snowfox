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

#ifndef INCLUDE_SNOWFOX_COMSTACK_CANOPEN_OBJDICT_OBJECTDICTIONARYBUILDER_H_
#define INCLUDE_SNOWFOX_COMSTACK_CANOPEN_OBJDICT_OBJECTDICTIONARYBUILDER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/comstack/canopen/objdict/ObjectDictionary.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace comstack
{

namespace canopen
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class ObjectDictionaryBuilder
{

public:


  static void build(ObjectDictionary & obj_dict);


private:

  ObjectDictionaryBuilder() { }
  ObjectDictionaryBuilder(ObjectDictionaryBuilder const & other) { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* canopen */

} /* comstack */

} /* snowfox */

#endif /* INCLUDE_SNOWFOX_COMSTACK_CANOPEN_OBJDICT_OBJECTDICTIONARYBUILDER_H_ */
