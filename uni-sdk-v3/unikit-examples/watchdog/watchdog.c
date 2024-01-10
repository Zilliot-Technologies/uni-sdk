#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/watchdog.h"

#define WATCHDOG_TIME 5000   //max 8.3 sec

int main() {
    stdio_init_all();

    if (watchdog_caused_reboot()) {
        printf("Rebooted by Watchdog!\n");
        return 0;
    } else {
        printf("Clean boot\n");
    }

    // Enable the watchdog, requiring the watchdog to be updated every WATCHDOG_TIME ms or the chip will reboot
    // second arg is pause on debug which means the watchdog will pause when stepping through code
    watchdog_enable(WATCHDOG_TIME, 1); //100

    for (uint i = 0; i < 10; i++) {
        printf("Updating watchdog %d\n", i);
        watchdog_update();
    }
    printf("watchdog count %d\n",watchdog_get_count());

    // Wait in an infinite loop and don't update the watchdog so it reboots us
    printf("Waiting to be rebooted by watchdog\n");
    while(1){
    }
}