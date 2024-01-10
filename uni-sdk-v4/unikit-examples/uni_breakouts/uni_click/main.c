#include <stdio.h>
#include "pico/stdlib.h"
#include "uni_click.h"

// #define USE_MIKRO_BUS
#define USE_QWIIC

#define I2C_SDA_PIN 22
#define I2C_SCL_PIN 23
#define I2C_INT_PIN 18

#define I2C_INSTANCE i2c1

void gpio_callback(uint gpio, uint32_t events)
{
    input_state buttons;
    Read_Port(&buttons);
     
     if(buttons.SW0)
     printf("button 1\n");
     if(buttons.SW1)
     printf("button 2\n");
     if(buttons.SW2)
     printf("button 3\n");
     if(buttons.SW3)
     printf("button 4\n");
     if(buttons.SW4)
     printf("button 5\n");
     if(buttons.SW5)
     printf("button 6\n");
     if(buttons.SW6)
     printf("button 7\n");
     if(buttons.SW7)
     printf("button 8\n");
 
 return;
}

int main()
{
    stdio_init_all();
    i2c_init(I2C_INSTANCE, 100 * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);

    PCA9554B_INIT(I2C_INSTANCE);
    
    #ifdef USE_MIKRO_BUS
        gpio_init(I2C_INT_PIN);
        gpio_set_dir(I2C_INT_PIN,0);
        gpio_pull_up(I2C_INT_PIN);
    #endif

    set_inversion(ALL_PORT,0);
    input_state buttons;
    
    #ifdef USE_MIKRO_BUS
    gpio_set_irq_enabled_with_callback(I2C_INT_PIN,GPIO_IRQ_EDGE_RISE,1,gpio_callback);
    #endif
    
   while(1)
   {
   
   Read_Port(&buttons);

   #ifdef USE_QWIIC
   printf(" button 1 %d \n",buttons.SW0);
   printf(" button 2 %d \n",buttons.SW1);
   printf(" button 3 %d \n",buttons.SW2);
   printf(" button 4 %d \n",buttons.SW3);
   printf(" button 5 %d \n",buttons.SW4);
   printf(" button 6 %d \n",buttons.SW5);
   printf(" button 7 %d \n",buttons.SW6);
   printf(" button 8 %d \n",buttons.SW7);
   printf("\n\n");
   sleep_ms(500);
   #endif

}
}