#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"

#define BUF_LEN 0x100

#define SPI_RX_PIN 16
#define SPI_SCK_PIN 18
#define SPI_TX_PIN 19
#define SPI_CSN_PIN 17

#define SPI_INSTANCE spi0

void printbuf(uint8_t buf[], size_t len) {
    int i;
    for (i = 0; i < len; ++i) {
        if (i % 16 == 15)
            printf("%02x\n", buf[i]);
        else
            printf("%02x ", buf[i]);
    }

    // append trailing newline if there isn't one
    if (i % 16) {
        putchar('\n');
    }
}

int main() {
    // Enable UART so we can print
    stdio_init_all();
    printf("SPI master example\n");

    // Enable SPI 0 at 1 MHz and connect to GPIOs
    spi_init(SPI_INSTANCE, 1000 * 1000);
    gpio_set_function(SPI_RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_TX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_CSN_PIN, GPIO_FUNC_SPI);

    // Make the SPI pins available to picotool
    bi_decl(bi_4pins_with_func(SPI_RX_PIN, SPI_TX_PIN, SPI_SCK_PIN, SPI_CSN_PIN, GPIO_FUNC_SPI));

    uint8_t out_buf[BUF_LEN], in_buf[BUF_LEN];

    // Initialize output buffer
    for (size_t i = 0; i < BUF_LEN; ++i) {
        out_buf[i] = i;
    }

    printf("SPI master says: The following buffer will be written to MOSI endlessly:\n");
    printbuf(out_buf, BUF_LEN);

    for (size_t i = 0; ; ++i) {
        // Write the output buffer to MOSI, and at the same time read from MISO.
        spi_write_read_blocking(SPI_INSTANCE, out_buf, in_buf, BUF_LEN);

        // Write to stdio whatever came in on the MISO line.
        printf("SPI master says: read page %d from the MISO line:\n", i);
        printbuf(in_buf, BUF_LEN);

        // Sleep for ten seconds so you get a chance to read the output.
        sleep_ms(10 * 1000);
    }
}
