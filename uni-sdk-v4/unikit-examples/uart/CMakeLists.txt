if (NOT PICO_NO_HARDWARE)
    add_subdirectory(uart_read)
    add_subdirectory(uart_write)
endif ()