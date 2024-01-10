#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"


#define VEML_6030_ADDR 0x48

void VEML6030_init(i2c_inst_t *INSTANCE);
void VEML6030_config(uint8_t gain,uint8_t ALS_intergration,uint8_t ALS_persistance,bool INT_en,bool SD);
void power_on();
void set_white_High_tresh(uint16_t tresholdHigh);
void set_white_Low_tresh(uint16_t tresholdLow);
uint8_t VEML6030_interrupt();
uint16_t Get_ambient();
uint16_t Get_white();