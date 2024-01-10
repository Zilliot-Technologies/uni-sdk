#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define ADDRESS_WRITE 0x34
#define ADDRESS_READ 0x35

#define ALL_LED 0X80


// void init_driver(void);
void init_driver();
void initDisplay(i2c_inst_t *INSTANCE,uint8_t sdaPin, uint8_t sclPin,uint8_t sdbPin);
void enableDisplay(uint8_t sdbPin);
void set_global_current(uint8_t level);
void set_config(uint8_t SWS,bool HLlevel,uint8_t OSDE,bool shutdown);
void set_pwm_level(uint8_t LED,uint8_t level);
void set_scaling_level(uint8_t row ,uint8_t level);
void reset(void);
bool set_led(uint8_t sw, uint8_t cs, uint8_t val);



