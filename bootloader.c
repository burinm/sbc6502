#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "6522.h"
#include "fm25640b.h"

#include "sbc_spi.h"
#include "sbc_spi.c" //debug only

#define SBC_CODE_TOP     0x1fff

#define HEADER_SIZE_OFFSET    0
#define HEADER_START_OFFSET   2
#define DATA_OFFSET    4 

uint8_t ram_location;
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
image_size+=DATA_OFFSET;

for (ii=0;ii<image_size;ii++) {
    b = fm25640b_read_byte(ii);
    DEVICE_6522_WRITE_A(VIA_0,b);
    //*(uint8_t*)ii = b;
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
while(1) {
    DEVICE_6522_WRITE_A(VIA_0, 0x1);
    for(ii=0;ii<20000;ii++);
    DEVICE_6522_WRITE_A(VIA_0, 0x2);
    for(ii=0;ii<20000;ii++);
    DEVICE_6522_WRITE_A(VIA_0, 0x4);
    for(ii=0;ii<20000;ii++);
    DEVICE_6522_WRITE_A(VIA_0, 0x8);
    for(ii=0;ii<20000;ii++);
    DEVICE_6522_WRITE_A(VIA_0, 0x10);
    for(ii=0;ii<20000;ii++);
    DEVICE_6522_WRITE_A(VIA_0, 0x20);
    for(ii=0;ii<20000;ii++);
    DEVICE_6522_WRITE_A(VIA_0, 0x40);
    for(ii=0;ii<20000;ii++);
    DEVICE_6522_WRITE_A(VIA_0, 0x80);
    for(ii=0;ii<20000;ii++);
}


while(1);



    return EXIT_SUCCESS;
}

