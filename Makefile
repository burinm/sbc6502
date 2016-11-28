.PHONY: clean

vpath %.h ../src/driver
vpath %.c ../src/driver

#Disable builtin rules
.SUFFIXES:

TOOLCHAIN := /opt/cc65
#OBJS := blink_stack.o crt0_exe.o 6522.o sbc_vectors.o
#OBJS := blink_knightrider.o crt0_exe.o 6522.o sbc_vectors.o
#OBJS := blink_fader.o crt0.o interrupts.o vectors.o stop.o 6522.o
OBJS := bootloader.o fm25640b.o spi.o sbc_spi.o crt0.o interrupts.o vectors.o stop.o 6522.o
#OBJS := led_sequence.o crt0.o interrupts.o vectors.o stop.o 6522.o

#CCLIB_PATH := $(TOOLCHAIN)/share/cc65/lib/
#CCLIB_PATH := /home/burin/cc65/lib/
CCLIB_PATH := ./lib/
#CCLIB := supervision.lib

CC := $(TOOLCHAIN)/bin/cc65
AS := $(TOOLCHAIN)/bin/ca65
LD := $(TOOLCHAIN)/bin/ld65
AR := $(TOOLCHAIN)/bin/ar65
SRECORD := /opt/srecord/bin/srec_cat
X65DASM := /opt/6502bin/x65dsasm

TARGET := none
#CPU := --cpu 65c02
CPU := --cpu 6502
CCLIB := supervision.lib.6502
#CCLIB := supervision.lib.65c02

# O1 = inline more
#OPTIMIZE := -O -Oi
CFLAGS := -g

INCLUDES := -I ../src/driver

out.hex: out.bin
	$(SRECORD) $^ -binary -offset 0xe000 -o $@ -intel
	 $(X65DASM) addr=0xe000 cpu=65c02 $^ > out.dis 

out.bin: $(OBJS) sbc.lib
	$(LD) -C sbc.cfg -m out.map $^ -o $@ sbc.lib

rom.bin: $(OBJS) sbc.lib
	$(LD) -C sbc_exe.cfg -m out.map $^ -o $@ sbc.lib
	 $(X65DASM) addr=0x0200 cpu=65c02 $@ > out.dis 

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
	rm -rf *.map *.dis *.o *.s *.lst sbc.lib *.bin out.hex

upload:
	cat out.hex > /dev/ttyS0

image:
	scp rom.bin 192.168.7.2:~/
