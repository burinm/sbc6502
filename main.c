#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "6522.h"

#define VIA_0 (uint8_t*)(0x8010)

uint8_t ram_location;
int main (void)
{
//device_6522_init(VIA_0);
    DEVICE_6522_SET_DDA_OUT(VIA_0, 7);
    DEVICE_6522_SET_DDA_OUT(VIA_0, 6);
    DEVICE_6522_SET_DDA_OUT(VIA_0, 5);
    DEVICE_6522_WRITE_A(VIA_0, 0xff);




    while(1);
    return EXIT_SUCCESS;
}

