#include "stdio.h"
#include "pico/stdlib.h"

#define GPIO_PIN 8
uint8_t gpioState;

int main() {
    gpio_init(GPIO_PIN);
    gpio_set_dir(GPIO_PIN, GPIO_IN);

    while (true) {
        gpioState = gpio_get(GPIO_PIN);
        printf("gpio state: %d\r\n",gpioState);
    }

}
