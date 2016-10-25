.PHONY: clean

#Disable builtin rules
.SUFFIXES:
OBJS := main.o crt0.o interrupts.o vectors.o stop.o
CCLIB_PATH := /opt/cc65/share/cc65/lib/
CCLIB := supervision.lib

CC := cc65
AS := ca65
LD := ld65

TARGET := none
CPU := 65c02


out.bin: $(OBJS) sbc.lib
	$(LD) -S 0x8000 -C sbc.cfg -m out.map $^ -o $@ sbc.lib

#out.bin: $(OBJS) crt0.o
#	$(LD) -S 0x8000 -C sbc.cfg -m out.map $^ -o $@

%.s: %.c
	$(CC) -t $(TARGET) --cpu $(CPU) $^

%.o: %.s
	$(AS) -t $(TARGET) -v $^

%.o: %.S
	$(AS) -t $(TARGET) -v $^

sbc.lib: $(CCLIB) crt0.o
	cp $(CCLIB_PATH)$(CCLIB) sbc.lib 

clean:
	rm -rf *.map *.o *.s sbc.lib out.bin
