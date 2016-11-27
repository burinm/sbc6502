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
uint16_t start_addr;
uint8_t i;
uint8_t b;
uint16_t ii;

for(i=0;i<8;i++) {
    DEVICE_6522_SET_DDA_OUT(VIA_0,i);
}
DEVICE_6522_WRITE_A(VIA_0, 0xff);

fm25640b_open();

image_size=0;
start_addr=0;

image_size_lo = fm25640b_read_byte(HEADER_SIZE_OFFSET);
image_size_hi = fm25640b_read_byte(HEADER_SIZE_OFFSET+1);
start_addr_lo = fm25640b_read_byte(HEADER_START_OFFSET);
start_addr_hi = fm25640b_read_byte(HEADER_START_OFFSET+1);

image_size = image_size_hi << 8;
image_size |= image_size_lo;

start_addr = start_addr_hi << 8;
start_addr |= start_addr_lo;

if (start_addr > SBC_CODE_TOP) {
    //sanity check
}

if (image_size > SBC_CODE_TOP) {
    //sanity check
}


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


//start_vector=(void(*)())(start_addr);
//start_vector();
__asm__ ("jmp (%w)",0x200);
while(1);



    return EXIT_SUCCESS;
}

