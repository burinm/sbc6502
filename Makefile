.PHONY: clean

vpath %.h ../src/driver
vpath %.c ../src/driver

#Disable builtin rules
.SUFFIXES:

TOOLCHAIN := /opt/cc65
OBJS := main.o crt0.o interrupts.o vectors.o stop.o 6522.o
CCLIB_PATH := $(TOOLCHAIN)/share/cc65/lib/
CCLIB := supervision.lib

CC := $(TOOLCHAIN)/bin/cc65
AS := $(TOOLCHAIN)/bin/ca65
LD := $(TOOLCHAIN)/bin/ld65
AR := $(TOOLCHAIN)/bin/ar65
SRECORD := /opt/srecord/bin/srec_cat

TARGET := none
CPU := --cpu 65c02
#CPU := --cpu 6502

# O1 = inline more
#OPTIMIZE := -O -Oi
CFLAGS := -g

INCLUDES := -I ../src/driver

out.hex: out.bin
	$(SRECORD) $^ -binary -offset 0xe000 -o $@ -intel
	 x65dsasm addr=0xe000 cpu=65c02 $^ > out.dis 

out.bin: $(OBJS) sbc.lib
	$(LD) $(CFLAG) -C sbc.cfg -m out.map $^ -o $@ sbc.lib

%.s: %.c
	$(CC) $(INCLUDES) $(CFLAGS) $(CPU) -t $(TARGET) $(OPTIMIZE) $^ -o $*.s

%.o: %.s
	$(AS) $(CFLAGS) $(CPU) -v $^ --listing $*.lst

%.o: %.S
	$(AS) $(CFLAGS) $(CPU) -v $^ --listing $*.lst 

sbc.lib: crt0.o
	cp $(CCLIB_PATH)$(CCLIB) sbc.lib 
	$(AR) d sbc.lib crt0.o
	$(AR) a sbc.lib ./crt0.o

clean:
	rm -rf *.map *.dis *.o *.s *.lst sbc.lib out.bin out.hex

upload:
	cat out.hex > /dev/ttyS0
