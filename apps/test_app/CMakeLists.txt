add_executable(test_app
    main.cpp
)

# Configure RTOS type (set per app based on requirements)
set(USE_FREERTOS OFF)  # Set to ON for FreeRTOS apps

# Base libraries
target_link_libraries(test_app
    PRIVATE
        # Add required modules
        bq25890
        # uart2echo     # Uncomment if needed
        # Add driverlib
        ${CC32XX_SDK_PATH}/source/ti/devices/cc32xx/driverlib/ticlang/Release/driverlib.a
)

target_link_options(drone_ground_station PRIVATE
    -Wl,-m"${CMAKE_CURRENT_BINARY_DIR}/drone_ground_station.map"
    -Wl,--xml_link_info="${CMAKE_CURRENT_BINARY_DIR}/drone_ground_station_linkInfo.xml"
)

# RTOS configuration
if(USE_FREERTOS)
    target_link_libraries(test_app
        PRIVATE
            startup_freertos
            ${CC32XX_SDK_PATH}/kernel/freertos/lib/ccs/m4/freertos.lib
    )
    target_link_options(test_app PRIVATE
        -T${FREERTOS_LINKER_SCRIPT}
    )
else()
    target_link_libraries(test_app
        PRIVATE
            startup_nortos
    )
    target_link_options(test_app PRIVATE
        -T${NORTOS_LINKER_SCRIPT}
    )
endif()

# Generate SysConfig (both image and application configs)
sysconfig_generate(test_app)

# Generate binary and SLI outputs
generate_outputs(test_app)