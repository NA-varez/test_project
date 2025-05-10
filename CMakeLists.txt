cmake_minimum_required(VERSION 3.12)

if(DEFINED ENV{TI_SIMPLELINK_SDK_PATH})
    # Continue
else()
    error(FATAL_ERROR "TI_SIMPLELINK_SDK_PATH Not set")
endif()

set(CC3235SF_BOARD quadrc2)

# Copy over the squad board and boot2 to sdk directory
#message("${PICO_BOARD}")
message("${CMAKE_CURRENT_SOURCE_DIR}")
if("${CC3235SF_BOARD}" STREQUAL "quadrc2")
    message("")

#
#
#


endif



# Pull in SDK (must be before project)
#set(PICO_PLATFORM rp2040)
#include(pico_sdk_import.cmake)

#project(QuAD C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

#could put a simplelinksdk version check here
#if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
#    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
#endif()


# Initialize the SDK
#pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        )
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()



add_subdirectory(uart2echo)
add_subdirectory(power_efficiency_test)

#add_subdirectory(m16)
#add_subdirectory(max_10)
#add_subdirectory(bmp390)
#add_subdirectory(bno055)
#add_subdirectory(mcp9808)
#add_subdirectory(power_manager)
#add_subdirectory(quad_test)
#add_subdirectory(bq25890)
#add_subdirectory(pca9685)
#add_subdirectory(sx126x)
#add_subdirectory(apps)
#add_subdirectory(telemetry)
#add_subdirectory(atwinc1500)
#add_subdirectory(mb85rs256t)