// Use the DMA to copy data between two buffers in memory.

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/dma.h"

// #define TRANSFER_INT
#define TRANSFER_STRING

// Data will be copied from src to dst
#ifdef TRANSFER_STRING
const char src[] = "string transfered from DMA!";
char dst[count_of(src)];
#endif

// Data will be copied from srcData to dstData
#ifdef TRANSFER_INT
uint8_t srcData[] = {10,20,30};
uint8_t dstData[count_of(srcData)];
#endif

int main() {
    stdio_init_all();

    // Get a free channel, panic() if there are none
    int chan = dma_claim_unused_channel(true);

    // 8 bit transfers. Both read and write address increment after each
    // transfer (each pointing to a location in src or dst respectively).
    // No DREQ is selected, so the DMA transfers as fast as it can.

    dma_channel_config c = dma_channel_get_default_config(chan);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
    channel_config_set_read_increment(&c, true);
    channel_config_set_write_increment(&c, true);

#ifdef TRANSFER_INT
    dma_channel_configure(
        chan,          // Channel to be configured
        &c,            // The configuration we just created
        dstData,           // The initial write address
        srcData,           // The initial read address
        count_of(srcData), // Number of transfers; in this case each is 1 byte.
        true           // Start immediately.
    );
#endif

#ifdef TRANSFER_STRING
    dma_channel_configure(
        chan,          // Channel to be configured
        &c,            // The configuration we just created
        dst,           // The initial write address
        src,           // The initial read address
        count_of(src), // Number of transfers; in this case each is 1 byte.
        true           // Start immediately.
    );
#endif

    // We could choose to go and do something else whilst the DMA is doing its
    // thing. In this case the processor has nothing else to do, so we just
    // wait for the DMA to finish.
    dma_channel_wait_for_finish_blocking(chan);

    // The DMA has now copied our text from the transmit buffer (src) to the
    // receive buffer (dst), so we can print it out from there.
    #ifdef TRANSFER_STRING
    puts(dst);
    #endif

    #ifdef TRANSFER_INT
    for(uint8_t i = 0;i < count_of(srcData);i++){
    printf("%d\t",dstData[i]);
    }
    #endif
    while(1){
        tight_loop_contents();
    }
}
