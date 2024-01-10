add_executable(button
        button.c
        )

# pull in common dependencies
target_link_libraries(button pico_stdlib hardware_gpio)

# create map/bin/hex file etc.
pico_add_extra_outputs(button)

# add url via pico_set_program_url
example_auto_set_url(button)

# disable uart output, enable usb output
pico_enable_stdio_uart(button 1)   
pico_enable_stdio_usb(button 0)
