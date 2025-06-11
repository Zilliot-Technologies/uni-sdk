#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "SHT4X.h"


i2c_inst_t *_instance;
uint8_t _SDA;
uint8_t _SCL;
char *sensorData;

sht4x_data sensordata; // sht40 sensor reading

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

void SHT4X_INITIALIZE()
{
    sht4x_init(_instance);
    setPrecision(SHT4X_HIGH_PRECISION);
    setHeater(SHT4X_NO_HEATER);
}

void SHT4X_Reading()
{
    getEvent(&sensordata);
    #ifdef DEBUG
    printf("Temperature : %.2f C \nHumidity : %.2f\n",sensordata.tempratureC,sensordata.humidity);
    #endif
}

int main(){
    stdio_init_all();
    printf("Hello, world!\n");
    initalize_i2c(i2c1,SDA_PIN,SCL_PIN);
    SHT4X_INITIALIZE();
    
 while(1){
   SHT4X_Reading();  
    sleep_ms(1000);
  }
}