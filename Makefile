
all:
	make -f bootloader.mk
	make -f bootloader.mk clean
	make -f led_sequence.mk
	make -f led_sequence.mk clean
	make -f blink_stack.mk
	make -f blink_stack.mk clean
	make -f blink_knightrider.mk
	make -f blink_knightrider.mk clean
	make -f blink_fader.mk
	make -f blink_fader.mk clean

clean:
	make -f bootloader.mk clean
	make -f led_sequence.mk clean
	make -f blink_stack.mk clean
	make -f blink_knightrider.mk clean
	make -f blink_fader.mk clean
	rm -rf ./bin/*
