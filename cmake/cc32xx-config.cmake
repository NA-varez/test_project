# cmake/cc32xx-config.cmake

# SysConfig executable
set(SYSCONFIG_TOOL "C:/ti/sysconfig_1_12_0/sysconfig_cli.bat" CACHE FILEPATH "Path to SysConfig tool")

# Function to run SysConfig for both image and application configs
function(sysconfig_generate TARGET)
    # Get the target directory
    get_filename_component(TARGET_DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    
    # Run SysConfig for image.syscfg
    add_custom_command(
        OUTPUT 
            ${CMAKE_CURRENT_BINARY_DIR}/syscfg/RegDomainSum5.csv
            ${CMAKE_CURRENT_BINARY_DIR}/syscfg/RegDomainSum24.csv
            ${CMAKE_CURRENT_BINARY_DIR}/syscfg/ti_drivers_net_wifi_config.json
        COMMAND ${SYSCONFIG_TOOL}
        ARGS 
            --script ${CMAKE_CURRENT_SOURCE_DIR}/image.syscfg
            -o ${CMAKE_CURRENT_BINARY_DIR}/syscfg
            -s "${CC32XX_SDK_PATH}/.metadata/product.json"
            --compiler ticlang
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/image.syscfg
        COMMENT "Generating SysConfig image files for ${TARGET}"
    )
    
    # Run SysConfig for application-specific config
    add_custom_command(
        OUTPUT 
            ${CMAKE_CURRENT_BINARY_DIR}/syscfg/ti_drivers_config.c
            ${CMAKE_CURRENT_BINARY_DIR}/syscfg/ti_drivers_config.h
            ${CMAKE_CURRENT_BINARY_DIR}/syscfg/ti_utils_build_linker.cmd.genlibs
            ${CMAKE_CURRENT_BINARY_DIR}/syscfg/syscfg_c.rov.xs
            ${CMAKE_CURRENT_BINARY_DIR}/syscfg/FreeRTOSConfig.h
            ${CMAKE_CURRENT_BINARY_DIR}/syscfg/ti_freertos_config.c
            ${CMAKE_CURRENT_BINARY_DIR}/syscfg/ti_freertos_portable_config.c
        COMMAND ${SYSCONFIG_TOOL}
        ARGS 
            --script ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_DIR}.syscfg
            -o ${CMAKE_CURRENT_BINARY_DIR}/syscfg
            -s "${CC32XX_SDK_PATH}/.metadata/product.json"
            --compiler ticlang
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_DIR}.syscfg
        COMMENT "Generating SysConfig application files for ${TARGET}"
    )
    
    # Add generated source files to target
    target_sources(${TARGET} PRIVATE 
        ${CMAKE_CURRENT_BINARY_DIR}/syscfg/ti_drivers_config.c
        ${CMAKE_CURRENT_BINARY_DIR}/syscfg/ti_freertos_config.c
        ${CMAKE_CURRENT_BINARY_DIR}/syscfg/ti_freertos_portable_config.c
    )
    
    # Add generated include directory
    target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/syscfg)
    
    # Add generated linker libraries
    target_link_options(${TARGET} PRIVATE
        -Wl,-l${CMAKE_CURRENT_BINARY_DIR}/syscfg/ti_utils_build_linker.cmd.genlibs
        -Wl,-i"${CMAKE_CURRENT_BINARY_DIR}/syscfg"
    )
endfunction()

# Function to generate binary and SLI files
function(generate_outputs TARGET)
    # Set output directory for this target
    set(TARGET_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET})
    
    # Create output directory structure
    file(MAKE_DIRECTORY ${TARGET_OUTPUT_DIR})
    
    # Generate .bin file
    add_custom_command(
        TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY}
        ARGS 
            -O binary
            --only-section .text
            --only-section .const
            --only-section .cinit
            --only-section .rodata
            --only-section .resetVecs
            $<TARGET_FILE:${TARGET}>
            ${TARGET_OUTPUT_DIR}/${TARGET}.bin
        COMMENT "Generating ${TARGET}.bin"
    )
    
    # Generate .sli file - this creates the syscfg folder with Programming files
    add_custom_command(
        TARGET ${TARGET} POST_BUILD
        COMMAND "${CC32XX_SDK_PATH}/source/ti/drivers/net/imagecreator/bin/SLImageCreator.exe"
        ARGS 
            syscfg create_image
            --sdk_path "${CC32XX_SDK_PATH}"
            --json "${CMAKE_CURRENT_BINARY_DIR}/syscfg/ti_drivers_net_wifi_config.json"
            --file "${TARGET_OUTPUT_DIR}/syscfg/sl_image.sli"
            --mcu "${TARGET_OUTPUT_DIR}/${TARGET}.bin"
        DEPENDS ${TARGET_OUTPUT_DIR}/${TARGET}.bin
        COMMENT "Generating ${TARGET} SysConfig image files"
    )
endfunction()