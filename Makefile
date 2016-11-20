.PHONY: clean

#Disable builtin rules
.SUFFIXES:
OBJS := main.o crt0.o interrupts.o vectors.o stop.o
CCLIB_PATH := /opt/cc65/share/cc65/lib/
CCLIB := supervision.lib

CC := cc65
AS := ca65
LD := ld65
SRECORD := /opt/srecord/bin/srec_cat

TARGET := none
CPU := --cpu 65c02
OPTIMIZE := -O
CFLAGS := -g


out.hex: out.bin
	$(SRECORD) $^ -binary -offset 0xe000 -o $@ -intel
	 x65dsasm addr=0xe000 cpu=65c02 $^ > out.dis 

out.bin: $(OBJS) sbc.lib
	$(LD) $(CFLAG) -C sbc.cfg -m out.map $^ -o $@ sbc.lib

%.s: %.c
	$(CC) $(CFLAGS) $(CPU) -t $(TARGET) $(OPTIMIZE) $^

%.o: %.s
	$(AS) $(CFLAGS) $(CPU) -v $^ --listing $*.lst

%.o: %.S
	$(AS) $(CFLAGS) $(CPU) -v $^ --listing $*.lst 

sbc.lib: crt0.o
	cp $(CCLIB_PATH)$(CCLIB) sbc.lib 
	ar65 d sbc.lib crt0.o
	ar65 a sbc.lib ./crt0.o

clean:
	rm -rf *.map *.dis *.o *.s *.lst sbc.lib out.bin out.hex

upload:
	cat out.hex > /dev/ttyS0
