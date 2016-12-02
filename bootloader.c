/* sbc bootloader

    This is the main routine that loads FRAM into
     the main RAM at startup. The FRAM binary should
     be in the following format:

    byte0 [image size low] byte1 [image size high] 
    byte2 [start addr low] byte1 [start addr high] 
    byte4 [............]
    byten+1 [checksum]

    The [start] address
     is 16 bit jump address to the _init call in the binary
    The [checksum] is a running 8bit total of
     bytes 0->n


    The binary, from byte 2->n is loaded into memory
    at the [start] address. (This includes writing
    the start vector as the first two bytes of the
    image)

    Failures are indicated on the main LED array:

    bit7[oooooooo]bit0

    0) - no FRAM inserted, system stops in loop
        leds will flash fast [ooooxxxx]<->[xxxxoooo]

    1) - Checksum error, system stops in loop
        leds will [calulated]<->[checksum from file] 

    3) - Success, system will boot to vector in RAM
        leds will flash [oooooooo] once
        then start addr    [start addr low] -> [start addr high]
        leds will flash [oooooooo] once
        then vector addr   [vector addr low] -> [vector addr high]
        leds will flash [oooooooo] once
        (start address should match vector address)

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "6522.h"
#include "fm25640b.h"
#include "sbc.h"

#include "sbc_spi.h"
#include "sbc_spi.c" //debug only

#define SBC_CODE_TOP     0x1fff


void (*start_vector)();
int main (void)
{
uint8_t checksum;
uint8_t image_size_lo;
uint8_t image_size_hi;
uint16_t image_size;
uint8_t start_addr_lo;
uint8_t start_addr_hi;
uint8_t i;
uint8_t b;
uint16_t ii;

for(i=0;i<8;i++) {
    DEVICE_6522_SET_DDA_OUT(VIA_0,i);
}
DEVICE_6522_WRITE_A(VIA_0, 0xff);

DEBUG_PORT_ON;
DEBUG_PB2_ON; //Time loading

fm25640b_open();

image_size=0;

image_size_lo = fm25640b_read_byte(HEADER_SIZE_OFFSET);
image_size_hi = fm25640b_read_byte(HEADER_SIZE_OFFSET+1);
start_addr_lo = fm25640b_read_byte(HEADER_START_OFFSET);
start_addr_hi = fm25640b_read_byte(HEADER_START_OFFSET+1);

if (image_size_lo == 0x0 && image_size_hi == 0x0 && start_addr_lo == 0x0 && start_addr_hi == 0x0) {
    //If FRAM isn't plugged in, system will read all 0x0
    fm25640b_close();
    while(1) {
    DEVICE_6522_WRITE_A(VIA_0, 0xf0);
    for(ii=0;ii<5000;ii++);
    DEVICE_6522_WRITE_A(VIA_0, 0x0f);
    for(ii=0;ii<5000;ii++);
    }
}

image_size = image_size_hi << 8;
image_size |= image_size_lo;

checksum=0;
checksum += image_size_lo;
checksum += image_size_hi;

image_size+=DATA_OFFSET;
for (ii=DATA_OFFSET;ii<image_size;ii++) {
    b = fm25640b_read_byte(ii);
    *((SBC_CODE_START - DATA_OFFSET) + ii) = b;
    DEVICE_6522_WRITE_A(VIA_0,b);
    checksum += b;
}


b = fm25640b_read_byte(ii);
fm25640b_close();

DEBUG_PB2_OFF; //Time loading

if (checksum != b) {
    //did't succeed flash...
    while(1) {
    DEVICE_6522_WRITE_A(VIA_0, checksum);
    for(ii=0;ii<10000;ii++);
    DEVICE_6522_WRITE_A(VIA_0, b);
    for(ii=0;ii<10000;ii++);
    }
}


//success
DEVICE_6522_WRITE_A(VIA_0, 0xff);
for(ii=0;ii<20000;ii++);

// Flash load address read from FRAM
DEVICE_6522_WRITE_A(VIA_0, start_addr_lo);
for(ii=0;ii<20000;ii++);
DEVICE_6522_WRITE_A(VIA_0, start_addr_hi);
for(ii=0;ii<20000;ii++);
DEVICE_6522_WRITE_A(VIA_0, 0xff);
for(ii=0;ii<40000;ii++);

// Flash load address stored in RAM as check
DEVICE_6522_WRITE_A(VIA_0, *(SBC_CODE_START));
for(ii=0;ii<20000;ii++);
DEVICE_6522_WRITE_A(VIA_0, *(SBC_CODE_START+1));
for(ii=0;ii<20000;ii++);
DEVICE_6522_WRITE_A(VIA_0, 0xff);
for(ii=0;ii<40000;ii++);

// Load the address stored in 0x200 into the function pointer
start_vector = (void (*)())(*(uint16_t*)0x0200);
start_vector();
//__asm__ ("jmp (%w)",0x200); //This, gets optimized out :(
while(1);

return EXIT_SUCCESS;
}

