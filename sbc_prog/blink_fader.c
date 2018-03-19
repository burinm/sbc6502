/* blink_fader.c - (c) 2016 - burin

    Demo program that fades in and out
    LEDs on SBC VIA0
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

for(s=0;s<8;s++) {
    DEVICE_6522_SET_DDA_OUT(VIA_0,s);
}

s=0;
d=0;
b=0;
ll=0;

    //Variable pulse width modulation of LEDs
    while(1) {
        for (j=0;j<100;j++) {
            for (ll=0;ll<100;ll++) {
                if (ll == 0) {
                    DEVICE_6522_WRITE_A(VIA_0, 0xff);
                }
                if (ll == s) {
                    DEVICE_6522_WRITE_A(VIA_0, 0x0);
                }
            }
            if (d==0) {
                s++;
            } else {
                s--;
            }
        }
        d=!d;
    }

return EXIT_SUCCESS;
}

