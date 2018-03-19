/* blink_stack.c - (c) 2016 - burin

    LEDs look like stacking blocks

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "sbc.h"
#include "device/6522.h"

uint8_t ram_location;
int main (void)
{
uint16_t ll;
uint16_t j;
uint8_t s;
uint8_t b;
uint8_t d;
uint8_t fill;

for(s=0;s<8;s++) {
    DEVICE_6522_SET_DDA_OUT(VIA_0,s);
}

s=0;
d=0;
b=0;
ll=0;

    while(1) {
        fill=0;


        for (d=0;d<8;d++) {
            for (s=8;s>d;s--) {
                b = 1<<(s-1) | fill; 
                DEVICE_6522_WRITE_A(VIA_0, b);
                for (ll=0;ll<2000;ll++);
            }
            fill |=b;
        }
    }
return EXIT_SUCCESS;
}

