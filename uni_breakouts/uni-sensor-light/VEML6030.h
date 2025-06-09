#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define ALS_CONF_REG 0x00
#define ALS_WH_REG 0x01
#define ALS_WL_REG 0x02
#define ALS_INT_REG 0x06
#define ALS_REG 0x04
#define WHITE_REG 0x05

#define VEML_6030_ADDR 0x48

enum ALS_GAIN{
    GAIN_1, 
    GAIN_2,
    GAIN_1_8,
    GAIN_1_4,
};

enum ALS_IT {
    ALS_25 = 12,       // 25ms
    ALS_50 = 8,        // 50ms
    ALS_100 = 0,         // 100ms
    ALS_200 = 1,       // 200ms
    ALS_400 = 2,       // 400ms
    ALS_800 = 3,       // 800ms
};

enum ALS_INT_EN{
    ALS_INT_DISABLE,
    ALS_INT_ENABLE
};

enum ALS_SD{
    ALS_POWER_ON,
    ALS_SHUTDOWN
};
enum ALS_PERS{
    ALS_PER_1 ,
    ALS_PER_2,
    ALS_PER_4,
    ALS_PER_8   
};

void VEML6030_init(i2c_inst_t *INSTANCE);
void VEML6030_config(uint8_t gain,uint8_t ALS_intergration,uint8_t ALS_persistance,bool INT_en,bool SD);
void power_on();
void set_white_High_tresh(uint16_t tresholdHigh);
void set_white_Low_tresh(uint16_t tresholdLow);
uint8_t VEML6030_interrupt();
uint16_t Get_ambient();
uint16_t Get_white();