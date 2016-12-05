/* loader

    This program takes a program image and loads it
    into a FRAM device. Format is:

Image size is added to the beginning:
    byte 0: image size - LSB
    byte 1: image size - MSB

This part is already in the image
    byte 2: start address - LSB
    byte 3: start address - MSB
    byte 4 .. n : image data
        ...

Checksum is added at the end:
    byte n+1 : checksum (adds up bytes 0-n, in 8bit number) 
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
void checksum_check();

int main(int argc, char* argv[]) {
uint8_t c;

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
    if (strcmp(argv[1],"c") == 0) {
        checksum_check();
        return 0;
    }
}

if (argc == 2) {
    if (strcmp(argv[1],"t") == 0) {
        printf("This is a destructive test.\n");
        printf("Continue? (y/n)\n");
        c =getchar();
        if (c != 'y') { printf("aborted\n"); return 0; }
        
        write_test_fram();
        return 0;
    }
}

if (argc !=2) {
    printf("Usage: loader (r read b blank t test c checksum)\n");
    printf("     : loader <image>\n");
    return 0;
}

FILE *f;
struct stat stat_s;
uint16_t image_size;
uint8_t image_size_hi;
uint8_t image_size_lo;
char* file_name;

//Open image file
file_name=argv[1];
f=fopen(file_name,"r");
if (f == NULL) {
    printf("couldn't open %s for reading.\n",file_name);
    return -1;
}

//Define header for image.
// TODO: This should really go into the 
// development tools for a specific platform.
// That way this can be a generic burner
#define HEADER_SIZE_OFFSET    0
#define HEADER_START_OFFSET   2
#define DATA_OFFSET    2 
#define CHECKSUM_SIZE  1

//Is the image gonna fit?
stat(file_name,&stat_s);
image_size = stat_s.st_size;
if (image_size > FM2560B_SIZE - DATA_OFFSET - CHECKSUM_SIZE) {
    printf("Image [%s] size [0x%x] too large\n",file_name,image_size);
    return 0;
}

if (image_size == 0) {
    printf("Image is empty!\n");
    return 0;
}

//O.k, grab the size and break it into little
// endian bytes
image_size_hi=(image_size & 0xff00) >>8;
image_size_lo=image_size & 0x00ff;


printf("image [%s] size [0x%04x] bytes %u\n",file_name,image_size,image_size);
printf("------header------\n");

//Start the checksum calculation.
// simple add-up-all-the-bytes-let-overflow algorithm
uint8_t checksum;
uint8_t checksum_save;
checksum=0;

printf(" size:  [%02x][%02x]\n",image_size_lo,image_size_hi);
    checksum += image_size_lo;
    printf("    (cheksum = %02x)\n",checksum);
    checksum += image_size_hi;
    printf("    (cheksum = %02x)\n",checksum);

uint16_t i;
uint16_t j;
#define READ_BUFFER_SIZE 256
uint8_t buffer[READ_BUFFER_SIZE];
uint16_t bytes_read;
uint16_t n_read;

    //Now we are serious, going to open the FRAM device
    fm25640b_open();

    i=0;
    n_read=DATA_OFFSET;
    do {
        //Read in chunks. We could have also done this in
        // one shot (easier code), but then we need a 8K
        // chunk of memory...
        printf("0x%04x ",n_read);
        fread(buffer,READ_BUFFER_SIZE,1,f);
        i+=READ_BUFFER_SIZE;
        if (i > image_size) {
           //Last chunk if the image file wasn't an even
           //  multiple ofREAD_BUFFER_SIZE
           bytes_read = (image_size % READ_BUFFER_SIZE);
        } else {
           bytes_read = READ_BUFFER_SIZE;
        } 
        //Actually write buffer to FRAM
        fm25640b_write_mem(n_read,buffer,bytes_read);
        n_read += bytes_read;
        //Checksum up the chunk 
        for (j=0;j<bytes_read;j++) {
            checksum += buffer[j];
//printf("checksum  +%x = %x\n", buffer[j], checksum);
        }
        printf("0x%04x (cheksum = %02x) wrote %u bytes\n",n_read-1,checksum,bytes_read);
    } while (i<image_size);


    //Write checksum
    fm25640b_write_byte(n_read,checksum);
    checksum_save=checksum;

    //Write header last.
    fm25640b_write_byte(HEADER_SIZE_OFFSET,image_size_lo);
    fm25640b_write_byte(HEADER_SIZE_OFFSET+1,image_size_hi);

    printf("image [0x%04x] %u bytes\n",n_read,n_read);

    fm25640b_close();

    //Now verify the fram
    fm25640b_open();
    image_size_lo = fm25640b_read_byte(HEADER_SIZE_OFFSET);
    image_size_hi = fm25640b_read_byte(HEADER_SIZE_OFFSET+1);

    n_read=0;
    n_read=image_size_hi << 8;
    n_read+=image_size_lo;

    n_read+=DATA_OFFSET;

//printf("n_read %d\n",n_read);
    checksum=0;
uint8_t tmp_check;
    for (i=0;i<n_read;i++) {
            tmp_check=fm25640b_read_byte(i);
            checksum += tmp_check; 
//printf("checksum +%x = %x\n",tmp_check,checksum);
    }

    printf("Verify = 0x%x\n",checksum);
    if (checksum == checksum_save) {
        printf("o.k.\n");
    } else {
        printf("Write error!\n");
    }

    //Pull start address back out for display
    n_read = (fm25640b_read_byte(HEADER_START_OFFSET+1))<<8;
    n_read += fm25640b_read_byte(HEADER_START_OFFSET);
    printf("Start address is $%04x\n",n_read);

    fm25640b_close();


fclose(f);

return 0;
}

//Fill the entire fram with 0
void blank_fram() {
    printf("Erasing\n");
    fm25640b_open();
    fm25640b_write_block(0,0,FM2560B_SIZE);
    fm25640b_close();
    printf("done.\n");
}

//Report the fram's contents in nice format
#if 0
//slow read
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
#endif

void read_fram() {
    printf("read FRAM\n");
    fm25640b_open();

    uint8_t buffer[FM2560B_SIZE];
    uint16_t i;
    uint8_t j;
    (void)fm25640b_read_block(0,FM2560B_SIZE,&buffer[0]);

    for (i=0x000;i<FM2560B_SIZE;i+=16) {
        printf("%04x: ",i);
        for (j=0;j<16;j++) {
           printf("%02x ",buffer[i+j]); 
        }
        for (j=0;j<16;j++) {
            if (buffer[j+i] >= ' ' && buffer[i+j] <= '~') {
                printf("%c",buffer[j+i]); 
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
printf("\n");
fm25640b_close();

}

//Test writing to every location in the fram and
// read it back.
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

void checksum_check() {

uint16_t i;
uint16_t j;
#define READ_BUFFER_SIZE 256
uint8_t buffer[READ_BUFFER_SIZE];
uint16_t bytes_read;
uint16_t n_read;
uint8_t image_size_hi;
uint8_t image_size_lo;
uint16_t image_size;
uint8_t checksum_from_image;
uint8_t checksum;

    //Now verify the fram
    fm25640b_open();
    image_size_lo = fm25640b_read_byte(HEADER_SIZE_OFFSET);
    image_size_hi = fm25640b_read_byte(HEADER_SIZE_OFFSET+1);

    printf("------header------\n");

    checksum=0;
    printf(" size:  [%02x][%02x]\n",image_size_lo,image_size_hi);
    checksum += image_size_lo;
    printf("    (cheksum = %02x)\n",checksum);
    checksum += image_size_hi;
    printf("    (cheksum = %02x)\n",checksum);

    image_size=0;
    image_size=image_size_hi << 8;
    image_size+=image_size_lo;


    i=0;
    n_read=DATA_OFFSET;
    do {
        //Read in chunks. We could have also done this in
        // one shot (easier code), but then we need a 8K
        // chunk of memory...
        printf("0x%04x ",n_read);
        fm25640b_read_block(n_read,READ_BUFFER_SIZE,buffer);
        i+=READ_BUFFER_SIZE;
        if (i > image_size) {
           //Last chunk if the image file wasn't an even
           //  multiple ofREAD_BUFFER_SIZE
           bytes_read = (image_size % READ_BUFFER_SIZE);
        } else {
           bytes_read = READ_BUFFER_SIZE;
        } 
        n_read += bytes_read;
        //Checksum up the chunk 
        for (j=0;j<bytes_read;j++) {
            checksum += buffer[j];
        }
        printf("0x%04x (checksum = %02x) read %u bytes\n",n_read-1,checksum,bytes_read);
    } while (i<image_size);

    checksum_from_image=fm25640b_read_byte(n_read);
    printf("Checksum stored in file 0x%x\n",checksum_from_image);
    printf("Checksum calulated from file 0x%x\n",checksum);

    printf("image [0x%04x] %u bytes\n",n_read,n_read);

    //Pull start address back out for display
    n_read = (fm25640b_read_byte(HEADER_START_OFFSET+1))<<8;
    n_read += fm25640b_read_byte(HEADER_START_OFFSET);
    printf("Start address is $%04x\n",n_read);

    fm25640b_close();
}
