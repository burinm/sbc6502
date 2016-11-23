#include "spi.h"
#include "util.h"
#include "fm25640b.h"

//Beagle Bone or Linux only
// This program is for loading FRAM,
//  and testing a bit banged SPI interface

int main() {


fm25640b_open();

fm25640b_get_status();

    spi_readwrite_byte('U');

        


for(;;);
}
