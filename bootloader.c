#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "6522.h"
#include "fm25640b.h"

#include "sbc_spi.h"
#include "sbc_spi.c" //debug only


uint8_t ram_location;
int main (void)
{
uint8_t i;

fm25640b_open();

    
for(i=0;i<8;i++) {
//    DEVICE_6522_SET_DDB_IN(VIA_0,i);
    DEVICE_6522_SET_DDA_OUT(VIA_0,i);
}

//spi_open_device();



//fm25640b_write_byte(0x77,0x22);
fm25640b_write_byte(0x77,0x44);
fm25640b_read_byte(0x77);
/*
 spi_clk_low();
 spi_clk_high();


spi_ss_low();
spi_ss_high();

spi_mosi_low();
spi_mosi_high();
*/

DEVICE_6522_WRITE_A(VIA_0, DEVICE_6522_READ_B(VIA_0));

while(1);



    return EXIT_SUCCESS;
}

