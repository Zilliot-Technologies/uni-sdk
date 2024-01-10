#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "BMA400.h"
#include "SHT4X.h"
#include "VEML6030.h"
#include "VEML6040.h"

i2c_inst_t *_instance;
uint8_t _SDA;
uint8_t _SCL;
char *sensorData;

sht4x_data sensordata; // sht40 sensor reading
ACC data; ;      // BMA xyz reading
color_t light;   // VEML6040 reading
uint16_t ambient,whiteLevel;  // VEML6030 reading

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

void BMA_INITIALIZE()
{
    initBMP(_instance);
    sleep_ms(200);
    softreset();
    sleep_ms(200);
    setmode(normal_mode);
    set_G_range(8);
}

void changeOrient(){
    Param_orient_change orient;
    orient.AXIS_SELECT = 7;
    orient.DATA_SRC = 1;
    orient.ORIENT_REF_UPDATE = 0;
    orient.STABILITY_MODE=0;
    orient.ORIENT_TRESH=100;
    orient.STABILITY_TRESH=50;
    orient.ORIENT_DUR=7;
    orient.ORIENT_REF_X=0;
    orient.ORIENT_REF_Y=0;
    orient.ORIENT_REF_Z=500;
    set_interrupt(orient_int_en,1);
    mapinterrupt1(orient_int,1);
    conf_orientation_change(&orient);
    sleep_ms(200);
}

void enableInterrupt1(){
    Param_genint1 gen1;                         //
    gen1.AXIS_SELECT = 7;                       //
    gen1.COMB_SEL = 0;                          // 
    gen1.CRITERION_SEL= 1;                      // 
    gen1.DATA_SRC=1;                            //
    gen1.GEN1_ACT_HYST =0;                      //
    gen1.GEN1_REF_UPDATE=0;                     //
    gen1.GEN_INT1_DUR =7;                       // 
    gen1.GEN_INT1_TRESH=50;                     // 
    gen1.INT1_REF_X=0;                          // 
    gen1.INT1_REF_Y=0;                          //
    gen1.INT1_REF_Z=500;                        //
    set_interrupt(gen1_int_en,1);               //
    mapinterrupt1(gen1_int,1);                  // 
    conf_genint1(&gen1);                        //
}

void enableInterrupt2(){
    Param_genint2 gen2;                         //
    gen2.AXIS_SELECT = 7;                       //
    gen2.COMB_SEL = 0;                          //
    gen2.CRITERION_SEL= 1;                      // 
    gen2.DATA_SRC=1;                            //
    gen2.GEN2_ACT_HYST =0;                      //
    gen2.GEN2_REF_UPDATE=0;                     //
    gen2.GEN_INT2_DUR =7;                       //
    gen2.GEN_INT2_TRESH=50;                     //
    gen2.INT2_REF_X=0;                          //
    gen2.INT2_REF_Y=0;                          //
    gen2.INT2_REF_Z=500;                        //
    set_interrupt(gen2_int_en,1);               //
    mapinterrupt1(gen2_int,1);                  //
    conf_genint2(&gen2);                        //
}

void tapConfig(){
    set_G_range(16);
    filt1_BW(1);
    set_interrupt(stap_int_en,1);
    set_interrupt(dtap_int_en,1);
    mapinterrupt12(tap_int2,1);
    config_tap(0,0,1,1,2);
    sleep_ms(200);
}

void stepConfig(){
    set_interrupt(step_int_en,1);
    clearstepcount();
    sleep_ms(200);
}

void BMA_CONFIGURE(config_t conf)
{
    switch(conf){
        case(CHANGE_ORIENT):
            changeOrient();
        break;

        case(INT1):
            enableInterrupt1();
        break;
    
        case(INT2):
            enableInterrupt2();
        break;

        case(TAP_CONFIG):
            tapConfig();
        break;

        case(STEP_CONFIG):
            stepConfig();
        break;

        default:
        break;
    }
}

void BMA_Reading()
{
    readACC(&data); 
    #ifdef DEBUG
    printf("x=%d,y=%d,z=%d\n",data.X,data.Y,data.Z);
    #endif
}

void BMA_stepcount()
{   
    readACC(&data); 
    #ifdef DEBUG
    printf("x=%d,y=%d,z=%d\n",data.X,data.Y,data.Z);
    #endif
    uint32_t step=stepcount();
    #ifdef DEBUG
    printf("\n\nstep%d\n\n",step);
    #endif
    stepstate();
}

void BMA_tap()
{
    check_tap();
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

void VEML6040_INITALIZE()
{
    VEML6040_init(_instance); 
    configure(0,0,0,0);
}

void VEML6040_Reading()
{   
    Read_colour(&light);
    #ifdef DEBUG
    printf("Red: %d , Green: %d , Blue : %d\n",light.Red,light.Green,light.Blue);
    printf("White :%d\n",light.White);
    printf("Ambient Light : %d \n",get_ambient_light());
    #endif
}

void VEML6030_INITALIZE()
{
    VEML6030_init(_instance);
    power_on();
    VEML6030_config(GAIN_1,ALS_100,ALS_PER_1,ALS_INT_ENABLE,ALS_POWER_ON);
    set_white_High_tresh(10000);
    set_white_Low_tresh(60);
}

void VEML6030_reading()
{  
    ambient = Get_ambient();
    whiteLevel = Get_white();
    #ifdef DEBUG
    printf("Ambient light level : %d \n",ambient);
    printf("White light level : %d \n\n\n",whiteLevel);
    #endif
}

int main(){
    stdio_init_all();
    initalize_i2c(i2c1,SDA_PIN,SCL_PIN);
    BMA_INITIALIZE();
    BMA_CONFIGURE(CHANGE_ORIENT);
    SHT4X_INITIALIZE();
    VEML6040_INITALIZE();
    VEML6030_INITALIZE();
    
 while(1){
    BMA_Reading();
    SHT4X_Reading();
    VEML6040_Reading();
    VEML6030_reading();   
    sleep_ms(1000);
  }
}