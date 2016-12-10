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
Sheet 2 4
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
$Comp
L DS1813 U?
U 1 1 581AC38B
P 3700 2550
F 0 "U?" H 4000 2550 60  0000 C CNN
F 1 "DS1813" H 3975 2875 60  0000 C CNN
F 2 "" H 3975 2875 60  0000 C CNN
F 3 "" H 3975 2875 60  0000 C CNN
	1    3700 2550
	1    0    0    -1  
$EndComp
Text GLabel 3850 2825 3    60   Input ~ 0
~RESET~
$Comp
L GND #PWR?
U 1 1 581AC43C
P 3500 2975
F 0 "#PWR?" H 3500 2725 50  0001 C CNN
F 1 "GND" H 3500 2825 50  0000 C CNN
F 2 "" H 3500 2975 50  0000 C CNN
F 3 "" H 3500 2975 50  0000 C CNN
	1    3500 2975
	1    0    0    -1  
$EndComp
Text GLabel 3675 2900 3    60   Input ~ 0
+5v
Wire Wire Line
	3500 2725 3500 2975
Wire Wire Line
	3675 2725 3675 2900
Wire Wire Line
	3850 2725 3850 2825
$Comp
L SW_PUSH SW?
U 1 1 581AC48C
P 4275 2700
F 0 "SW?" H 4425 2810 50  0000 C CNN
F 1 "SW_PUSH" H 4275 2620 50  0000 C CNN
F 2 "" H 4275 2700 50  0000 C CNN
F 3 "" H 4275 2700 50  0000 C CNN
	1    4275 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 2700 3975 2700
$Comp
L Rsqig R?
U 1 1 581AC631
P 4575 2900
F 0 "R?" V 4655 2900 50  0000 C CNN
F 1 "3.3k" V 4500 2900 50  0000 C CNN
F 2 "" V 4505 2900 50  0000 C CNN
F 3 "" H 4575 2900 50  0000 C CNN
	1    4575 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 581AC694
P 4575 3150
F 0 "#PWR?" H 4575 2900 50  0001 C CNN
F 1 "GND" H 4575 3000 50  0000 C CNN
F 2 "" H 4575 3150 50  0000 C CNN
F 3 "" H 4575 3150 50  0000 C CNN
	1    4575 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4575 3150 4575 3050
Wire Wire Line
	4575 2750 4575 2700
Wire Notes Line
	1375 1950 2450 1950
Wire Notes Line
	2450 1950 2450 3700
Wire Notes Line
	2450 3700 1325 3700
Wire Notes Line
	1325 3700 1325 1950
Wire Notes Line
	1325 1950 1400 1950
Wire Notes Line
	3100 1950 4750 1950
Wire Notes Line
	4750 1950 4750 3725
Wire Notes Line
	4750 3725 3100 3725
Wire Notes Line
	3100 3725 3100 1950
Text Notes 1400 3575 0    60   ~ 0
4.000 MHz
Text Notes 3150 1875 0    60   ~ 0
Reset
Text Notes 1375 1875 0    60   ~ 0
Clock
Wire Wire Line
	1625 2450 1450 2450
Wire Wire Line
	1450 2450 1450 3325
Wire Wire Line
	1450 3325 1625 3325
Connection ~ 1625 2450
$EndSCHEMATC
