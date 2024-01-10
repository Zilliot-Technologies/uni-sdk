#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_INS uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 12  
#define UART_RX_PIN 13  

#define MAX_BUFFER_SIZE 128

char buffer[MAX_BUFFER_SIZE];
size_t buffer_index = 0;

int main(){
    stdio_init_all();
    // Set up our UART with the required speed.
    uart_init(UART_INS, BAUD_RATE);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    while(true){
    if (uart_is_readable(UART_INS)) {
        char received_data = uart_getc(UART_INS);
        if (received_data == '\n') {
            buffer[buffer_index] = '\0';  // Null-terminate the received string
            printf("Received: %s\n", buffer);
            buffer_index = 0;  // Reset the buffer index for the next line
        } else {
            buffer[buffer_index] = received_data;
            buffer_index++;
            if (buffer_index >= MAX_BUFFER_SIZE) {
                buffer_index = 0;  // Reset the buffer index if it exceeds the maximum size
            }
        }
    }
}
}