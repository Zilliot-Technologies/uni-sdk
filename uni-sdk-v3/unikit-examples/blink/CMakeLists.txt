add_executable(blink
        blink.c
        )

# pull in common dependencies
target_link_libraries(blink pico_stdlib hardware_gpio)

# create map/bin/hex file etc.
pico_add_extra_outputs(blink)

# add url via pico_set_program_url
example_auto_set_url(blink)

# enable uart output, disable usb output
pico_enable_stdio_uart(blink 1)   
pico_enable_stdio_usb(blink 0)
