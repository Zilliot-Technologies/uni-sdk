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
