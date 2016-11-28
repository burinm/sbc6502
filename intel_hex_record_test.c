#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "intel_hex.h"

extern uint16_t write_count;

void write_eeprom(uint16_t address_i, uint8_t byte_count, uint8_t *d);
void write_eeprom(uint16_t address_i, uint8_t byte_count, uint8_t *d) {
uint8_t i;
    for (i=0;i<byte_count;i++) {
        printf("%x:",*(uint8_t *)(d+i));
    }
}

int main(int argc, char * argv[]) {
int hex_fd;
char c;
state_i_e state;
//open file
hex_fd=open(argv[1], O_RDONLY);
if (hex_fd != -1) {

intel_hex_sm_init(&write_eeprom);

while (read(hex_fd,&c,1)) {
    state = intel_hex_sm_next(c);
}

    close(hex_fd);
} else {
    printf("Could not open file %s\n",argv[1]);
    return -1;
}

printf("Read in %u bytes\n",write_count);

}
