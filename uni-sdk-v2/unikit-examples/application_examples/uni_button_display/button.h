#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define PCA9554B_ADDR 0x20
#define ALL_PORT 0xFF

typedef struct
{
 bool SW0 ;   
 bool SW1 ;
 bool SW2 ;
 bool SW3 ;
 bool SW4 ;
 bool SW5 ;
 bool SW6 ;
 bool SW7 ;
}input_state;

typedef struct
{
  bool SW0 ;   
 bool SW1 ;
 bool SW2 ;
 bool SW3 ;
 bool SW4 ;
 bool SW5 ;
 bool SW6 ;
 bool SW7 ;
}inversion_state;

void PCA9554B_INIT(i2c_inst_t *INSTANCE,uint8_t sdaPin,uint8_t sclPin);
void Read_Port(input_state *this);
void set_output(uint8_t port,bool state);
void readpolarity(inversion_state *this);
void set_port_dir(uint8_t port,bool state);
void set_inversion(uint8_t port,bool state);
void enableInterrupt(uint8_t enablePin );