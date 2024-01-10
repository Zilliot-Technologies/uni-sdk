add_executable(uni_button_display
main.c
disp.c
button.c
        )

# pull in common dependencies
target_link_libraries(uni_button_display pico_stdlib hardware_i2c)

# create map/bin/hex file etc.
pico_add_extra_outputs(uni_button_display)

# add url via pico_set_program_url
example_auto_set_url(uni_button_display)

# disable uart output, enable usb output
pico_enable_stdio_uart(uni_button_display 1)   
pico_enable_stdio_usb(uni_button_display 0)
