PROJECT=blink_fader

OBJS := blink_fader.o crt0_exe.o 6522.o sbc_vectors.o

SBC_CFG := sbc_exe.cfg
LOAD_ADDR := 0x0200

export
message:
	make -f target.mk 
clean:
	make -f target.mk clean
