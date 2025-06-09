#include "stdio.h"
#include "pico/stdlib.h"

#define GPIO_PIN 29

int main() {
    gpio_init(GPIO_PIN);
    gpio_set_dir(GPIO_PIN, GPIO_OUT);

    while (true) {
        gpio_put(GPIO_PIN,true);
        sleep_ms(1000);
        gpio_put(GPIO_PIN,false);
        sleep_ms(1000);
    }

}
