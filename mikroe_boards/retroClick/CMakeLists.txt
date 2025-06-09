add_executable(retroClick
        retroClick.c
        main.c
        )

# pull in common dependencies
target_link_libraries(retroClick pico_stdlib hardware_i2c)

# create map/bin/hex file etc.
pico_add_extra_outputs(retroClick)

# add url via pico_set_program_url
example_auto_set_url(retroClick)

# enable uart output, disable usb output
pico_enable_stdio_uart(retroClick 1)   
pico_enable_stdio_usb(retroClick 0)
