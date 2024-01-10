#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "uni_click.h"

bool inversion = 0;
inversion_state polarity;
i2c_inst_t *PCA9554B_INSTANCE;

void PCA9554B_INIT(i2c_inst_t *INSTANCE)
{
PCA9554B_INSTANCE = INSTANCE;
}

void Read_Port(input_state *this)
{ 
   uint8_t point=0x00;
   uint8_t Register ;
   i2c_write_blocking(PCA9554B_INSTANCE,PCA9554B_ADDR,&point,1,true);
   i2c_read_blocking(PCA9554B_INSTANCE,PCA9554B_ADDR,&Register,1,false);
   if(inversion)
   {
   this->SW0= Register & 1 ;
   this->SW1= Register & 1 << 1 ;
   this->SW2= Register & 1 << 2 ;
   this->SW3= Register & 1 << 3 ;
   this->SW4= Register & 1 << 4 ;
   this->SW5= Register & 1 << 5 ;
   this->SW6= Register & 1 << 6 ;
   this->SW7= Register & 1 << 7 ;
  }
   else{
   this->SW0= ~Register & 1 ;
   this->SW1= ~Register & 1 << 1 ;
   this->SW2= ~Register & 1 << 2 ;
   this->SW3= ~Register & 1 << 3 ;
   this->SW4= ~Register & 1 << 4 ;
   this->SW5= ~Register & 1 << 5 ;
   this->SW6= ~Register & 1 << 6 ;
   this->SW7= ~Register & 1 << 7 ;
   }
}

void set_output(uint8_t port,bool state)
{  
   uint8_t point=0x01;
   uint8_t temp;
   uint8_t Register[2] ;
    Register[0]=0x01;
   i2c_write_blocking(PCA9554B_INSTANCE,PCA9554B_ADDR,&point,1,true);
   i2c_read_blocking(PCA9554B_INSTANCE,PCA9554B_ADDR,&temp,1,false);
 if(port==ALL_PORT)
 {
  if(state)
  Register[1]=0xFF;
  else
  Register[1]=0x00;

  i2c_write_blocking(PCA9554B_INSTANCE,PCA9554B_ADDR,Register,2,false); 
 }
 else
 {
 if(port>=8)
 return;
 Register[1]= (temp|state<<port) ;
 i2c_write_blocking(PCA9554B_INSTANCE,PCA9554B_ADDR,Register,2,false); 
 }
}

void readpolarity(inversion_state *this)
{
    uint8_t point=0x00;
   uint8_t Register ;
   i2c_write_blocking(PCA9554B_INSTANCE,PCA9554B_ADDR,&point,1,true);
   i2c_read_blocking(PCA9554B_INSTANCE,PCA9554B_ADDR,&Register,1,false);
   this->SW0= Register & 1 ;
   this->SW1= Register & 1 << 1 ;
   this->SW2= Register & 1 << 2 ;
   this->SW3= Register & 1 << 3 ;
   this->SW4= Register & 1 << 4 ;
   this->SW5= Register & 1 << 5 ;
   this->SW6= Register & 1 << 6 ;
   this->SW7= Register & 1 << 7 ;   
}



void set_port_dir(uint8_t port,bool state)
{
   uint8_t point=0x03;
   uint8_t temp;
   uint8_t Register[2] ;
    Register[0]=0x03;
   i2c_write_blocking(PCA9554B_INSTANCE,PCA9554B_ADDR,&point,1,true);
   i2c_read_blocking(PCA9554B_INSTANCE,PCA9554B_ADDR,&temp,1,false);

 if(port==ALL_PORT)
 {
  if(state)
  Register[1]=0xFF;
  else
  Register[1]=0x00;

  i2c_write_blocking(PCA9554B_INSTANCE,PCA9554B_ADDR,Register,2,false); 
 }
 else
 {
 if(port>=8)
 return;
 if(state)
 Register[1]=(temp|state<<port);
 else
 {
   uint8_t mask=0x00;
   mask|=(!state)<<port;
   mask= ~mask;
 Register[1]= (temp|mask) ;
 }
 i2c_write_blocking(PCA9554B_INSTANCE,PCA9554B_ADDR,Register,2,false); 
 }
}

void set_inversion(uint8_t port,bool state)
  {
   inversion = state; 
   uint8_t point=0x02;
   uint8_t temp;
   uint8_t Register[2] ;
   Register[0]=0x02;
   i2c_write_blocking(PCA9554B_INSTANCE,PCA9554B_ADDR,&point,1,true);
   i2c_read_blocking(PCA9554B_INSTANCE,PCA9554B_ADDR,&temp,1,false);
 if(port==ALL_PORT)
 {
  if(state)
  Register[1]=0xFF;
  else
  Register[1]=0x00;

  i2c_write_blocking(PCA9554B_INSTANCE,PCA9554B_ADDR,Register,2,false); 
 }
 else
 {
 if(port>=8)
 return;
 if(state)
 Register[1]=(temp|state<<port);
 else
 {
   uint8_t mask=0x00;
   mask|=(!state)<<port;
   mask= ~mask;
 Register[1]= (temp|mask) ;
 }
 i2c_write_blocking(PCA9554B_INSTANCE,PCA9554B_ADDR,Register,2,false); 
 }
}



