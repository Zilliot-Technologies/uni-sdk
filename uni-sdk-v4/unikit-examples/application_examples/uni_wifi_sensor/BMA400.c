#include <stdio.h>
#include "pico/stdlib.h"
#include "BMA400.h"

i2c_inst_t *BMA_INSTANCE;
uint8_t BMA_SDA;
uint8_t BMA_SCL;

void initBMP(i2c_inst_t *INSTANCE)
//void initBMP(void)
{
  //  i2c_init(BMA_INSTANCE, 100 * 1000);
  //   gpio_set_function(22, GPIO_FUNC_I2C);
  //   gpio_set_function(23, GPIO_FUNC_I2C);
  //   gpio_pull_up(22);
  //   gpio_pull_up(23);
    uint8_t chipid;
    BMA_INSTANCE = INSTANCE;
    i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,CHIP_ID_REG,1,true);
    i2c_read_blocking(BMA_INSTANCE,BMP_ADDRESS,&chipid,1,false);
    if(chipid==0x90)
    {
        return ;
    }
    else
    printf("BMA error,try again\n");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void enablestep(void)
{
  uint8_t RegisterByte[2];
   RegisterByte[0]=0x20;
  RegisterByte[1]=0x01;
    i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,RegisterByte,2,false);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void set_G_range(uint8_t range)
{
  range = (range/4)-1;
  range &= 0x03;
  uint8_t addr=0x1A,temp;
  uint8_t Register_Byte[2];
   i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,&addr,1,true);
    i2c_read_blocking(BMA_INSTANCE,BMP_ADDRESS,&temp,1,false);
  temp &= 0x3F;  
  Register_Byte[0]=0x1A;
  Register_Byte[1]= (temp|range<<6) ;
  i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,Register_Byte,2,false);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void filt1_BW(bool state)
{
uint8_t addr=0x19,temp;
  uint8_t Register_Byte[2];
   i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,&addr,1,true);
    i2c_read_blocking(BMA_INSTANCE,BMP_ADDRESS,&temp,1,false);
  temp &= 0x7F;  
  Register_Byte[0]=0x19;
  Register_Byte[1]= (temp|state<<7) ;
  i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,Register_Byte,2,false);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void softreset(void)
{
  uint8_t RegisterByte[2];
   RegisterByte[0]=0x7E;
  RegisterByte[1]=0xb6;
    i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,RegisterByte,2,false);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void clearstepcount(void)
{
  uint8_t RegisterByte[2];
   RegisterByte[0]=0x7E;
  RegisterByte[1]=0xb1;
    i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,RegisterByte,2,false);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stepstate(void)
{
    uint8_t Register_Byte;
  uint8_t point=0x18;
    i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,&point,1,true);
    i2c_read_blocking(BMA_INSTANCE,BMP_ADDRESS,&Register_Byte,1,false);
    if(Register_Byte==0)
    printf("still\n");
    if(Register_Byte==1)
    printf("walking\n");
      if(Register_Byte==2)
    printf("running\n");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void conf_orientation_change(Param_orient_change *this )
{
  this->AXIS_SELECT &= 0x07;

  this->DATA_SRC &= 0x01;
  
  if(this->ORIENT_REF_UPDATE >3)
  this->ORIENT_REF_UPDATE=0;
  this->ORIENT_REF_UPDATE &= 0x03;
    
  if(this->STABILITY_MODE >2)
  this->STABILITY_MODE = 0;
  this->STABILITY_MODE &= 0x03;

  if(this->ORIENT_TRESH >255)
  this->ORIENT_TRESH  =255;

  if(this->STABILITY_TRESH >255)
   this->STABILITY_TRESH = 255;

  if(this->ORIENT_DUR >255)
  this->ORIENT_DUR = 255;

  if(this->ORIENT_REF_X > 0xFFF)
  this->ORIENT_REF_X = 0xFFF;
  this->ORIENT_REF_X &= 0x0FFF;

  if(this->ORIENT_REF_Y >0xFFF)
  this->ORIENT_REF_Y = 0xFFF;
  this->ORIENT_REF_Y &= 0x0FFF;

  if(this->ORIENT_REF_Z >0xFFF)
  this->ORIENT_REF_Z = 0xFFF;
  this->ORIENT_REF_Z &= 0x0FFF;

  uint8_t Register_Byte[20];
  Register_Byte[0]=0x35;
  Register_Byte[1]=((this->AXIS_SELECT<<5)|(this->DATA_SRC<<4)|(this->ORIENT_REF_UPDATE<<2)|(this->STABILITY_MODE));
  Register_Byte[2]=0x36;
  Register_Byte[3]= this->ORIENT_TRESH;
  Register_Byte[4]=0x37; 
  Register_Byte[5]= this->STABILITY_TRESH;
  Register_Byte[6]=0x38;
  Register_Byte[7]= this->ORIENT_DUR;
  Register_Byte[8]=0x39;
  Register_Byte[9]= this->ORIENT_REF_X;
  Register_Byte[10]=0x3A;
  Register_Byte[11]= this->ORIENT_REF_X>>8;
  Register_Byte[12]=0x3B;
  Register_Byte[13]= this->ORIENT_REF_Y;
  Register_Byte[14]=0x3C;
  Register_Byte[15]= this->ORIENT_REF_Y >>8;
  Register_Byte[16]=0x3D;
  Register_Byte[17]= this->ORIENT_REF_Z;
  Register_Byte[18]=0x3E;
  Register_Byte[19]= this->ORIENT_REF_Z >>8;

  i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,Register_Byte,20,false); 
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void conf_genint1(Param_genint1 *this )
{
  this->AXIS_SELECT &= 0x07;

  this->DATA_SRC &= 0x01;
  
  if(this->GEN1_REF_UPDATE >3)
  this->GEN1_REF_UPDATE = 0;
  this->GEN1_REF_UPDATE &= 0x03;

  if(this->GEN1_ACT_HYST >3)
  this->GEN1_ACT_HYST = 0;
  this->GEN1_ACT_HYST &= 0x03; 

  if(this->GEN_INT1_TRESH >255)
  this->GEN_INT1_TRESH  =255;

  if(this->GEN_INT1_DUR > 0xFFFF)
  this->GEN_INT1_DUR = 0xFFFF ;

  if(this->INT1_REF_X > 0xFFF)
  this->INT1_REF_X= 0xFFF;
  this->INT1_REF_X &= 0x0FFF;

  if(this->INT1_REF_Y >0xFFF)
  this->INT1_REF_Y = 0xFFF;
  this->INT1_REF_Y &= 0x0FFF;

  if(this->INT1_REF_Z >0xFFF)
  this->INT1_REF_Z = 0xFFF;
  this->INT1_REF_Z &= 0x0FFF;

  uint8_t Register_Byte[22];
  Register_Byte[0]=0x3F;
  Register_Byte[1]=((this->AXIS_SELECT<<5)|(this->DATA_SRC<<4)|(this->GEN1_REF_UPDATE<<2)|(this->GEN1_ACT_HYST));
  Register_Byte[2]=0x40;
  Register_Byte[3]= ((this->CRITERION_SEL<<1)|(this->COMB_SEL));
  Register_Byte[4]=0x41; 
  Register_Byte[5]= this->GEN_INT1_TRESH;
  Register_Byte[6]=0x42;
  Register_Byte[7]= this->GEN_INT1_DUR>>8;
  Register_Byte[8]=0x43;
  Register_Byte[9]= this->GEN_INT1_DUR;
  Register_Byte[10]=0x44;
  Register_Byte[11]= this->INT1_REF_X;
  Register_Byte[12]=0x45;
  Register_Byte[13]= this->INT1_REF_X>>8;
  Register_Byte[14]=0x46;
  Register_Byte[15]= this->INT1_REF_Y;
  Register_Byte[16]=0x47;
  Register_Byte[17]= this->INT1_REF_Y>>8;
  Register_Byte[18]=0x48;
  Register_Byte[19]= this->INT1_REF_Z;
  Register_Byte[20]=0x49;
  Register_Byte[21]= this->INT1_REF_Z>>8;


  i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,Register_Byte,22,false); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void conf_genint2(Param_genint2 *this )
{
  this->AXIS_SELECT &= 0x07;

  this->DATA_SRC &= 0x01;
  
  if(this->GEN2_REF_UPDATE >3)
  this->GEN2_REF_UPDATE = 0;
  this->GEN2_REF_UPDATE &= 0x03;

  if(this->GEN2_ACT_HYST >3)
  this->GEN2_ACT_HYST = 0;
  this->GEN2_ACT_HYST &= 0x03; 

  if(this->GEN_INT2_TRESH >255)
  this->GEN_INT2_TRESH  =255;

  if(this->GEN_INT2_DUR > 0xFFFF)
  this->GEN_INT2_DUR = 0xFFFF ;

  if(this->INT2_REF_X > 0xFFF)
  this->INT2_REF_X= 0xFFF;
  this->INT2_REF_X &= 0x0FFF;

  if(this->INT2_REF_Y >0xFFF)
  this->INT2_REF_Y = 0xFFF;
  this->INT2_REF_Y &= 0x0FFF;

  if(this->INT2_REF_Z >0xFFF)
  this->INT2_REF_Z = 0xFFF;
  this->INT2_REF_Z &= 0x0FFF;

  uint8_t Register_Byte[22];
  Register_Byte[0]=0x4A;
  Register_Byte[1]=((this->AXIS_SELECT<<5)|(this->DATA_SRC<<4)|(this->GEN2_REF_UPDATE<<2)|(this->GEN2_ACT_HYST));
  Register_Byte[2]=0x4B;
  Register_Byte[3]= ((this->CRITERION_SEL<<1)|(this->COMB_SEL));
  Register_Byte[4]=0x4C; 
  Register_Byte[5]= this->GEN_INT2_TRESH;
  Register_Byte[6]=0x4D;
  Register_Byte[7]= this->GEN_INT2_DUR>>8;
  Register_Byte[8]=0x4E;
  Register_Byte[9]= this->GEN_INT2_DUR;
  Register_Byte[10]=0x4F;
  Register_Byte[11]= this->INT2_REF_X;
  Register_Byte[12]=0x50;
  Register_Byte[13]= this->INT2_REF_X>>8;
  Register_Byte[14]=0x51;
  Register_Byte[15]= this->INT2_REF_Y;
  Register_Byte[16]=0x52;
  Register_Byte[17]= this->INT2_REF_Y>>8;
  Register_Byte[18]=0x53;
  Register_Byte[19]= this->INT2_REF_Z;
  Register_Byte[20]=0x54;
  Register_Byte[21]= this->INT2_REF_Z>>8;


  i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,Register_Byte,22,false); 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fifoflush(void)
{
   uint8_t RegisterByte[2];
   RegisterByte[0]=0x7E;
  RegisterByte[1]=0xb0;
    i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,RegisterByte,2,false);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setmode(int8_t mode)
{
       uint8_t RegisterByte[2];
  uint8_t point=0x19;
      i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,&point,1,true);
    i2c_read_blocking(BMA_INSTANCE,BMP_ADDRESS,&RegisterByte[1],1,false);
 
  RegisterByte[0]=0x19;
  RegisterByte[1]&=0xFC;
  RegisterByte[1]|=mode;
  i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,RegisterByte,2,false); 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void readACC(ACC *this)
{
    uint8_t Register_Byte[6];
    uint8_t acc=0x04;
    i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,&acc,1,true);
    i2c_read_blocking(BMA_INSTANCE,BMP_ADDRESS,Register_Byte,6,false);
   
   
     this->X = Register_Byte[0]+256*(Register_Byte[1]);
    if(this->X >2047)
    {
   this->X=this->X-4096;
    }
     this->Y = Register_Byte[2]|(Register_Byte[3]<<8);
    if(this->Y >2047)
    {
    this->Y = this->Y-4096;
    }
     this->Z = Register_Byte[4]|(Register_Byte[5]<<8);
    if(this->Z >2047)
    {
    this->Z = this->Z-4096;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int stepcount(void)
{
  uint8_t Register_Byte[3];
  uint8_t point=0x15;
      i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,&point,1,true);
    i2c_read_blocking(BMA_INSTANCE,BMP_ADDRESS,Register_Byte,3,false);
    uint32_t steps = Register_Byte[0]|(Register_Byte[1]<<8)|(Register_Byte[2]<<16);
 return steps;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void set_interrupt(int interrupt,bool state)
{
 uint8_t temp[2];
  uint8_t point=0x1F;
  i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,&point,1,true);
  i2c_read_blocking(BMA_INSTANCE,BMP_ADDRESS,temp,2,false);
  uint8_t Register_Byte[4];
  uint16_t Register=(temp[1]|temp[0]<<8);
  Register|=(state<<interrupt);
  Register_Byte[0]=0x1F;
  Register_Byte[1]=Register>>8;
  Register_Byte[2]=0x20;
  Register_Byte[3]=Register;
  i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,Register_Byte,4,false);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mapinterrupt1(u_int8_t inter,bool state)
{
  uint8_t temp;
  uint8_t point=0x21;
  i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,&point,1,true);
   i2c_read_blocking(BMA_INSTANCE,BMP_ADDRESS,&temp,1,false);
   uint8_t Register_Byte[2];
   Register_Byte[0]=0x21;
   Register_Byte[1]=(temp|(state<<inter));
   i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,Register_Byte,2,false);
    
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setautolowpower(uint16_t treshold , uint8_t timeout,bool genint,bool dataready)
{
  treshold &= 0xFFF;
  timeout &= 0x03;
  uint8_t Register_Byte[4]; 
  Register_Byte[0]=0x2A;
  Register_Byte[1]=treshold>>4;
  Register_Byte[2]=0x2B;
  Register_Byte[3]=(treshold<<4|timeout<<2|genint<<1|dataready);
  i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,Register_Byte,4,false);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setautowakeup(uint16_t treshold,bool wakeup_timeout,bool wake_int)
{
  treshold &= 0xFFF;
  uint8_t Register_Byte[4];
  Register_Byte[0]=0x2C;
  Register_Byte[1]=treshold>>4;
  Register_Byte[2]=0x2D;
  Register_Byte[3]=(treshold<<4 | wakeup_timeout<<2 | wake_int<<1);
  i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,Register_Byte,4,false);
 }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void configwakeup(param_wakeup *this)
{
  this->AXIS_SELECT &= 0x07;

  this->SAMPLES &= 0x07;

  this->REF_UPDATE &= 3;

  if(this->TRESHOLD == 0xFF)
  {
    this->TRESHOLD = 0xFF;
  }

    if(this->REF_X == 0xFF)
  {
    this->REF_X = 0xFF;
  }

    if(this->REF_Y == 0xFF)
  {
    this->REF_Y = 0xFF;
  }

      if(this->REF_Z == 0xFF)
  {
    this->REF_Z = 0xFF;
  }

  uint8_t REGISTER_BYTE[10];
  REGISTER_BYTE[0] = 0X2F;
  REGISTER_BYTE[1] = ((this->AXIS_SELECT<<5)|(this->SAMPLES<<2)|this->REF_UPDATE);
  REGISTER_BYTE[2] = 0X30;
  REGISTER_BYTE[3] = this->TRESHOLD;
  REGISTER_BYTE[2] = 0X31;
  REGISTER_BYTE[3] = this->REF_X;
  REGISTER_BYTE[2] = 0X32;
  REGISTER_BYTE[3] = this->REF_Y;
  REGISTER_BYTE[2] = 0X33;
  REGISTER_BYTE[3] = this->REF_Z;
  
  i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,REGISTER_BYTE,10,false);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mapinterrupt2(uint8_t inter,bool state)
{
  uint8_t temp;
  uint8_t point=0x22;
  i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,&point,1,true);
   i2c_read_blocking(BMA_INSTANCE,BMP_ADDRESS,&temp,1,false);
   uint8_t Register_Byte[2];
   Register_Byte[0]=0x22;
   Register_Byte[1]=(temp|(state<<inter));
   i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,Register_Byte,2,false);
    
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mapinterrupt12 (uint8_t inter,bool state)
{
uint8_t temp;
  uint8_t point=0x23;
  i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,&point,1,true);
   i2c_read_blocking(BMA_INSTANCE,BMP_ADDRESS,&temp,1,false);
   uint8_t Register_Byte[2];
   Register_Byte[0]=0x23;
   Register_Byte[1]=(temp|(state<<inter));
   i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,Register_Byte,2,false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void config_tap(uint8_t axis , uint8_t sensitivity ,uint8_t quiet_dt,uint8_t quiet,uint8_t tics_th)
{
axis &= 0x03;
sensitivity &= 0x07;
quiet &= 0x03;
quiet_dt &= 0x03;
tics_th &= 0x03;
uint8_t Register_Byte[3];
Register_Byte[0]=0x57;
Register_Byte[1] = (axis<<3|sensitivity);
Register_Byte[2] = 0x58;
Register_Byte[3] = (quiet_dt<<4|quiet<<2|tics_th);+
i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,Register_Byte,4,false);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void check_tap(void)
{
      uint8_t tap;
    uint8_t add=0x0F;
    i2c_write_blocking(BMA_INSTANCE,BMP_ADDRESS,&add,1,true);
    i2c_read_blocking(BMA_INSTANCE,BMP_ADDRESS,&tap,1,false);
    if(tap==4)
    {
    printf("single tap\n");
    sleep_ms(50);
    }
    if(tap==8)
    {
    printf("double tap\n");
    sleep_ms(50);
    } 
}


