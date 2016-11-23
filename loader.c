#include "spi.h"
#include "util.h"
#include <string.h>
#include "fm25640b.h"

//Beagle Bone or Linux only
// This program is for loading FRAM,
//  and testing a bit banged SPI interface

int main() {
uint8_t status0;
uint8_t status1;
uint8_t i;
uint8_t b;

uint8_t message[]="Hello FRAM?";

printf("message has %d bytes\n", strlen(message));

fm25640b_open();

status0 = fm25640b_get_status();

fm25640b_set_write_enable();
fm25640b_write_block(0x000,(uint8_t*)message, strlen(message));
fm25640b_set_write_disable();

status1 = fm25640b_get_status();

printf ("0x%x 0x%x\n",status0,status1);

for (i=0;i<strlen(message);i++) {
b = fm25640b_read_byte(i);
printf("%c",(char)b);
    


}
printf("\n");

        


for(;;);
}
