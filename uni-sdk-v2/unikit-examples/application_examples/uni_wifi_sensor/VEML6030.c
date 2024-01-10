/*
*************TMP-102********************
**********Date:04/11/23*****************
**********Author:Tushar D**************
*/
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "VEML6030.h"

i2c_inst_t *VEML6030_INSTANCE;

void VEML6030_init(i2c_inst_t *INSTANCE)
{
   VEML6030_INSTANCE = INSTANCE;
}

void VEML6030_config(uint8_t gain,uint8_t ALS_intergration,uint8_t ALS_persistance,bool INT_en,bool SD)
{
uint8_t RegisterByte[3];
uint16_t Register = ((gain<<11)|(ALS_intergration<<6)|(ALS_persistance<<4)|(INT_en<<1)| (SD) );
Register &= 0x1BF3;
RegisterByte[0]=0x00;
RegisterByte[1]=Register;
RegisterByte[2]=Register>>8;
i2c_write_blocking(VEML6030_INSTANCE,VEML_6030_ADDR,RegisterByte,3,false);
}

void power_on()
{
    uint8_t Register[2];
    Register[0]=0x00;
    Register[1]=0x00;
    i2c_write_blocking(VEML6030_INSTANCE,VEML_6030_ADDR,Register,2,false);
}

void set_white_High_tresh(uint16_t tresholdHigh)
{
  tresholdHigh&=0xFFFF;
  uint8_t RegisterByte[3];
  RegisterByte[0]=0x01;
  RegisterByte[1]=tresholdHigh;
  RegisterByte[2]=tresholdHigh>>8;
  i2c_write_blocking(VEML6030_INSTANCE,VEML_6030_ADDR,RegisterByte,3,false);
}

void set_white_Low_tresh(uint16_t tresholdLow)
{
  tresholdLow&=0xFFFF;
  uint8_t RegisterByte[3];
  RegisterByte[0]=0x02;
  RegisterByte[1]=tresholdLow;
  RegisterByte[2]=tresholdLow>>8;
  i2c_write_blocking(VEML6030_INSTANCE,VEML_6030_ADDR,RegisterByte,3,false);
}

uint8_t VEML6030_interrupt()
{
   uint8_t point=0x06;
  uint8_t RegisterByte[2];
  i2c_write_blocking(VEML6030_INSTANCE,VEML_6030_ADDR,&point,1,true);
  i2c_read_blocking(VEML6030_INSTANCE,VEML_6030_ADDR,RegisterByte,2,false);
  if((RegisterByte[1]>>6)==2)
  {
   printf("light low\n");
   return 1;
  }
  if((RegisterByte[1]>>6)==1)
  {
   printf("light high\n");
   return 2;
  }
  return 0;
}



uint16_t Get_ambient()
{
  uint8_t point=0x04;
  uint8_t RegisterByte[2];
  i2c_write_blocking(VEML6030_INSTANCE,VEML_6030_ADDR,&point,1,true);
  i2c_read_blocking(VEML6030_INSTANCE,VEML_6030_ADDR,RegisterByte,2,false);
  return (RegisterByte[0]|RegisterByte[1]<<8);
}

uint16_t Get_white()
{
  uint8_t point=0x05;
  uint8_t RegisterByte[2];
  i2c_write_blocking(VEML6030_INSTANCE,VEML_6030_ADDR,&point,1,true);
  i2c_read_blocking(VEML6030_INSTANCE,VEML_6030_ADDR,RegisterByte,2,false);
  return (RegisterByte[0]|RegisterByte[1]<<8);
}

