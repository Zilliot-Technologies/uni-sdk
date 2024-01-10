add_executable(dma_basic
        dma_basic.c
        )

target_link_libraries(dma_basic pico_stdlib hardware_dma)

# enable uart output, disable usb output
pico_enable_stdio_uart(dma_basic 1)   
pico_enable_stdio_usb(dma_basic 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(dma_basic)

# add url via pico_set_program_url
example_auto_set_url(dma_basic)
