/* 8051_eeprom_loader.c - (c) 2016 - burin

    Atmel AT28C64B EEPROM writer

    NOTE - Writing routines work, serial does not!
*/

#include <stdio.h>
#include "89c51rc2_driver.h"
#include "circbuf.h"
#include "intel_hex.h"

#ifndef HEAP_SIZE
    #error "No HEAP_SIZE defined!"
#endif

_sdcc_external_startup()
{
//x2_mode_on();
setup_xram();

return 0;
}

void write_eeprom(uint16_t addr, uint16_t byte_count, uint8_t *d);
void write_eeprom_block(uint16_t addr, uint16_t byte_count, uint8_t d);
void _write_eeprom(uint16_t addr, uint16_t byte_count, uint8_t *d, uint8_t block_fill);

extern uint8_t serial_rx_up;

int8_t main()
{
volatile uint8_t *addr=0x8000;
uint16_t char_count;
uint16_t overflow_count;
uint16_t i;
uint16_t not_zeros;
uint8_t j;
char c;

state_i_e state_local;

setup_TX_RX_buffers();
setup_serial();

printf("[flash EEPROM]\n\r");

while(c != 'f') {
    printf("Press 'f' key to flash\n\r");
    printf(" (e) erase (r) read (z) zero check\n\r");

#ifndef POLLING
c = getchar_blocking();
#else
c = getchar();
#endif

#if 1
    if (c == 'e') {
        printf("Erasing flash\n\r");
        write_eeprom_block(0x8000, 0x2000, 0);
    }
    if (c == 'r') {
        for (i=0;i<0x2000;i++) {
             if (i % 16 == 0) { printf("%04x\n\r",(uint16_t)addr +i);}
               printf("[%x]",*(uint8_t *)(addr + i)) ;
        }
    }
    if (c == 'z') {
        not_zeros=0;
        for (i=0;i<0x2000;i++) {
               if (*(uint8_t *)(addr + i) != 0) {
                  //printf("%04xx ",(uint16_t)addr+i); 
                  not_zeros++;
                }
                //if ((i % 8) == 0) {
                 //   printf("\n\r");
                //}
        }
        printf("found %u non-zero locations\n\r",not_zeros);
    }
#endif
}
printf("flashing\n\r");

printf("\n\r");

char_count=0;
overflow_count=0;

c=0;
intel_hex_sm_init(&write_eeprom);
//while (c != '@') { 
while (1) { 

#ifdef POLLING

            c = getchar();
            state_local = intel_hex_sm_next(c);
            char_count++;
#else
    #if 0
        if (serial_rx_up) {
            if (serial_rx_up == 2) {
                overflow_count++;
            }
            c = getchar();
            char_count++;
            state_local = intel_hex_sm_next(c);
        }
    #endif
        if (serial_rx_up) {
            if (serial_rx_up == 2) {
                overflow_count++;
            }
            c = getchar();
            char_count++;
        }
#endif
   
        if (state_local == ERROR_S) { break; }
        if (state_local == EOF_S) { break; }
  //      if (char_count == 0x2000) { break; }


}

printf("state is %x\n\r",state_local);
printf("read %u characters in\n\r",char_count);
printf("overflow %u characters in\n\r",overflow_count);

if (state_local == ERROR_S) {
     printf("ERROR_S\n\r");
     for(;;);
}

for (i=0;i<0x2000;i++) {
    if (i % 16 == 0) { printf("%04x\n\r",(uint16_t)addr +i);}
    printf("[%x]",*(uint8_t *)(addr + i)) ;
}
for(;;);

return 0;
}


void write_eeprom_block(uint16_t addr, uint16_t byte_count, uint8_t d)
{
    _write_eeprom(addr, byte_count, &d, 1);
}
#if 0
void write_eeprom(uint16_t addr, uint16_t byte_count, uint8_t *d)
{
    _write_eeprom(addr, byte_count, d, 0);
}
#endif

void _write_eeprom(uint16_t addr, uint16_t byte_count, uint8_t *d, uint8_t block_fill) { 
uint16_t i;
uint16_t j;
uint8_t w_byte;
i=0;
    do {
//        printf("w:%x\n\r",addr);
        for (j=addr % 64;j<64;j++) {
                w_byte =  block_fill ? *d : d[i];
                *(__xdata uint8_t *)(addr) = w_byte;
            addr++;
            i++;
        }
        // /DATA polling - poll on last byte written
        //while (*(__xdata uint8_t *)(addr -1 ) != *(__xdata uint8_t *)(addr -1));
        while (*(__xdata uint8_t *)(addr -1 ) != w_byte);

            printf(".");
            if (i % 0x800 == 0) {
                printf("\r");
            }
    } while ( i< byte_count);
}
#if 1
void write_eeprom(uint16_t addr, uint16_t byte_count, uint8_t *d) { 

uint8_t i;
uint16_t j;
i=0;
    do {
    for (j=addr % 64;j<64;j++) {
        printf("%04lx:%x ", addr, d[i]);
        addr++;
        i++;
    }
    printf("\n\r");
    } while ( i< byte_count);
}
#endif


#if 0
This works

volatile uint8_t *addr=0x8000;

for (i=0;i<0x2000;i++) {
    if (i % 16 == 0) { printf("%04x\n\r",(uint16_t)addr +i);}
    printf("[%x]",*(uint8_t *)(addr + i)) ;

}

for (i=0;i<0x2000;i+=64) {

    for (j=0;j<64;j++) {
        *(__xdata uint8_t *)(addr + i + j) = 0x22;
    }
    // /DATA polling
    while (*(__xdata uint8_t *)(addr + i) != *(__xdata uint8_t *)(addr + i));

        printf(".");
        if (i % 0x800 == 0) {
            printf("\r");
        }

}
#endif
