#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


uint8_t ram_location;
int main (void)
{
    while(1) {
        // Test low ROM write
        *(uint8_t *)(0xc000)=0xab;
        // Test low I/O write
        *(uint8_t *)(0x8000)=0xcd;
        // Test RAM write
        ram_location=0xef;
    }
    return EXIT_SUCCESS;
}

