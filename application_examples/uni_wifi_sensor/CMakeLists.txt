add_executable(uni_wifi_sensor
BMA400.c
SHT4X.c
VEML6030.c
VEML6040.c
main.c
Credential.h
        )

# pull in common dependencies
target_link_libraries(uni_wifi_sensor pico_stdlib hardware_i2c hardware_uart )

# create map/bin/hex file etc.
pico_add_extra_outputs(uni_wifi_sensor)

# add url via pico_set_program_url
example_auto_set_url(uni_wifi_sensor)

# enable uart output, disable usb output
pico_enable_stdio_uart(uni_wifi_sensor 1)   
pico_enable_stdio_usb(uni_wifi_sensor 0)
