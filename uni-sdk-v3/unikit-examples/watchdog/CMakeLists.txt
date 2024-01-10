add_executable(watchdog
        watchdog.c
        )

target_link_libraries(watchdog pico_stdlib)


# enable uart output, disable usb output
pico_enable_stdio_uart(watchdog 1)
pico_enable_stdio_usb(watchdog 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(watchdog)

# add url via pico_set_program_url
example_auto_set_url(watchdog)
