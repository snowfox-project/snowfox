##########################################################################

cmake_minimum_required(VERSION 2.8)

##########################################################################

set(SPECTRE_TEST_HOST_MEMORY_TARGET test-host-memory)

##########################################################################

set(SPECTRE_TEST_HOST_MEMORY_SRCS
  test-main-memory.cpp
  
  container/test_Queue.cpp
)

##########################################################################

add_executable(
  ${SPECTRE_TEST_HOST_MEMORY_TARGET}
  ${SPECTRE_TEST_HOST_MEMORY_SRCS}
)

target_link_libraries(
  ${SPECTRE_TEST_HOST_MEMORY_TARGET}
  spectre-host
  gcov
)

##########################################################################
