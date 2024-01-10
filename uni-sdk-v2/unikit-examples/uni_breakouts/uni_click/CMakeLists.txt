add_executable(uni_click
        uni_click.c
        main.c
        )

# pull in common dependencies
target_link_libraries(uni_click pico_stdlib hardware_i2c  )

# create map/bin/hex file etc.
pico_add_extra_outputs(uni_click)

# add url via pico_set_program_url
example_auto_set_url(uni_click)

# disable uart output, enable usb output
pico_enable_stdio_uart(uni_click 1)   
pico_enable_stdio_usb(uni_click 0)
