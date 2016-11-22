#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "6522.h"

#define VIA_0 (uint8_t*)(0x8010)

uint8_t ram_location;
int main (void)
{
uint16_t i;
uint16_t j;
//device_6522_init(VIA_0);

        
    DEVICE_6522_SET_DDA_OUT(VIA_0, 0);
    DEVICE_6522_SET_DDA_OUT(VIA_0, 1);
    DEVICE_6522_SET_DDA_OUT(VIA_0, 2);
    DEVICE_6522_SET_DDA_OUT(VIA_0, 3);
    DEVICE_6522_SET_DDA_OUT(VIA_0, 4);
    DEVICE_6522_SET_DDA_OUT(VIA_0, 5);
    DEVICE_6522_SET_DDA_OUT(VIA_0, 6);
    DEVICE_6522_SET_DDA_OUT(VIA_0, 7);
while(1) {
    DEVICE_6522_WRITE_A(VIA_0, 0x1);
    for(i=0;i<20000;i++);
    DEVICE_6522_WRITE_A(VIA_0, 0x2);
    for(i=0;i<20000;i++);
    DEVICE_6522_WRITE_A(VIA_0, 0x4);
    for(i=0;i<20000;i++);
    DEVICE_6522_WRITE_A(VIA_0, 0x8);
    for(i=0;i<20000;i++);
    DEVICE_6522_WRITE_A(VIA_0, 0x10);
    for(i=0;i<20000;i++);
    DEVICE_6522_WRITE_A(VIA_0, 0x20);
    for(i=0;i<20000;i++);
    DEVICE_6522_WRITE_A(VIA_0, 0x40);
    for(i=0;i<20000;i++);
    DEVICE_6522_WRITE_A(VIA_0, 0x80);
    for(i=0;i<20000;i++);
}





    return EXIT_SUCCESS;
}

