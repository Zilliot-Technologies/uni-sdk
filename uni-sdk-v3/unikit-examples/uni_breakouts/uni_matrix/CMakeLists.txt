add_executable(uni_matrix
        uni_matrix.c
        main.c
        )

# pull in common dependencies
target_link_libraries(uni_matrix pico_stdlib hardware_i2c )

# create map/bin/hex file etc.
pico_add_extra_outputs(uni_matrix)

# add url via pico_set_program_url
example_auto_set_url(uni_matrix)

# disable uart output, enable usb output
pico_enable_stdio_uart(uni_matrix 1)   
pico_enable_stdio_usb(uni_matrix 0)
