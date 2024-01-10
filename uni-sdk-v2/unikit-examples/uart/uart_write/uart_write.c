#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_INS uart0
#define BAUD_RATE 9600
#define UART_TX_PIN 16  
#define UART_RX_PIN 17  

#define UART_RAW
// #define UART_PUTC
// #define UART_PUTS

int main(){
    // Set up our UART with the required speed.
    uart_init(UART_INS, BAUD_RATE);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    uart_set_hw_flow(UART_INS, false, false);  // Disable hardware flow control
    uart_set_format(UART_INS, 8, 1, UART_PARITY_NONE);

    while(1){
       #ifdef UART_RAW
        // Send out a character without any conversions
        uart_putc_raw(UART_INS, 'A');
       #endif

       #ifdef UART_PUTC
        // Send out a character but do CR/LF conversions
        uart_putc(UART_INS, 'B');
       #endif

       #ifdef UART_PUTS
        // Send out a string, with CR/LF conversions
        uart_puts(UART_INS, " Hello, UART!\n");
        sleep_ms(10);
       #endif

    }

}