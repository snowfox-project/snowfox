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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/comstack/canopen/FrameDispatcher.h>

#include <snowfox/comstack/canopen/CobBaseId.h>
#include <snowfox/comstack/canopen/util/CanOpenFrameUtil.h>

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
 * CTOR/DTOR
 **************************************************************************************/

FrameDispatcher::FrameDispatcher(interface::FrameHandler & nmt_frame_handler,
                                 interface::FrameHandler & sync_frame_handler,
                                 interface::FrameHandler & pdo_frame_handler,
                                 interface::FrameHandler & sdo_frame_handler,
                                 interface::FrameHandler & node_guard_frame_handler,
                                 interface::FrameHandler & unkown_frame_handler)
: _nmt_frame_handler       (nmt_frame_handler       ),
  _sync_frame_handler      (sync_frame_handler      ),
  _pdo_frame_handler       (pdo_frame_handler       ),
  _sdo_frame_handler       (sdo_frame_handler       ),
  _node_guard_frame_handler(node_guard_frame_handler),
  _unkown_frame_handler    (unkown_frame_handler    )
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void FrameDispatcher::dispatch(util::type::CanFrame const & frame)
{
  uint16_t const frame_cob_base_id = toCobId(frame);

  switch(frame_cob_base_id)
  {
  case toValue(CobBaseId::NetworkManagement): _nmt_frame_handler.onFrameReceived       (frame); break;
  case toValue(CobBaseId::Sync_Emergency   ): _sync_frame_handler.onFrameReceived      (frame); break;
  case toValue(CobBaseId::TPDO1            ):
  case toValue(CobBaseId::RPDO1            ):
  case toValue(CobBaseId::TPDO2            ):
  case toValue(CobBaseId::RPDO2            ):
  case toValue(CobBaseId::TPDO3            ):
  case toValue(CobBaseId::RPDO3            ):
  case toValue(CobBaseId::TPDO4            ):
  case toValue(CobBaseId::RPDO4            ): _pdo_frame_handler.onFrameReceived       (frame); break;
  case toValue(CobBaseId::SDO_TX           ):
  case toValue(CobBaseId::SDO_RX           ): _sdo_frame_handler.onFrameReceived       (frame); break;
  case toValue(CobBaseId::NodeGuard        ): _node_guard_frame_handler.onFrameReceived(frame); break;
  default                                   : _unkown_frame_handler.onFrameReceived    (frame); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* canopen */

} /* comstack */

} /* snowfox */
