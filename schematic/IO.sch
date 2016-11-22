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
Sheet 4 4
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
L FM25640B U?
U 1 1 583481DA
P 2275 2000
F 0 "U?" H 2700 1625 60  0000 C CNN
F 1 "FM25640B" H 2475 2325 60  0000 C CNN
F 2 "" H 2475 2325 60  0000 C CNN
F 3 "" H 2475 2325 60  0000 C CNN
	1    2275 2000
	1    0    0    -1  
$EndComp
Text GLabel 1675 2175 0    60   Input ~ 0
PB0
Text GLabel 2950 1825 2    60   Input ~ 0
PB6
Text GLabel 2950 1925 2    60   Input ~ 0
PB7
Wire Wire Line
	2825 1825 2950 1825
Wire Wire Line
	2825 1925 2950 1925
Wire Wire Line
	1675 2175 1775 2175
$Comp
L GND #PWR?
U 1 1 583481E7
P 2175 2700
F 0 "#PWR?" H 2175 2450 50  0001 C CNN
F 1 "GND" H 2175 2550 50  0000 C CNN
F 2 "" H 2175 2700 50  0000 C CNN
F 3 "" H 2175 2700 50  0000 C CNN
	1    2175 2700
	1    0    0    -1  
$EndComp
Text GLabel 2125 1225 0    60   Input ~ 0
+5v
$Comp
L C_Small C?
U 1 1 583481EE
P 2000 1425
F 0 "C?" H 2010 1495 50  0001 L CNN
F 1 ".1uF" H 2010 1345 50  0000 L CNN
F 2 "" H 2000 1425 50  0000 C CNN
F 3 "" H 2000 1425 50  0000 C CNN
	1    2000 1425
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 583481F4
P 1775 1425
F 0 "#PWR?" H 1775 1175 50  0001 C CNN
F 1 "GND" H 1775 1275 50  0000 C CNN
F 2 "" H 1775 1425 50  0000 C CNN
F 3 "" H 1775 1425 50  0000 C CNN
	1    1775 1425
	1    0    0    -1  
$EndComp
Wire Wire Line
	2125 1225 2175 1225
Wire Wire Line
	2175 1225 2175 1550
Wire Wire Line
	2100 1425 2175 1425
Connection ~ 2175 1425
Wire Wire Line
	1900 1425 1775 1425
Wire Wire Line
	2175 2700 2175 2625
Text GLabel 2975 2625 2    60   Input ~ 0
PB1
Wire Wire Line
	2475 2625 2975 2625
$Comp
L WD65c22 U?
U 1 1 5834833D
P 8975 3075
F 0 "U?" H 8975 3475 50  0000 C CNN
F 1 "WD65c22" V 8975 2650 50  0000 C CNN
F 2 "" H 8975 3075 50  0000 C CNN
F 3 "" H 8975 3075 50  0000 C CNN
	1    8975 3075
	1    0    0    -1  
$EndComp
Entry Wire Line
	9675 2975 9775 2875
Entry Wire Line
	9675 2875 9775 2775
Entry Wire Line
	9675 2775 9775 2675
Entry Wire Line
	9675 2675 9775 2575
Entry Wire Line
	9675 2575 9775 2475
Entry Wire Line
	9675 2475 9775 2375
Entry Wire Line
	9675 2375 9775 2275
Entry Wire Line
	9675 2275 9775 2175
Wire Bus Line
	9775 1750 9775 2875
Text GLabel 9175 5175 3    60   Input ~ 0
A4
Wire Wire Line
	9175 5175 9175 5050
Text GLabel 9275 5350 3    60   Input ~ 0
~I/O~
Wire Wire Line
	9275 5350 9275 5050
Text Notes 9400 5250 0    60   ~ 0
8010-801f
$Comp
L GND #PWR?
U 1 1 58348352
P 8775 5375
F 0 "#PWR?" H 8775 5125 50  0001 C CNN
F 1 "GND" H 8775 5225 50  0000 C CNN
F 2 "" H 8775 5375 50  0000 C CNN
F 3 "" H 8775 5375 50  0000 C CNN
	1    8775 5375
	1    0    0    -1  
$EndComp
Wire Wire Line
	8775 5050 8775 5375
Text GLabel 8725 1700 0    60   Input ~ 0
+5v
$Comp
L GND #PWR?
U 1 1 5834835A
P 8400 1975
F 0 "#PWR?" H 8400 1725 50  0001 C CNN
F 1 "GND" H 8400 1825 50  0000 C CNN
F 2 "" H 8400 1975 50  0000 C CNN
F 3 "" H 8400 1975 50  0000 C CNN
	1    8400 1975
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 58348360
P 8600 1875
F 0 "C?" H 8610 1945 50  0001 L CNN
F 1 ".1uF" H 8610 1795 50  0000 L CNN
F 2 "" H 8600 1875 50  0000 C CNN
F 3 "" H 8600 1875 50  0000 C CNN
	1    8600 1875
	0    1    1    0   
$EndComp
Wire Wire Line
	8700 1875 8825 1875
Wire Wire Line
	8825 1700 8825 1925
Wire Wire Line
	8825 1700 8725 1700
Connection ~ 8825 1875
Wire Wire Line
	8400 1975 8400 1875
Wire Wire Line
	8400 1875 8500 1875
Text GLabel 9775 1750 1    60   Input ~ 0
D0-7
Text GLabel 9925 3525 2    60   Input ~ 0
R~W~
Text GLabel 9900 3375 2    60   Input ~ 0
~RESET~
Text GLabel 8275 4700 3    60   Input ~ 0
CLOCK
Wire Wire Line
	9675 3375 9900 3375
Wire Wire Line
	9675 3525 9925 3525
Wire Wire Line
	8275 4700 8275 4500
Entry Wire Line
	8175 2225 8275 2325
Entry Wire Line
	8175 2325 8275 2425
Entry Wire Line
	8175 2425 8275 2525
Entry Wire Line
	8175 2525 8275 2625
Wire Bus Line
	8175 2525 8175 1675
Text GLabel 8175 1675 1    60   Input ~ 0
D0-3
Entry Wire Line
	8025 2675 8125 2775
Entry Wire Line
	8025 2775 8125 2875
Entry Wire Line
	8025 2875 8125 2975
Entry Wire Line
	8025 2975 8125 3075
Entry Wire Line
	8025 3075 8125 3175
Entry Wire Line
	8025 3175 8125 3275
Entry Wire Line
	8025 3275 8125 3375
Entry Wire Line
	8025 3375 8125 3475
Wire Wire Line
	8125 2775 8275 2775
Wire Wire Line
	8125 2875 8275 2875
Wire Wire Line
	8125 2975 8275 2975
Wire Wire Line
	8125 3075 8275 3075
Wire Wire Line
	8125 3175 8275 3175
Wire Wire Line
	8125 3275 8275 3275
Wire Wire Line
	8125 3375 8275 3375
Wire Wire Line
	8125 3475 8275 3475
Wire Bus Line
	8025 3375 8025 2500
Wire Bus Line
	8025 2500 7925 2500
Text GLabel 7925 2500 1    60   Input ~ 0
x8_LED
Text GLabel 8150 4350 0    60   Input ~ 0
PB0
Text GLabel 8125 3750 0    60   Input ~ 0
PB6
Text GLabel 8125 3650 0    60   Input ~ 0
PB7
Wire Wire Line
	8125 3650 8275 3650
Wire Wire Line
	8125 3750 8275 3750
Wire Wire Line
	8150 4350 8275 4350
Text GLabel 8150 4250 0    60   Input ~ 0
PB1
Wire Wire Line
	8150 4250 8275 4250
$Comp
L Led_Small D?
U 1 1 58348402
P 2750 6175
F 0 "D?" H 2700 6300 50  0001 L CNN
F 1 "Led_Small" H 2575 6075 50  0001 L CNN
F 2 "" V 2750 6175 50  0000 C CNN
F 3 "" V 2750 6175 50  0000 C CNN
	1    2750 6175
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 58348408
P 2850 6625
F 0 "#PWR?" H 2850 6375 50  0001 C CNN
F 1 "GND" H 2850 6475 50  0000 C CNN
F 2 "" H 2850 6625 50  0000 C CNN
F 3 "" H 2850 6625 50  0000 C CNN
	1    2850 6625
	1    0    0    -1  
$EndComp
$Comp
L Rsqig R?
U 1 1 5834840E
P 2850 6375
F 0 "R?" V 2930 6375 50  0001 C CNN
F 1 "2.2K" V 2775 6375 50  0000 C CNN
F 2 "" V 2780 6375 50  0000 C CNN
F 3 "" H 2850 6375 50  0000 C CNN
	1    2850 6375
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 6625 2850 6525
Wire Wire Line
	2850 6225 2850 6175
Entry Wire Line
	2550 6075 2650 6175
Wire Bus Line
	2550 6075 2550 5875
Text GLabel 2550 5875 1    60   Input ~ 0
x8_LED
Text Notes 2975 6400 0    60   ~ 0
x8
$Comp
L 74LS08 U?
U 1 1 58348893
P 2500 4075
F 0 "U?" H 2500 4125 50  0000 C CNN
F 1 "74LS08" H 2500 4025 50  0000 C CNN
F 2 "" H 2500 4075 50  0000 C CNN
F 3 "" H 2500 4075 50  0000 C CNN
	1    2500 4075
	-1   0    0    1   
$EndComp
Text GLabel 1825 4075 0    60   Input ~ 0
~IRQ~
Text GLabel 3200 3975 2    60   Input ~ 0
~IRQ1~
Text GLabel 3200 4175 2    60   Input ~ 0
~IRQ2~
Wire Wire Line
	1825 4075 1900 4075
Wire Wire Line
	3100 3975 3200 3975
Wire Wire Line
	3100 4175 3200 4175
Text GLabel 2950 2125 2    60   Input ~ 0
+5v
Wire Wire Line
	2825 2125 2950 2125
Text GLabel 2950 2225 2    60   Input ~ 0
+5v
Wire Wire Line
	2825 2225 2950 2225
$EndSCHEMATC
