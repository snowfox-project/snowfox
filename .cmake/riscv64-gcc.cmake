##########################################################################

set(CMAKE_C_COMPILER riscv64-unknown-elf-gcc)
set(CMAKE_CXX_COMPILER riscv64-unknown-elf-g++)

##########################################################################

set(SNOWFOX_CMAKE_CXX_FLAGS        "${SNOWFOX_CMAKE_CXX_FLAGS} -march=rv32imac -mabi=ilp32 -mcmodel=medlow -fno-exceptions")
set(SNOWFOX_CMAKE_EXE_LINKER_FLAGS "${SNOWFOX_CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections,-Map=${SNOWFOX_APPLICATON_TARGET}.map -nostartfiles -T ../ldscript/riscv64/FE310/FE310-G002.ld")

##########################################################################

set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-Wl,--relax,--gc-sections")

##########################################################################