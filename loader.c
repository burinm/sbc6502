#include "spi.h"
#include "util.h"

//Beagle Bone or Linux only
// This program is for loading FRAM,
//  and testing a bit banged SPI interface

int main() {

//Move to FRAM driver...
 spi_set_mode(SPI_MODE_0);
    spi_set_bitorder(SPI_MSBit);
    spi_open_device();


for(;;) {
    spi_readwrite_byte('U');
}

        


for(;;);
}
