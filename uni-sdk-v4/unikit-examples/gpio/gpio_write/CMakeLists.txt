add_executable(gpio_write
        gpio_write.c
        )

# pull in common dependencies
target_link_libraries(gpio_write pico_stdlib hardware_gpio)

# create map/bin/hex file etc.
pico_add_extra_outputs(gpio_write)

# add url via pico_set_program_url
example_auto_set_url(gpio_write)

# disable uart output, enable usb output
pico_enable_stdio_uart(gpio_write 1)   
pico_enable_stdio_usb(gpio_write 0)
