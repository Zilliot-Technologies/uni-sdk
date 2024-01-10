add_executable(uart_read
        uart_read.c
        )

# pull in common dependencies
target_link_libraries(uart_read pico_stdlib)

# enable uart output, disable usb output
pico_enable_stdio_uart(uart_read 1)
pico_enable_stdio_usb(uart_read 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(uart_read)

# add url via pico_set_program_url
example_auto_set_url(uart_read)