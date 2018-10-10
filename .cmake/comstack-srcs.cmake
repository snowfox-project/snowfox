##########################################################################
# COMSTACK ###############################################################
##########################################################################

##########################################################################
# CANOPEN ################################################################
##########################################################################

set(COMSTACK_CANOPEN_SRC_PATH src/comstack/canopen)

set(SPECTRE_LIBRARY_COMSTACK_SRCS
  ${COMSTACK_CANOPEN_SRC_PATH}/CanFrame.cpp
  ${COMSTACK_CANOPEN_SRC_PATH}/NmtFrameHandler.cpp
  ${COMSTACK_CANOPEN_SRC_PATH}/NodeGuardFrameHandler.cpp
  ${COMSTACK_CANOPEN_SRC_PATH}/PdoFrameHandler.cpp
  ${COMSTACK_CANOPEN_SRC_PATH}/SdoFrameHandler.cpp
  ${COMSTACK_CANOPEN_SRC_PATH}/SyncFrameHandler.cpp
)

set(SPECTRE_LIBRARY_COMSTACK_SRCS ${SPECTRE_LIBRARY_COMSTACK_SRCS} ${SPECTRE_LIBRARY_COMSTACK_SRCS})

##########################################################################
