#include "circbuf_tiny.h"
#include <stdio.h>

int main() {

uint8_t b;
uint16_t i;

circbuf_tiny_t c;
circbuf_tiny_init(&c);
for (i=1;i<50;i++) {
    circbuf_tiny_write(&c,i);
    printf("write-->%d\n",i);
}

for (i=1;i<10;i++) {
    circbuf_tiny_read(&c,&b);
    printf("read-->%d\n",b);
}

for (i=88;i<99;i++) {
    circbuf_tiny_write(&c,i);
    printf("write-->%d\n",i);
}

for (i=0;i<51;i++) {
    circbuf_tiny_read(&c,&b);
    printf("read-->%d\n",b);
}

circbuf_tiny_destroy(&c);

circbuf_tiny_init(&c);
circbuf_tiny_destroy(&c);





}
