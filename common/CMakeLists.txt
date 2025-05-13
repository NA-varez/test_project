
##############################################################################
# FreeRTOS library
add_library(startup_freertos STATIC
    main_freertos.cpp
)

target_include_directories(startup_freertos PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CC32XX_SDK_PATH}/source
    ${CC32XX_SDK_PATH}/kernel/freertos
    C:/FreeRTOSv202212.01/FreeRTOS/Source/include
    C:/FreeRTOSv202212.01/FreeRTOS/Source/portable/GCC/ARM_CM4F
)
##############################################################################


##############################################################################
# NoRTOS library  
add_library(startup_nortos STATIC
    main_nortos.cpp
)

target_include_directories(startup_nortos PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CC32XX_SDK_PATH}/source
)
#############################################################################

# Make linker scripts available
set(FREERTOS_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/cc32xxsf_freertos.cmd PARENT_SCOPE)
set(NORTOS_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/cc32xxsf_nortos.cmd PARENT_SCOPE)