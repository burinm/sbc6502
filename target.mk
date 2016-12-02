.PHONY: clean

VPATH += ../src/project4
VPATH += ../src/driver

# unfortunately, assembler doesn't understand vpath
#  all platform files will have to stay here
#VPATH += ../src/driver/arch.6502

#Disable builtin rules
.SUFFIXES:

TOOLCHAIN := /opt/cc65
CCLIB_PATH := ./lib/

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

PROJECT ?= out

$(PROJECT).hex: $(PROJECT).bin
	$(SRECORD) $^ -binary -offset $(LOAD_ADDR) -o $@ -intel
	$(X65DASM) addr=$(LOAD_ADDR) cpu=65c02 $^ > $(PROJECT).dis 
	cp $(PROJECT).hex $(PROJECT).bin $(PROJECT).map $(PROJECT).dis ./bin

$(PROJECT).bin: $(OBJS) sbc.lib
	$(LD) -C $(SBC_CFG) -m $(PROJECT).map $^ -o $@ sbc.lib

#rom.bin: $(OBJS) sbc.lib
#	$(LD) -C sbc_exe.cfg -m out.map $^ -o $@ sbc.lib
#	$(X65DASM) addr=0x0200 cpu=65c02 $@ > out.dis 

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
	rm -rf *.map *.dis *.o *.s *.lst sbc.lib $(PROJECT).bin $(PROJECT).hex

upload:
	cat $(PROJECT).hex > /dev/ttyS0

image:
	scp $(PROJECT).bin 192.168.7.2:~/
