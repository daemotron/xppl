cmake_minimum_required (VERSION 3.2)

# default compilers
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

# build universal 2 binary on macOS, supporting both, Intel Macs and Silicon (M1/M2)
if(APPLE)
    set (CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
endif()

# For CMake versions < 3.25
if(CMAKE_VERSION VERSION_LESS "3.25")
    if(UNIX AND NOT APPLE)
        set(LINUX TRUE)
        message("-- Linux detected")
    endif()
endif()

project(XPPL)

# Copy symbol collisions file
configure_file("collisions" "collisions" COPYONLY)

# Global compiler flags
set (GCC_DEFAULT_FLAGS -std=gnu17 -Wall -Wunreachable-code -pipe -Wextra -Wshadow -Wfloat-equal -pedantic -fvisibility=hidden -O2 -fmessage-length=0 -D_FORTIFY_SOURCE=2 -fstack-protector -funwind-tables -fasynchronous-unwind-tables -W)
set (GXX_DEFAULT_FLAGS -std=gnu++17 -Wall -Wunreachable-code -pipe -Wextra -Wshadow -Wfloat-equal -pedantic -fvisibility=hidden -O2 -fmessage-length=0 -D_FORTIFY_SOURCE=2 -fstack-protector -funwind-tables -fasynchronous-unwind-tables -W)

include_directories("./include")

file(GLOB_RECURSE TEST_SOURCES "test/*.c")
file(GLOB_RECURSE XPPL_COMMON_SOURCES "xppl_common/*.c")
file(GLOB_RECURSE XPPL_CONFIG_SOURCES "xppl_config/*.c")
file(GLOB_RECURSE XPPL_TEST_SOURCES "xppl_test/*.c")

set(SOURCES ${TEST_SOURCES} ${XPPL_TEST_SOURCES} ${XPPL_COMMON_SOURCES} ${XPPL_CONFIG_SOURCES})

if(WIN32)
    cmake_policy(SET CMP0015 NEW)
    set (CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
    set (CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
    add_executable(WIN_TEST_64 ${SOURCES})
    target_compile_options(WIN_TEST_64 PRIVATE ${GCC_DEFAULT_FLAGS} -s -c -fno-stack-protector -static-libgcc -static-libstdc++ -DIBM)
    target_link_libraries(WIN_TEST_64 -static-libgcc -static-libstdc++ -static ssp)
    set_target_properties(WIN_TEST_64 PROPERTIES LINK_FLAGS "-s -Wl,--version-script=collisions")
    set_target_properties(WIN_TEST_64 PROPERTIES OUTPUT_NAME "test")
endif()

if(LINUX)
    add_executable(LIN_TEST_64 ${SOURCES})
    target_compile_options(LIN_TEST_64 PRIVATE ${GCC_DEFAULT_FLAGS} -m64 -fPIC -DLIN)
    set_target_properties(LIN_TEST_64 PROPERTIES LINK_FLAGS "-Wl,--version-script=collisions")
    set_target_properties(LIN_TEST_64 PROPERTIES OUTPUT_NAME "test")
endif()

if(APPLE)
    cmake_policy(SET CMP0042 NEW)
    set (CMAKE_SYSTEM_NAME Darwin)
    set (CMAKE_CXX_COMPILER g++)
    set (CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
    add_executable(MAC_TEST_64 SHARED ${SOURCES})
    target_compile_options(MAC_TEST_64 PRIVATE ${GCC_DEFAULT_FLAGS} -nostdinc++ -I/Library/Developer/CommandLineTools/usr/include/c++/v1 -DAPL)
    target_link_libraries(MAC_TEST_64 "-nodefaultlibs" "-lc++" "-lc++abi" "-lm" "-lc")
    set_target_properties(MAC_TEST_64 PROPERTIES LINK_FLAGS "-m64 -fvisibility=hidden")
    set_target_properties(MAC_TEST_64 PROPERTIES OUTPUT_NAME "test")
endif()
