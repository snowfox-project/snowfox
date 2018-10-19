##########################################################################
# COMSTACK ###############################################################
##########################################################################

##########################################################################
# CANOPEN ################################################################
##########################################################################

set(COMSTACK_CANOPEN_SRC_PATH src/comstack/canopen)

set(SPECTRE_LIBRARY_COMSTACK_SRCS
  ${COMSTACK_CANOPEN_SRC_PATH}/util/CanOpenFrameUtil.cpp
  
  ${COMSTACK_CANOPEN_SRC_PATH}/nmt/NmtFrameHandler.cpp
  ${COMSTACK_CANOPEN_SRC_PATH}/nodeguard/NodeGuardFrameHandler.cpp
  ${COMSTACK_CANOPEN_SRC_PATH}/pdo/PdoFrameHandler.cpp
  ${COMSTACK_CANOPEN_SRC_PATH}/sdo/SdoFrameHandler.cpp
  ${COMSTACK_CANOPEN_SRC_PATH}/sync/SyncFrameHandler.cpp
  
  ${COMSTACK_CANOPEN_SRC_PATH}/CanFrame.cpp
  ${COMSTACK_CANOPEN_SRC_PATH}/CanOpenStack.cpp
  ${COMSTACK_CANOPEN_SRC_PATH}/FrameDispatcher.cpp
  ${COMSTACK_CANOPEN_SRC_PATH}/ObjectDictionary.cpp
  ${COMSTACK_CANOPEN_SRC_PATH}/UnkownFrameHandler.cpp
)

set(SPECTRE_LIBRARY_COMSTACK_SRCS ${SPECTRE_LIBRARY_COMSTACK_SRCS} ${SPECTRE_LIBRARY_COMSTACK_SRCS})

##########################################################################
