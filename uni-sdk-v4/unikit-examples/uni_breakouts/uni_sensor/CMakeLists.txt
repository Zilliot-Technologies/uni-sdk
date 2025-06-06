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

add_executable(uni_sensor
BMA400.c
SHT4X.c
VEML6030.c
VEML6040.c
main.c
        )

# pull in common dependencies
target_link_libraries(uni_sensor pico_stdlib hardware_i2c)

# create map/bin/hex file etc.
pico_add_extra_outputs(uni_sensor)

# add url via pico_set_program_url
example_auto_set_url(uni_sensor)

# disable uart output, enable usb output
pico_enable_stdio_uart(uni_sensor 1)   
pico_enable_stdio_usb(uni_sensor 0)
