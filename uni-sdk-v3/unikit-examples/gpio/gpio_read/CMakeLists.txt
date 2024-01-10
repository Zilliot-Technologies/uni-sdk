add_executable(gpio_read
        gpio_read.c
        )

# pull in common dependencies
target_link_libraries(gpio_read pico_stdlib hardware_gpio)

# create map/bin/hex file etc.
pico_add_extra_outputs(gpio_read)

# add url via pico_set_program_url
example_auto_set_url(gpio_read)

# disable uart output, enable usb output
pico_enable_stdio_uart(gpio_read 1)   
pico_enable_stdio_usb(gpio_read 0)