#include "retroClick.h"

#define I2C_SPEED 100 * 1000
#define I2C_PORT i2c1
#define I2C_SCL 23
#define I2C_SDA 22
#define INT_PIN 24
#define I2C_ADDRESS 0x00

c8800retro_cfg_t c8800retro_cfg;
struct repeating_timer timer;
int cnt = 0;
uint8_t demo_string[ 10 ] = { ' ', 'U', 'N', 'I', '-', 'K', 'I', 'T', ' ', 0 };

bool repeating_timer_callback(struct repeating_timer *t) {
    if(cnt > 255){
        cnt = 0;
    }
    else{
        cnt++;
    }
    return true;
}

int main()
{
    c8800retro_cfg.i2c_address = I2C_ADDRESS;
    c8800retro_cfg.i2c_speed = I2C_SPEED;
    c8800retro_cfg.inst = I2C_PORT;
    c8800retro_cfg.int_pin = INT_PIN;
    c8800retro_cfg.scl = I2C_SCL;
    c8800retro_cfg.sda = I2C_SDA;

    initDisplay(&c8800retro_cfg);
    clear_display(&c8800retro_cfg);
    // add_repeating_timer_ms(2000, repeating_timer_callback, NULL, &timer);
    while(1)
    {   
        // display_char(&c8800retro_cfg,cnt);
        display_string(&c8800retro_cfg,C8800RETRO_SCROLL_HORIZONTAL_LEFT,C8800RETRO_SCROLL_SPEED_MEDIUM,demo_string);

        // tight_loop_contents();
        }
  }
