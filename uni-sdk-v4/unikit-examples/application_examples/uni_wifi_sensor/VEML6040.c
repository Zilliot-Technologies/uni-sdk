/*
*************TMP-102********************
**********Date:04/11/23*****************
**********Author:Tushar D**************
*/
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "VEML6040.h"

i2c_inst_t *VEML6040_INSTANCE;

void VEML6040_init(i2c_inst_t *INSTANCE)
{
   VEML6040_INSTANCE = INSTANCE;
}

void Read_colour(color_t *this)
{

  this->Red = Get_Red();

  this->Green = Get_Green();

  this->Blue = Get_Blue();

  this->White = Get_White();
}

uint16_t Get_Red()
{
  uint8_t point=0x08;
  uint8_t RegisterByte[2];
  i2c_write_blocking(VEML6040_INSTANCE,VEML_6040_ADDR,&point,1,true);
  i2c_read_blocking(VEML6040_INSTANCE,VEML_6040_ADDR,RegisterByte,2,false);
  return (RegisterByte[0]|RegisterByte[1]<<8);
}

uint16_t Get_Green()
{
  uint8_t point=0x09;
  uint8_t RegisterByte[2];
  i2c_write_blocking(VEML6040_INSTANCE,VEML_6040_ADDR,&point,1,true);
  i2c_read_blocking(VEML6040_INSTANCE,VEML_6040_ADDR,RegisterByte,2,false);
  uint16_t data = (RegisterByte[0]|RegisterByte[1]<<8);
  return data;
}

uint16_t Get_Blue()
{
  uint8_t point=0x0A;
  uint8_t RegisterByte[2];
  i2c_write_blocking(VEML6040_INSTANCE,VEML_6040_ADDR,&point,1,true);
  i2c_read_blocking(VEML6040_INSTANCE,VEML_6040_ADDR,RegisterByte,2,false);
  return (RegisterByte[0]|RegisterByte[1]<<8);
}


uint16_t Get_White()
{
  uint8_t point=0x0B;
  uint8_t RegisterByte[2];
  i2c_write_blocking(VEML6040_INSTANCE,VEML_6040_ADDR,&point,1,true);
  i2c_read_blocking(VEML6040_INSTANCE,VEML_6040_ADDR,RegisterByte,2,false);
  return (RegisterByte[0]|RegisterByte[1]<<8);
}



void configure(uint8_t VEML_IT_,bool trigger,bool force_mode,bool shutdown)
{
    if(VEML_IT_>5)
    VEML_IT_=5;

    uint8_t RegisterByte[2];
    RegisterByte[0]=0x00;
    RegisterByte[1]=((VEML_IT_)|(trigger)|(force_mode)|(shutdown));
    RegisterByte[1] &= 0x77;
    i2c_write_blocking(VEML6040_INSTANCE,VEML_6040_ADDR,RegisterByte,2,false);

}

uint8_t last_config()
{
    uint8_t point=0x00;
    uint8_t RegisterByte[2];
    i2c_write_blocking(VEML6040_INSTANCE,VEML_6040_ADDR,&point,1,true);
    i2c_read_blocking(VEML6040_INSTANCE,VEML_6040_ADDR,RegisterByte,2,false);
  return RegisterByte[0];  
}

uint16_t get_ambient_light()
{
    uint16_t sensorValue; 
  float ambientLightInLux;
  
  sensorValue = Get_Green();
  uint16_t lastConfiguration = last_config();
  
  switch(lastConfiguration & 0x70) {
  
    case VEML6040_IT_40MS:    ambientLightInLux = sensorValue * VEML6040_GSENS_40MS;
                              break;
    case VEML6040_IT_80MS:    ambientLightInLux = sensorValue * VEML6040_GSENS_80MS;
                              break;
    case VEML6040_IT_160MS:   ambientLightInLux = sensorValue * VEML6040_GSENS_160MS;
                              break;
    case VEML6040_IT_320MS:   ambientLightInLux = sensorValue * VEML6040_GSENS_320MS;
                              break;
    case VEML6040_IT_640MS:   ambientLightInLux = sensorValue * VEML6040_GSENS_640MS;
                              break; 
    case VEML6040_IT_1280MS:  ambientLightInLux = sensorValue * VEML6040_GSENS_1280MS; 
                              break;   
    default:                  ambientLightInLux = -1;
                              break;                             
  } 
  return ambientLightInLux;
}

// uint16_t getCCT(float offset) {
//   uint16_t red,blue,green;
//   float cct,ccti;
  
//   red = Get_Red;
//   green = Get_Green;
//   blue = Get_Blue;
  
//   ccti = ((float)red-(float)blue) / (float)green;
//   ccti = ccti + offset; 
//   cct = 4278.6 * pow(ccti,-1.2455);
  
//   return((uint16_t)cct);
// }



