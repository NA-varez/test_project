add_library(bq25890 STATIC
    bq25890.cpp
)

target_include_directories(bq25890 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CC32XX_SDK_PATH}/source
)

target_compile_definitions(bq25890 PRIVATE
    DDeviceFamily_CC3220
)

# Add test subdirectory if enabled
if(BUILD_TESTS)
    add_subdirectory(test)
endif()