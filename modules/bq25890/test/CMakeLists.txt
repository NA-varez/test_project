add_executable(test_bq25890
    test_bq25890.cpp
)

target_link_libraries(test_bq25890
    PRIVATE
        bq25890
        startup_nortos  # or startup_freertos depending on test requirements
        ${CC32XX_SDK_PATH}/source/ti/devices/cc32xx/driverlib/ticlang/Release/driverlib.a
)

# Include parent directory for access to module headers
target_include_directories(test_bq25890 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# Add map file and link info generation
target_link_options(test_bq25890 PRIVATE
    -Wl,-m"${CMAKE_CURRENT_BINARY_DIR}/test_bq25890.map"
    -Wl,--xml_link_info="${CMAKE_CURRENT_BINARY_DIR}/test_bq25890_linkInfo.xml"
    -T${NORTOS_LINKER_SCRIPT}
)

# Generate SysConfig (both image and test configs)
sysconfig_generate(test_bq25890)

# Generate outputs
generate_outputs(test_bq25890)