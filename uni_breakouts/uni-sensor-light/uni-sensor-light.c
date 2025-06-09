
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "VEML6030.h"

i2c_inst_t *_instance;
uint8_t _SDA;
uint8_t _SCL;

uint16_t ambient,whiteLevel;  // VEML6030 reading

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

void VEML6030_INITALIZE()
{
    VEML6030_init(_instance);
    power_on();
    VEML6030_config(GAIN_1,ALS_100,ALS_PER_1,ALS_INT_ENABLE,ALS_POWER_ON);
    set_white_High_tresh(10000);
    set_white_Low_tresh(60);
}

void VEML6030_reading()
{  
    ambient = Get_ambient();
    whiteLevel = Get_white();
    #ifdef DEBUG
    printf("Ambient light level : %d \n",ambient);
    printf("White light level : %d \n\n\n",whiteLevel);
    #endif
}

int main(){
    stdio_init_all();
    printf("Hello, world!\n");

    initalize_i2c(i2c1,SDA_PIN,SCL_PIN);

    VEML6030_INITALIZE();
    
 while(1){
    VEML6030_reading();   
    sleep_ms(1000);
  }
}