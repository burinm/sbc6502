/* loader

    This program takes a program image and loads it
    into a FRAM device. Format is:

    byte 0: image size - LSB
    byte 1: image size - MSB
    byte 2: start address - LSB
    byte 3: stop address - MSB
    byte 4 .. n : image data
        ...
    byte n+1 : checksum (add bytes 0-n in 8bit number) 
*/
        
#include "spi.h"
#include "util.h"
#include <string.h>
#include "fm25640b.h"

//Beagle Bone or Linux only
// This program is for loading FRAM,
//  and testing a bit banged SPI interface

int main(int argc, char* argv[]) {

#if 0
    uint8_t *message="This is a test...";
    fm25640b_open();
    fm25640b_write_mem(0x000,(uint8_t*)message, strlen(message));
    fm25640b_close();
    for(;;);
#endif
 
if (argc == 2) {
    if (strcmp(argv[1],"b") == 0) {
    printf("Erasing\n");
    fm25640b_open();
    fm25640b_write_block(0,0,FM2560B_SIZE);
    fm25640b_close();
    printf("done.\n");
    return 0;
    }

}


if (argc == 2) {
    if (strcmp(argv[1],"r") == 0) {

        printf("read FRAM\n");

        uint8_t buffer[16];
        fm25640b_open();
        uint16_t i;
        uint8_t j;
        for (i=0x000;i<FM2560B_SIZE;i+=16) {
            printf("%04x: ",i);
            for (j=0;j<16;j++) {
                buffer[j] = fm25640b_read_byte(i+j);
            }
            for (j=0;j<16;j++) {
               printf("%02x ",buffer[j]); 
            }
            for (j=0;j<16;j++) {
                if (buffer[j] >= ' ' && buffer[j] <= '~') {
                    printf("%c",buffer[j]); 
                } else {
                    printf(".");
                }
            }
            printf("\n");
        }
    printf("\n");
    fm25640b_close();
    return 0;
    }
}

if (argc == 2) {
    if (strcmp(argv[1],"t") == 0) {
        uint16_t errors=0;

        printf("Write test\n");
        fm25640b_open();

        uint8_t b;
        uint16_t i;
        uint8_t j;
        for (i=0x000;i<FM2560B_SIZE;i+=16) {
            for (j=0;j<16;j++) {
                fm25640b_write_byte(i+j,j+FM2560B_TEST_FILL);
                b = fm25640b_read_byte(i+j);
                if (b != j + FM2560B_TEST_FILL) {
                    printf("x");
                    errors++;
                } else {
                    printf(".");
                }
            }
        }
        printf("\n");
        printf("%u errors found\n",errors);
        fm25640b_close();
    }
}

if (argc !=3) {
    printf("Usage: loader (t test r read)\n");
    printf("     : loader <image> <start address>\n");
    exit(0);
}



#if 0
uint8_t i;
uint8_t b;
uint8_t status0;
uint8_t status1;

fm25640b_open();

status0 = fm25640b_get_status();



for (i=0;i<strlen(message);i++) {
b = fm25640b_read_byte(i);
printf("%c",(char)b);
    


}
printf("\n");

#endif
        


for(;;);
}
