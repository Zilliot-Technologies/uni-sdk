#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "IS31FL3728.h"

int main()
{
  stdio_init_all();
  init_IS31FL3728(i2c1,22,23);
  set_row_current(IS31FL3728_CURRENT_SETTING_5);
    

    // while(1)
    // {
    // IS31FL3728_displaytext("Tushar12345678");
    // }
  write_led(0xFF);
  update_screen();
  while(1)
  {
  // write_data(4,0xAA);
  // update_screen();
  shutdown(1);
  sleep_ms(50);
  shutdown(0);
  sleep_ms(50);
   }
}