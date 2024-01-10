#include "disp.h"
#include "button.h"

// #define ENABLE_INTERRUPT
#define intPin 19
#define SDA_PIN 22
#define SCL_PIN 23
#define DISP_SDB_PIN 7
#define I2C_INSTANCE i2c1

#define LED_COUNT 128
#define ROW_SIZE 8     
#define COL_SIZE 16
#define MAX_PEAK_INTENSITY 100

input_state buttons;
int current_row = 0;
int current_col = 0;
int currLedAddr;
uint8_t ledIntensity = 40;
bool invert_display = false;

void set_led_state(uint8_t led_address, uint8_t intensity) {
   set_pwm_level(led_address,intensity);
}

// Function to clear all LEDs
void clear_leds() {
    for (int i = 1; i <= ROW_SIZE * COL_SIZE; ++i) {
        set_pwm_level(i, 0);
    }
}

void gpio_callback(uint gpio, uint32_t events)
{
    input_state buttons;
    Read_Port(&buttons);
     
     if(buttons.SW0)
     printf("button 1\n");
     if(buttons.SW1)
     printf("button 2\n");
     if(buttons.SW2)
     printf("button 3\n");
     if(buttons.SW3)
     printf("button 4\n");
     if(buttons.SW4)
     printf("button 5\n");
     if(buttons.SW5)
     printf("button 6\n");
     if(buttons.SW6)
     printf("button 7\n");
     if(buttons.SW7)
     printf("button 8\n");
 
 return;
}

// Function to set the state of a specific LED with fading effect
void set_led_state_fade(uint8_t led_address, uint8_t intensity) {

    uint8_t current_intensity = 0;
    while (current_intensity < intensity) {
        set_led_state(led_address, current_intensity);
        current_intensity++;
        sleep_ms(5);
    }
    set_led_state(led_address, intensity);
}

 int main(){
    stdio_init_all();
    initDisplay(I2C_INSTANCE,SDA_PIN,SCL_PIN,DISP_SDB_PIN);
    PCA9554B_INIT(I2C_INSTANCE,SDA_PIN,SCL_PIN);

    #ifdef ENABLE_INTERRUPT
    enableInterrupt(intPin);
    gpio_set_irq_enabled_with_callback(intPin,GPIO_IRQ_EDGE_RISE,1,gpio_callback);
    #endif

while(1){
  Read_Port(&buttons);
//   clear_leds();
    currLedAddr = current_row * COL_SIZE + current_col + 1;
    set_led_state(currLedAddr, ledIntensity);

    if (buttons.SW1){
        invert_display = !invert_display;
        if (invert_display) {
                // Invert the display
            for (int i = 1; i <= ROW_SIZE * COL_SIZE; ++i) {
                set_led_state(i, MAX_PEAK_INTENSITY - ledIntensity);
            }
            }
            else{
                clear_leds();
                current_col = 0;
                current_row = 0;
                currLedAddr = 0x01;
            }
        sleep_ms(200);
    }
    if (buttons.SW2){
        set_led_state_fade(current_row * COL_SIZE + current_col + 1, 255);
    }
    else{
        if (buttons.SW4 ) {
            clear_leds();
            current_row = (current_row == 0) ? ROW_SIZE - 1 : current_row - 1; // Move up
            sleep_ms(200); 
        } else if (buttons.SW3){
            clear_leds();
            current_row = (current_row == ROW_SIZE - 1) ? 0 : current_row + 1; // Move down
            sleep_ms(200); 
        }

        if (buttons.SW5) {
            clear_leds();
            current_col = (current_col == 0) ? COL_SIZE - 1 : current_col - 1; // Move left
            sleep_ms(200);
        } else if (buttons.SW7) {
            clear_leds();
            current_col = (current_col == COL_SIZE - 1) ? 0 : current_col + 1; // Move right
            sleep_ms(200);
        }
        if(buttons.SW6){
            ledIntensity+=1;
            if(ledIntensity >=255){
                ledIntensity = 254;
            }
            sleep_ms(10);
        }
        else if(buttons.SW0){
            ledIntensity-=1;
            if (ledIntensity <=10){
                ledIntensity = 10;
            }
                sleep_ms(10);
        }
    }
}

}