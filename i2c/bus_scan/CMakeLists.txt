add_executable(bus_scan
        bus_scan.c
        bus_scan.h
        )

# pull in common dependencies and additional i2c hardware support
target_link_libraries(bus_scan pico_stdlib hardware_i2c)

# enable uart output, disable usb output
pico_enable_stdio_usb(bus_scan 0)
pico_enable_stdio_uart(bus_scan 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(bus_scan)

# add url via pico_set_program_url
example_auto_set_url(bus_scan)
