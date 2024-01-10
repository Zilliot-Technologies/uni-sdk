add_executable(uart_write
        uart_write.c
        )

# pull in common dependencies
target_link_libraries(uart_write pico_stdlib)

# enable uart output, disable usb output
pico_enable_stdio_uart(uart_write 1)
pico_enable_stdio_usb(uart_write 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(uart_write)

# add url via pico_set_program_url
example_auto_set_url(uart_write)
