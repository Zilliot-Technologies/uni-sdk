# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

add_executable(IS31FL3728
        IS31FL3728.c
        main.c
        )

# pull in common dependencies
target_link_libraries(IS31FL3728 pico_stdlib hardware_i2c )

# create map/bin/hex file etc.
pico_add_extra_outputs(IS31FL3728)

# add url via pico_set_program_url
example_auto_set_url(IS31FL3728)

# disable uart output, enable usb output
pico_enable_stdio_uart(IS31FL3728 1)   
pico_enable_stdio_usb(IS31FL3728 1)
