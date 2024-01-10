#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "BMA400.h"
#include "SHT4X.h"
#include "VEML6030.h"
#include "VEML6040.h"
#include "Credential.h"

#define ENABLE_UART

bool ackFlag = false;
bool sendCredFlag = false;
bool sendSenseVarFlag = false;
bool sendSensorDataFlag = false;

char *sensorVarName = "{temp,humid,ambient,redLevel,greenLevel,blueLevel,xValue,yValue,zValue}";
i2c_inst_t *_instance;
uint8_t _SDA;
uint8_t _SCL;

char sensorData[256];
char credData[256];

sht4x_data sensordata; // sht40 sensor reading
ACC data; ;      // BMA xyz reading
color_t light;   // VEML6040 reading
uint16_t ambient,whiteLevel;  // VEML6030 reading

#define DEBUG   // used to enable debug prints
#define ENABLE_UART    // used to enable uart 

// uart configuration
#define UART_INS uart1
#define BAUD 115200
#define UART_TX 20  
#define UART_RX 21  
#define MAX_BUFFER_SIZE 10
char buffer[MAX_BUFFER_SIZE];
size_t buffer_index = 0;

#define SDA_PIN 22
#define SCL_PIN 23

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
 //setautolowpower(0,0,0,1); 
 set_G_range(8);
 //set_interrupt(latch_int_en,1);
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
    Param_genint1 gen1;                         
    gen1.AXIS_SELECT = 7;                       
    gen1.COMB_SEL = 0;                          
    gen1.CRITERION_SEL= 1;                      
    gen1.DATA_SRC=1;                            
    gen1.GEN1_ACT_HYST =0;                      
    gen1.GEN1_REF_UPDATE=0;                     
    gen1.GEN_INT1_DUR =7;                      
    gen1.GEN_INT1_TRESH=50;                      
    gen1.INT1_REF_X=0;                          
    gen1.INT1_REF_Y=0;                          
    gen1.INT1_REF_Z=500;                        
    set_interrupt(gen1_int_en,1);               
    mapinterrupt1(gen1_int,1);                   
    conf_genint1(&gen1);   
}      
               
void enableInterrupt2(){
    Param_genint2 gen2;                         
    gen2.AXIS_SELECT = 7;                       
    gen2.COMB_SEL = 0;                          
    gen2.CRITERION_SEL= 1;                       
    gen2.DATA_SRC=1;                            
    gen2.GEN2_ACT_HYST =0;                      
    gen2.GEN2_REF_UPDATE=0;                     
    gen2.GEN_INT2_DUR =7;                       
    gen2.GEN_INT2_TRESH=50;                     
    gen2.INT2_REF_X=0;                          
    gen2.INT2_REF_Y=0;                          
    gen2.INT2_REF_Z=500;                        
    set_interrupt(gen2_int_en,1);               
    mapinterrupt1(gen2_int,1);                  
    conf_genint2(&gen2);                        
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
    printf("the temperature is %.2f C \n the humidity is %.2f \n ",sensordata.tempratureC,sensordata.humidity);
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
    printf(" red: %d , Green: %d , Blue : %d \n",light.Red,light.Green,light.Blue);
    printf("White :%d\n",light.White);
    printf("Ambient Light : %d \n",get_ambient_light());
    #endif
}

void VEML6030_INITALIZE()
{
    VEML6030_init(_instance);
    power_on();
    VEML6030_config(0,0,0,1,0);
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

void initalize_uart(uart_inst_t *UART_ID,uint BAUD_RATE,uint8_t UART_TX_PIN,uint8_t UART_RX_PIN)
{
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    uart_set_hw_flow(UART_ID, false, false);  // Disable hardware flow control
    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);

}

void processID(uint8_t data){
        switch (data)
        {
        case 0x01:
            sendCredFlag = true;
            break;
        case 0x02:
            sendSenseVarFlag = true;
            break;
        case 0x03:
            sendSensorDataFlag = true;
            break;
        default:
            break;
        }
}

void uart_process(char *data){
    char type[4] = {'\0'};
    int hexValue = 0;
    int hexValueStarted = 0;

    for (int i = 0; data[i] != '\0'; ++i) {
        char currentChar = data[i];
        printf("%c\n",data[i]);
        if (currentChar == 'I' && data[i + 1] == 'D' && data[i + 2] == ':') {
            type[0] = 'I';
            type[1] = 'D';
            hexValueStarted = 1;
            i += 2;  // Skip':I'
        } else if (currentChar == 'A' && data[i + 1] == 'C' && data[i + 2] == 'K' && data[i + 3] == ':') {
            type[0] = 'A';
            type[1] = 'C';
            type[2] = 'K';
            hexValueStarted = 1;
            i += 3;  // Skip ':AC'
        } else if ((currentChar >= '0' && currentChar <= '9') ||
                   (currentChar >= 'a' && currentChar <= 'f') ||
                   (currentChar >= 'A' && currentChar <= 'F')) {    
            if (hexValueStarted) {
                hexValue = hexValue * 16 + ((currentChar >= '0' && currentChar <= '9') ? (currentChar - '0') :
                                            (currentChar >= 'a' && currentChar <= 'f') ? (currentChar - 'a' + 10) :
                                            (currentChar - 'A' + 10));
            } else {
                printf("Invalid character before hex value\n");
                return;
            }
        } else if (currentChar == ':') {
            printf("Invalid message format\n");
            return;
        }
    }

    if ((type[0] == 'I' && type[1] == 'D') || (type[0] == 'A' && type[1] == 'C' && type[2] == 'K')) {
        printf("Processing %s: 0x%02X\n", type, hexValue);
        if(type[0] == 'I' && type[1] == 'D'){
            processID(hexValue);
        }
        else if(type[0] == 'A' && type[1] == 'C' && type[2] == 'K'){
            ackFlag = true;
        }

    } else {
        printf("Invalid message format\n");
    }
}

void uartRead(){
    if (uart_is_readable(UART_INS)) {
         char received_data = uart_getc(UART_INS);
         if (received_data == '\n') {
            buffer[buffer_index] = '\0';  // Null-terminate the received string
            printf("Received: %s\n", buffer);
            uart_process(buffer);
            buffer_index = 0;  // Reset the buffer index for the next line
        } else {
            buffer[buffer_index] = received_data;
            buffer_index++;
            if (buffer_index >= MAX_BUFFER_SIZE) {
                buffer_index = 0;  // Reset the buffer index if it exceeds the maximum size
            }
        }
    }
}

int main()
{
    stdio_init_all();
    initalize_i2c(i2c1,SDA_PIN,SCL_PIN);

    #ifdef ENABLE_UART
    initalize_uart(UART_INS,BAUD,UART_TX,UART_RX);
    #endif

    BMA_INITIALIZE();
    BMA_CONFIGURE(CHANGE_ORIENT);
    SHT4X_INITIALIZE();
    VEML6040_INITALIZE();
    VEML6030_INITALIZE();

  while(1)
  {
    BMA_Reading();
    SHT4X_Reading();
    VEML6040_Reading();
    VEML6030_reading();

    uartRead();
   
   if (sendCredFlag){
    if(ackFlag){
        sendCredFlag = false;
        ackFlag = false;
    }
    snprintf(credData,sizeof(credData),"{ssid:%c,psswd:%c,Token:%c}\n",wifi_ssid,wifi_pswd,ubidots_token);
    uart_puts(UART_INS,credData);
   }

   if(sendSenseVarFlag){
    if(ackFlag){
        sendSenseVarFlag = false;
        ackFlag = false;
    }
    uart_puts(UART_INS,sensorVarName);
   }

   if(sendSensorDataFlag){
        snprintf(sensorData,sizeof(sensorData),"{%.2f,%.2f,%d,%d,%d,%d,%d,%d,%d}\n",sensordata.tempratureC,sensordata.humidity,ambient, light.Red, light.Green, light.Blue, data.X, data.Y, data.Z);
        uart_puts(UART_INS,sensorData);
   }

  }
}
