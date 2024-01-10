#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "disp.h"

i2c_inst_t *IS31FL3729_INSTANCE;

void initDisplay(i2c_inst_t *INSTANCE,uint8_t sdaPin, uint8_t sclPin,uint8_t sdbPin){
  IS31FL3729_INSTANCE = INSTANCE;
  i2c_init(INSTANCE, 100 * 1000);
  gpio_set_function(sdaPin, GPIO_FUNC_I2C);
  gpio_set_function(sclPin, GPIO_FUNC_I2C);
  enableDisplay(sdbPin);
  init_driver();
}

void enableDisplay(uint8_t sdbPin){
  gpio_init(sdbPin);
  gpio_set_dir(sdbPin,1);
  gpio_put(sdbPin,1);
}

void init_driver()
{
  reset();
  set_pwm_level(ALL_LED,0);
  set_scaling_level(ALL_LED,127);
  set_global_current(64);
  set_config(1,0,0,1);
  sleep_ms(10);
}

void set_global_current(uint8_t level)
{
  uint8_t Register_Byte[2];
  // uint8_t x;
  if(level>0x40)
  level=0x40;
  Register_Byte[0]=0xA1;
  Register_Byte[1]=level;
  i2c_write_blocking(IS31FL3729_INSTANCE,ADDRESS_WRITE,Register_Byte,2,false);

}

void set_config(uint8_t SWS,bool HLlevel,uint8_t OSDE,bool shutdown)
{
  uint8_t Register_Byte[2];
  Register_Byte[0]=0xA0;
  Register_Byte[1]=((SWS<<4)|(HLlevel<<3)|(OSDE<<1)|shutdown);
  i2c_write_blocking(IS31FL3729_INSTANCE,ADDRESS_WRITE,Register_Byte,2,false);
}

void reset(void)
{
    uint8_t Register_Byte[2];
  Register_Byte[0]=0xCF;
  Register_Byte[1]=0xAE;
  i2c_write_blocking(IS31FL3729_INSTANCE,ADDRESS_WRITE,Register_Byte,2,false);
}

void set_pwm_level(uint8_t LED,uint8_t level)
{
  if(level>=256)
  level=255;

  // if(LED==ALL_LED)
  // {
  // for(int i=0x01;i<=0x8f;i++)
  // {
  //   uint8_t Register[2];
  //   Register[0]=i;
  //   Register[1]=level;
  //   i2c_write_blocking(IS31FL3729_INSTANCE,ADDRESS_WRITE,Register,2,false);
  // }
  // }
  // else
  // {
  //   if(LED>=128)
  //   return ;
    uint8_t Register[2];
    Register[0]=LED;
    Register[1]=level;
    i2c_write_blocking(IS31FL3729_INSTANCE,ADDRESS_WRITE,Register,2,false);
  // } 
}

void set_scaling_level(uint8_t row ,uint8_t level)
{
    if(level>=256)
    level=255;

    if(row==ALL_LED)
  {
  for(int i=0x90;i<=0x9f;i++)
  {
    uint8_t Register[2];
    Register[0]=i;
    Register[1]=level;
    i2c_write_blocking(IS31FL3729_INSTANCE,ADDRESS_WRITE,Register,2,false);
  }
  }
  else{
    if(row>=16)
    return ;
    uint8_t Register[2];
    Register[0]=row;
    Register[1]=level;
    i2c_write_blocking(IS31FL3729_INSTANCE,ADDRESS_WRITE,Register,2,false);
  }
}

void read_short(void)
{
  set_global_current(1);
   uint8_t addd[2] ;
   addd[0]= 0xB0;
   addd[1]=0x00;

  i2c_write_blocking(IS31FL3729_INSTANCE,ADDRESS_WRITE,addd,2,false);
  uint8_t add = 0xA0;
  uint8_t tempbyte;
  uint8_t updreg[2];

  i2c_write_blocking(IS31FL3729_INSTANCE,ADDRESS_WRITE,&add,1,true);
  i2c_read_blocking(IS31FL3729_INSTANCE,ADDRESS_WRITE,&tempbyte,1,false);
  tempbyte &= 0xF9;
  updreg[0]=0xA0;
  updreg[1]=(tempbyte | 0x01<<1);
  i2c_write_blocking(IS31FL3729_INSTANCE,ADDRESS_WRITE,updreg,2,false);
  uint8_t addr;
  for(int i=0xB3 ;i<=0xC4;i++)
   {
  addr=i;
  uint8_t byte;
    i2c_write_blocking(IS31FL3729_INSTANCE,ADDRESS_WRITE,&addr,1,true);
    i2c_read_blocking(IS31FL3729_INSTANCE,ADDRESS_WRITE,&byte,1,false);
    printf("%d \n",byte);
  }
}



