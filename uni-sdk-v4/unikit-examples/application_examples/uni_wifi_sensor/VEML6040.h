#include <stdio.h>
#include "pico/stdlib.h"

#define VEML_6040_ADDR 0x10


// REGISTER CONF (00H) SETTINGS

#define VEML6040_IT_40MS       0x00
#define VEML6040_IT_80MS       0x10
#define VEML6040_IT_160MS      0x20
#define VEML6040_IT_320MS      0x30
#define VEML6040_IT_640MS      0x40
#define VEML6040_IT_1280MS     0x50

#define VEML6040_TRIG_DISABLE  0x00
#define VEML6040_TRIG_ENABLE   0x04

#define VEML6040_AF_AUTO       0x00
#define VEML6040_AF_FORCE      0x02

#define VEML6040_SD_ENABLE     0x00
#define VEML6040_SD_DISABLE    0x01 
// G SENSITIVITY

#define VEML6040_GSENS_40MS       0.25168
#define VEML6040_GSENS_80MS       0.12584
#define VEML6040_GSENS_160MS      0.06292
#define VEML6040_GSENS_320MS      0.03146
#define VEML6040_GSENS_640MS      0.01573
#define VEML6040_GSENS_1280MS     0.007865

typedef struct VEML6040
{
 uint16_t Red;
 uint16_t Green;
 uint16_t Blue;
 uint16_t White; 
}color_t;


void VEML6040_init(i2c_inst_t *INSTANCE);
uint16_t Get_Red();
uint16_t Get_Green();
uint16_t Get_Blue();
uint16_t Get_White();
void configure(uint8_t VEML_IT_,bool trigger,bool force_mode,bool enable);
uint8_t last_config();
void Read_colour(color_t *this);
uint16_t get_ambient_light();
// uint16_t getCCT(float offset)