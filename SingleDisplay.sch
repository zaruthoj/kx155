EESchema Schematic File Version 2
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
LIBS:custom
LIBS:display-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 4750 2800
NoConn ~ 4750 3100
NoConn ~ 4750 3300
$Comp
L R R4
U 1 1 59D40956
P 6400 3000
AR Path="/59D40580/59D40956" Ref="R4"  Part="1" 
AR Path="/59D412E4/59D40956" Ref="R5"  Part="1" 
AR Path="/59D41D61/59D40956" Ref="R6"  Part="1" 
AR Path="/59D41D65/59D40956" Ref="R7"  Part="1" 
F 0 "R7" V 6480 3000 50  0000 C CNN
F 1 "20k" V 6400 3000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 6330 3000 50  0001 C CNN
F 3 "" H 6400 3000 50  0000 C CNN
	1    6400 3000
	0    1    1    0   
$EndComp
$Comp
L GND #PWR028
U 1 1 59D4095E
P 4300 3550
AR Path="/59D40580/59D4095E" Ref="#PWR028"  Part="1" 
AR Path="/59D412E4/59D4095E" Ref="#PWR031"  Part="1" 
AR Path="/59D41D61/59D4095E" Ref="#PWR034"  Part="1" 
AR Path="/59D41D65/59D4095E" Ref="#PWR037"  Part="1" 
F 0 "#PWR037" H 4300 3300 50  0001 C CNN
F 1 "GND" H 4300 3400 50  0000 C CNN
F 2 "" H 4300 3550 50  0000 C CNN
F 3 "" H 4300 3550 50  0000 C CNN
	1    4300 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 59D40964
P 6200 3700
AR Path="/59D40580/59D40964" Ref="#PWR029"  Part="1" 
AR Path="/59D412E4/59D40964" Ref="#PWR032"  Part="1" 
AR Path="/59D41D61/59D40964" Ref="#PWR035"  Part="1" 
AR Path="/59D41D65/59D40964" Ref="#PWR038"  Part="1" 
F 0 "#PWR038" H 6200 3450 50  0001 C CNN
F 1 "GND" H 6200 3550 50  0000 C CNN
F 2 "" H 6200 3700 50  0000 C CNN
F 3 "" H 6200 3700 50  0000 C CNN
	1    6200 3700
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 59D4096A
P 6200 3450
AR Path="/59D40580/59D4096A" Ref="C3"  Part="1" 
AR Path="/59D412E4/59D4096A" Ref="C4"  Part="1" 
AR Path="/59D41D61/59D4096A" Ref="C5"  Part="1" 
AR Path="/59D41D65/59D4096A" Ref="C6"  Part="1" 
F 0 "C6" H 6225 3550 50  0000 L CNN
F 1 "0.1uF" H 6225 3350 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 6238 3300 50  0001 C CNN
F 3 "" H 6200 3450 50  0000 C CNN
	1    6200 3450
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 59D40971
P 6450 3450
AR Path="/59D40580/59D40971" Ref="C8"  Part="1" 
AR Path="/59D412E4/59D40971" Ref="C9"  Part="1" 
AR Path="/59D41D61/59D40971" Ref="C10"  Part="1" 
AR Path="/59D41D65/59D40971" Ref="C11"  Part="1" 
F 0 "C11" H 6475 3550 50  0000 L CNN
F 1 "10uF" H 6475 3350 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 6488 3300 50  0001 C CNN
F 3 "" H 6450 3450 50  0000 C CNN
	1    6450 3450
	1    0    0    -1  
$EndComp
$Comp
L MAX7221 U2
U 1 1 59D40980
P 5300 2900
AR Path="/59D40580/59D40980" Ref="U2"  Part="1" 
AR Path="/59D412E4/59D40980" Ref="U4"  Part="1" 
AR Path="/59D41D61/59D40980" Ref="U6"  Part="1" 
AR Path="/59D41D65/59D40980" Ref="U8"  Part="1" 
F 0 "U8" H 5450 3500 60  0000 C CNN
F 1 "MAX7221" H 5150 3500 60  0000 C CNN
F 2 "custom:MAX7221CWG" H 5300 2900 60  0001 C CNN
F 3 "" H 5300 2900 60  0001 C CNN
	1    5300 2900
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR030
U 1 1 59D40987
P 6550 2900
AR Path="/59D40580/59D40987" Ref="#PWR030"  Part="1" 
AR Path="/59D412E4/59D40987" Ref="#PWR033"  Part="1" 
AR Path="/59D41D61/59D40987" Ref="#PWR036"  Part="1" 
AR Path="/59D41D65/59D40987" Ref="#PWR039"  Part="1" 
F 0 "#PWR039" H 6550 2750 50  0001 C CNN
F 1 "VCC" H 6550 3050 50  0000 C CNN
F 2 "" H 6550 2900 50  0000 C CNN
F 3 "" H 6550 2900 50  0000 C CNN
	1    6550 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3000 6250 3000
Wire Wire Line
	5800 2900 6550 2900
Connection ~ 6550 2900
Wire Wire Line
	6550 2900 6550 3000
Wire Wire Line
	4750 2700 4300 2700
Wire Wire Line
	4300 2700 4300 3550
Wire Wire Line
	4750 3200 4300 3200
Connection ~ 4300 3200
Wire Wire Line
	6200 3300 6200 2900
Connection ~ 6200 2900
Wire Wire Line
	6200 3300 6450 3300
Wire Wire Line
	6450 3600 6200 3600
Wire Wire Line
	6200 3600 6200 3700
Text Label 5800 3400 0    60   ~ 0
S_A
Text Label 5800 3300 0    60   ~ 0
S_F
Text Label 5800 3200 0    60   ~ 0
S_B
Text Label 5800 3100 0    60   ~ 0
S_G
Text Label 5800 2800 0    60   ~ 0
S_C
Text Label 5800 2500 0    60   ~ 0
S_D
Text Label 5800 2600 0    60   ~ 0
S_DP
Text Label 5800 2700 0    60   ~ 0
S_E
Text Label 4750 2600 2    60   ~ 0
D_5
Text Label 4750 3000 2    60   ~ 0
D_4
Text Label 4750 2900 2    60   ~ 0
D_3
Text Label 4750 3400 2    60   ~ 0
D_2
Text Label 4750 2500 2    60   ~ 0
D_1
Text Label 5800 4550 0    60   ~ 0
S_B
Text Label 4800 4450 2    60   ~ 0
S_G
Text Label 4800 4350 2    60   ~ 0
S_C
Text Label 4800 4250 2    60   ~ 0
S_DP
Text Label 4800 4150 2    60   ~ 0
S_D
Text Label 4800 4050 2    60   ~ 0
S_E
Text Label 5800 4250 0    60   ~ 0
S_F
Text Label 5800 4150 0    60   ~ 0
S_A
Text Label 5800 4650 0    60   ~ 0
D_5
Text Label 4800 4550 2    60   ~ 0
D_4
Text Label 5800 4450 0    60   ~ 0
D_3
Text Label 5800 4350 0    60   ~ 0
D_2
Text Label 5800 4050 0    60   ~ 0
D_1
Text HLabel 4750 2400 0    60   Input ~ 0
DIN
Text HLabel 5800 2400 2    60   Input ~ 0
DOUT
Text GLabel 5800 3500 2    60   Input ~ 0
CLK
Text GLabel 4750 3500 0    60   Input ~ 0
CS
$Comp
L 5x7Segment U3
U 1 1 59DAB88D
P 5350 4300
AR Path="/59D40580/59DAB88D" Ref="U3"  Part="1" 
AR Path="/59D412E4/59DAB88D" Ref="U5"  Part="1" 
AR Path="/59D41D61/59DAB88D" Ref="U7"  Part="1" 
AR Path="/59D41D65/59DAB88D" Ref="U9"  Part="1" 
F 0 "U9" V 5800 4550 60  0000 C CNN
F 1 "5x7Segment" V 5800 4100 60  0000 C CNN
F 2 "custom:5x7Segment" H 5600 4400 60  0001 C CNN
F 3 "" H 5600 4400 60  0001 C CNN
	1    5350 4300
	0    1    1    0   
$EndComp
$EndSCHEMATC
