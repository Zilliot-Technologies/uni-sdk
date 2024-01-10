#include "pico/stdlib.h"

#define RED_LED_PIN 4
#define GREEN_LED_PIN 3
#define BLUE_LED_PIN  5

// #define RED_LED
// #define GREEN_LED
#define BLUE_LED

#define BLINK_DELAY 1000 //in ms

int main(){
    #ifdef RED_LED
    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN,GPIO_OUT);
    #endif

    #ifdef GREEN_LED
    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN,GPIO_OUT);    
    #endif

    #ifdef BLUE_LED
    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(BLUE_LED_PIN,GPIO_OUT);  
    #endif

    while (true){
        #ifdef RED_LED
        gpio_put(RED_LED_PIN,1);
        #endif

        #ifdef GREEN_LED
        gpio_put(GREEN_LED_PIN,1);
        #endif

        #ifdef BLUE_LED
        gpio_put(BLUE_LED_PIN,1);
        #endif

        sleep_ms(BLINK_DELAY);

        #ifdef RED_LED
        gpio_put(RED_LED_PIN,0);
        #endif

        #ifdef GREEN_LED
        gpio_put(GREEN_LED_PIN,0);
        #endif

        #ifdef BLUE_LED
        gpio_put(BLUE_LED_PIN,0);
        #endif
        sleep_ms(BLINK_DELAY);
    }
    
}