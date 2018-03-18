# sbc6502
## A single board computer based on the 65c02 CPU

## Features
* **65c02 CPU** running at 4MHz - Western Design Center static implementation of MOS6502
* **8K EEPROM** for bootloader "bios" - Atmel AT28C64B
* **32K SRAM** for program space - Cypress CY62256NLL-70PXC
* Loads code from **SPI** based **FRAM** - Cypress FM25640B, 64Kbit
* Space for **2x I/O controllers** - Western Design Center W65C22, 16x8bit in/out
* Low power green **LEDs 8x**!

![Wire wrapped prototype](sbc_top.png?raw=true "8-bit Single Board Computer")

