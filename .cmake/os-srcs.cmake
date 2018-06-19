##########################################################################
# OS #####################################################################
##########################################################################

set(SPECTRE_LIBRARY_OS_SRCS ${SPECTRE_LIBRARY_OS_SRCS} src/os/event/Event.cpp)
set(SPECTRE_LIBRARY_OS_SRCS ${SPECTRE_LIBRARY_OS_SRCS} src/os/event/EventGroup.cpp)
set(SPECTRE_LIBRARY_OS_SRCS ${SPECTRE_LIBRARY_OS_SRCS} src/os/event/EventGroupWaiter.cpp)
set(SPECTRE_LIBRARY_OS_SRCS ${SPECTRE_LIBRARY_OS_SRCS} src/os/event/EventWaiter.cpp)
set(SPECTRE_LIBRARY_OS_SRCS ${SPECTRE_LIBRARY_OS_SRCS} src/os/scheduler.c)
set(SPECTRE_LIBRARY_OS_SRCS ${SPECTRE_LIBRARY_OS_SRCS} src/os/task.c)
