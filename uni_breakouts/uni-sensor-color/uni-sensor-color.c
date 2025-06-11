#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "VEML6040.h"

i2c_inst_t *_instance;
uint8_t _SDA;
uint8_t _SCL;

color_t light;   // VEML6040 reading

#define SDA_PIN 22
#define SCL_PIN 23
#define DEBUG

void initalize_i2c(i2c_inst_t *instance,uint8_t SDA,uint8_t SCL)
{
    i2c_init(instance, 100 * 1000);
    gpio_set_function(SDA, GPIO_FUNC_I2C);
    gpio_set_function(SCL, GPIO_FUNC_I2C);
    gpio_pull_up(SDA);
    gpio_pull_up(SCL);
    _instance = instance;
    _SDA = SDA;
    _SCL = SCL;

}

void VEML6040_INITALIZE()
{
    VEML6040_init(_instance); 
    configure(0,0,0,0);
}

void VEML6040_Reading()
{   
    Read_colour(&light);
    #ifdef DEBUG
    printf("Red: %d , Green: %d , Blue : %d\n",light.Red,light.Green,light.Blue);
    printf("White :%d\n",light.White);
    printf("Ambient Light : %d \n",get_ambient_light());
    #endif
}
int main(){
    stdio_init_all();
    printf("Hello, world!\n");
    initalize_i2c(i2c1,SDA_PIN,SCL_PIN);
    VEML6040_INITALIZE();
    
 while(1){
    VEML6040_Reading();  
    sleep_ms(1000);
  }
}