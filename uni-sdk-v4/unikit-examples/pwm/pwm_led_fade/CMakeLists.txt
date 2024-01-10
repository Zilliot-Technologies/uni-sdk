add_executable(pwm_led_fade
        pwm_led_fade.c
        )

# pull in common dependencies
target_link_libraries(pwm_led_fade pico_stdlib hardware_pwm)

# create map/bin/hex file etc.
pico_add_extra_outputs(pwm_led_fade)

# add url via pico_set_program_url
example_auto_set_url(pwm_led_fade)

# disable uart output, enable usb output
pico_enable_stdio_uart(pwm_led_fade 1)   
pico_enable_stdio_usb(pwm_led_fade 0)