# Top-level CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(cc32xx_embedded VERSION 1.0.0 LANGUAGES C CXX)

# Set TI toolchain paths (based on your makefile)
set(TI_TOOLCHAIN_PATH "C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS")

set(CMAKE_C_COMPILER   "${TI_TOOLCHAIN_PATH}/bin/tiarmclang.exe")
set(CMAKE_CXX_COMPILER "${TI_TOOLCHAIN_PATH}/bin/tiarmclang.exe")
set(CMAKE_AR           "${TI_TOOLCHAIN_PATH}/bin/tiarmar.exe")
set(CMAKE_OBJCOPY      "${TI_TOOLCHAIN_PATH}/bin/tiarmobjcopy.exe")

# Set SDK and FreeRTOS paths
set(CC32XX_SDK_PATH "C:/ti/simplelink_cc32xx_sdk_7_10_00_13")
set(FREERTOS_PATH "C:/FreeRTOSv202212.01/FreeRTOS")

# Global include directories - inherited by all targets
include_directories(
    ${CC32XX_SDK_PATH}/source
    ${CC32XX_SDK_PATH}/kernel/freertos
    ${CC32XX_SDK_PATH}/source/ti/posix/ticlang
    ${FREERTOS_PATH}/Source/include
    ${FREERTOS_PATH}/Source/portable/GCC/ARM_CM4F
)

# Compiler flags from your makefile
add_compile_options(
    -mcpu=cortex-m4
    -mfloat-abi=soft
    -mfpu=none
    -mlittle-endian
    -mthumb
    -Oz
    -gdwarf-3
    -march=armv7e-m
    # Dependency generation
    -MMD
    -MP
)

# Global preprocessor definitions
add_compile_definitions(DeviceFamily_CC3220)

# Linker flags from your makefile
add_link_options(
    -Wl,-i"${CC32XX_SDK_PATH}/source"
    -Wl,-i"${TI_TOOLCHAIN_PATH}/lib"
    -Wl,--diag_wrap=off
    -Wl,--display_error_number
    -Wl,--warn_sections
    -Wl,--rom_model
    # Add standard library
    -Wl,-llibc.a
)

# SysConfig tool
set(SYSCONFIG_TOOL "C:/ti/sysconfig_1_12_0/sysconfig_cli.bat")

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include helper functions
include(cmake/cc32xx-config.cmake)

# Add subdirectories
add_subdirectory(common)
add_subdirectory(modules)
add_subdirectory(apps)

# Option to build tests
option(BUILD_TESTS "Build module tests" OFF)