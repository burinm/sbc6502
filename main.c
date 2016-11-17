#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

extern const char text[];       /* In text.s */

int main (void)
{
//    printf ("%s\n", text);
    *(uint8_t *)(0xc000)=0xab;
    while(1);
    return EXIT_SUCCESS;
}

