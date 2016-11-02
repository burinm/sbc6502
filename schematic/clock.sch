EESchema Schematic File Version 2
LIBS:ecen5613
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:sbc-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MX045 U?
U 1 1 581A2D72
P 1900 2875
F 0 "U?" H 2275 2625 60  0000 C CNN
F 1 "MX045" H 1850 2875 60  0000 C CNN
F 2 "" H 1850 2875 60  0000 C CNN
F 3 "" H 1850 2875 60  0000 C CNN
	1    1900 2875
	1    0    0    -1  
$EndComp
Text GLabel 1625 2400 1    60   Input ~ 0
+5v
$Comp
L GND #PWR?
U 1 1 581A2E2F
P 2100 3400
F 0 "#PWR?" H 2100 3150 50  0001 C CNN
F 1 "GND" H 2100 3250 50  0000 C CNN
F 2 "" H 2100 3400 50  0000 C CNN
F 3 "" H 2100 3400 50  0000 C CNN
	1    2100 3400
	1    0    0    -1  
$EndComp
Text GLabel 2100 2400 1    60   Input ~ 0
Clock
Wire Wire Line
	2100 3400 2100 3325
Wire Wire Line
	2100 2475 2100 2400
Wire Wire Line
	1625 2475 1625 2400
NoConn ~ 1625 3325
$EndSCHEMATC
