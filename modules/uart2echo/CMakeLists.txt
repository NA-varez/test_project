add_library(uart2echo STATIC
    uart2echo.c
)

target_include_directories(uart2echo 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CC32XX_SDK_PATH}/source
)

target_compile_definitions(uart2echo PRIVATE
    DDeviceFamily_CC3220
)

# This module uses FreeRTOS based on your description
target_link_libraries(uart2echo
    PUBLIC
        startup_freertos
)

if(BUILD_TESTS)
    add_subdirectory(test)
endif()