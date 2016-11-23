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
#include <sys/stat.h>
#include "fm25640b.h"


//Beagle Bone or Linux only
// This program is for loading FRAM,
//  and testing a bit banged SPI interface
void blank_fram();
void read_fram();
void write_test_fram();

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
        blank_fram();
        return 0;
    }
}

if (argc == 2) {
    if (strcmp(argv[1],"r") == 0) {
        read_fram();
        return 0;
    }
}

if (argc == 2) {
    if (strcmp(argv[1],"t") == 0) {
        write_test_fram();
        return 0;
    }
}

if (argc !=3) {
    printf("Usage: loader (t test r read)\n");
    printf("     : loader <image> <start address>\n");
    return 0;
}

FILE *f;
struct stat stat_s;
uint16_t image_size;
uint8_t image_size_hi;
uint8_t image_size_lo;
uint16_t start_addr;
uint8_t start_addr_hi;
uint8_t start_addr_lo;
char* file_name;

file_name=argv[1];

f=fopen(file_name,"r");
if (f == NULL) {
    printf("couldn't open %s for reading.\n",file_name);
    return -1;
}

#define HEADER_SIZE_OFFSET    0
#define HEADER_START_OFFSET   2
#define DATA_OFFSET    4 

stat(file_name,&stat_s);
image_size = stat_s.st_size;
if (image_size > FM2560B_SIZE - DATA_OFFSET) {
    printf("Image [%s] size [0x%x] too large\n",file_name,image_size);
    return 0;
}
image_size_hi=(image_size & 0xff00) >>8;
image_size_lo=image_size & 0x00ff;

start_addr=strtol(argv[2],NULL,16);
start_addr_hi=(start_addr & 0xff00) >>8;
start_addr_lo=start_addr & 0x00ff;

printf("image [%s] size [0x%04x] bytes %u\n",file_name,image_size,image_size);
printf("------header------\n");

uint8_t checksum;
checksum=0;

printf(" size:  [%02x][%02x]\n",image_size_lo,image_size_hi);
    checksum += image_size_lo;
    printf("    (cheksum = %02x)\n",checksum);
    checksum += image_size_hi;
    printf("    (cheksum = %02x)\n",checksum);

printf(" start: [%02x][%02x]\n",start_addr_lo,start_addr_hi);
    checksum += start_addr_lo;
    printf("    (cheksum = %02x)\n",checksum);
    checksum += start_addr_hi;
    printf("    (cheksum = %02x)\n",checksum);

uint16_t i;
uint16_t j;
#define READ_BUFFER_SIZE 256
uint8_t buffer[READ_BUFFER_SIZE];
uint16_t bytes_read;
uint16_t n_read;

    fm25640b_open();

    i=0;
    n_read=DATA_OFFSET;
    do {
        printf("0x%04x ",n_read);
        fread(buffer,READ_BUFFER_SIZE,1,f);
        i+=READ_BUFFER_SIZE;
        if (i > image_size) {
           bytes_read = image_size % READ_BUFFER_SIZE;
        } else {
           bytes_read = READ_BUFFER_SIZE;
        } 
        fm25640b_write_mem(n_read,buffer,bytes_read);
        n_read += bytes_read;
        for (j=0;j<bytes_read;j++) { checksum += buffer[j]; }
        printf("0x%04x (cheksum = %02x) wrote %u bytes\n",n_read-1,checksum,bytes_read);
    } while (i<image_size);


    fm25640b_write_byte(n_read-1,checksum);

    fm25640b_write_byte(HEADER_SIZE_OFFSET,image_size_lo);
    fm25640b_write_byte(HEADER_SIZE_OFFSET+1,image_size_hi);
    fm25640b_write_byte(HEADER_START_OFFSET,start_addr_lo);
    fm25640b_write_byte(HEADER_START_OFFSET+1,start_addr_hi);

    printf("image [0x%04x] %u bytes\n",n_read,n_read);

    fm25640b_close();

fclose(f);

return 0;
}

void blank_fram() {
    printf("Erasing\n");
    fm25640b_open();
    fm25640b_write_block(0,0,FM2560B_SIZE);
    fm25640b_close();
    printf("done.\n");
}

void read_fram() {
    printf("read FRAM\n");
    fm25640b_open();

    uint8_t buffer[16];
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
}

void write_test_fram() {
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

