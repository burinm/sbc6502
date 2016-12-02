#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "sbc.h"
#include "6522.h"



uint8_t ram_location;
int main (void)
{
uint16_t ll;
uint8_t s;
uint8_t b;
uint8_t d;

for(s=0;s<8;s++) {
    DEVICE_6522_SET_DDA_OUT(VIA_0,s);
}


s=0;
d=0;
b=0;

while(1) {
    DEVICE_6522_WRITE_A(VIA_0, 1<<b);
    if (s <= 6) {
        if ( d==0) {
            b++;
        } else {
            b--;
        }
    }
    s++;
    if (s == 10) {
        d=!d;
        s=0;
    }
for (ll=0;ll<1500;ll++);
}


    return EXIT_SUCCESS;
}

