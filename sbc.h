#ifndef __SBC_H__
#define __SBC_H__

#define HEADER_SIZE_OFFSET    0
#define HEADER_START_OFFSET   2
#define DATA_OFFSET    2 


#define SBC_CODE_START  (uint8_t*)(0x0200)
#define VIA_0 (uint8_t*)(0x8010)

//#define VIA_0 (struct __VIA*)(8010)

struct {
    uint8_t     portB;
    uint8_t     portA;
    uint8_t     ddB;
    uint8_t     ddA;
    uint8_t     t1cl;
    uint8_t     t1ch;
    uint8_t     t1ll;
    uint8_t     t1lh;
    uint8_t     t2cl;
    uint8_t     t2ch;
    uint8_t     sr;
    uint8_t     acr;
    uint8_t     pcr;
    uint8_t     ifr;
    uint8_t     ier;
    uint8_t     ra2;
} __VIA;

#define DEBUG_PORT_ON DEVICE_6522_SET_DDB_OUT(VIA_0,2)
#define DEBUG_PB2_ON DEVICE_6522_WRITE_B(VIA_0,DEVICE_6522_READ_B(VIA_0) | 1<<2)  
#define DEBUG_PB2_OFF DEVICE_6522_WRITE_B(VIA_0,DEVICE_6522_READ_B(VIA_0) & ~(1<<2))


#endif
