PROJECT=bootloader

OBJS := bootloader.o fm25640b.o spi.o sbc_spi.o crt0.o interrupts.o vectors.o stop.o 6522.o

SBC_CFG := sbc.cfg
LOAD_ADDR := 0xe000

export
message:
	make -f target.mk 
clean:
	make -f target.mk clean
