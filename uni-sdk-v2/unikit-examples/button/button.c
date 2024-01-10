#include "pico/stdlib.h"
#include "stdio.h"

#define BUTTON_PIN 2
bool buttonState;

int main(){
    stdio_init_all();
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN,false);

    while(true){
       buttonState = gpio_get(BUTTON_PIN);
       if(!buttonState){
        printf("button pressed\n");
       }
       else{
        printf("button released\n");
       }
    }
}
