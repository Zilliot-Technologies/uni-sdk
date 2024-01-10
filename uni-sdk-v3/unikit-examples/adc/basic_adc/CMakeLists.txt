add_executable(basic_adc
    basic_adc.c
        )

target_link_libraries(basic_adc pico_stdlib hardware_adc)

# create map/bin/hex file etc.
pico_add_extra_outputs(basic_adc)

# add url via pico_set_program_url
example_auto_set_url(basic_adc)

# enable uart output, disable usb output
pico_enable_stdio_uart(basic_adc 1)   
pico_enable_stdio_usb(basic_adc 0)