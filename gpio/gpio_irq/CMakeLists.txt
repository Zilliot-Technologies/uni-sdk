add_executable(gpio_irq
        gpio_irq.c
        )

# pull in common dependencies
target_link_libraries(gpio_irq pico_stdlib hardware_gpio)

# create map/bin/hex file etc.
pico_add_extra_outputs(gpio_irq)

# add url via pico_set_program_url
example_auto_set_url(gpio_irq)

# disable uart output, enable usb output
pico_enable_stdio_uart(gpio_irq 1)   
pico_enable_stdio_usb(gpio_irq 0)