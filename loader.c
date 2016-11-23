#include "spi.h"
#include "util.h"
#include "fm25640b.h"

//Beagle Bone or Linux only
// This program is for loading FRAM,
//  and testing a bit banged SPI interface

int main() {
uint8_t status0;
uint8_t status1;


fm25640b_open();

fm25640b_set_write_enable();
status0 = fm25640b_get_status();
fm25640b_set_write_disable();
status1 = fm25640b_get_status();

printf ("0x%x 0x%x\n",status0,status1);


        


for(;;);
}
