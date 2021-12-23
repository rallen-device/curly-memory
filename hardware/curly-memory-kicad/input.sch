EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 5
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
L Connector:AudioJack2 J?
U 1 1 61C83151
P 1300 1400
AR Path="/61C83151" Ref="J?"  Part="1" 
AR Path="/61C818BB/61C83151" Ref="J?"  Part="1" 
AR Path="/61C92EF9/61C83151" Ref="J?"  Part="1" 
AR Path="/61C93C03/61C83151" Ref="J?"  Part="1" 
AR Path="/61C96555/61C83151" Ref="J?"  Part="1" 
F 0 "J?" H 1332 1725 50  0000 C CNN
F 1 "AudioJack2" H 1332 1634 50  0000 C CNN
F 2 "" H 1300 1400 50  0001 C CNN
F 3 "~" H 1300 1400 50  0001 C CNN
	1    1300 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 61C8579B
P 1850 1300
AR Path="/61C818BB/61C8579B" Ref="C?"  Part="1" 
AR Path="/61C92EF9/61C8579B" Ref="C?"  Part="1" 
AR Path="/61C93C03/61C8579B" Ref="C?"  Part="1" 
AR Path="/61C96555/61C8579B" Ref="C?"  Part="1" 
F 0 "C?" V 1598 1300 50  0000 C CNN
F 1 "C" V 1689 1300 50  0000 C CNN
F 2 "" H 1888 1150 50  0001 C CNN
F 3 "~" H 1850 1300 50  0001 C CNN
	1    1850 1300
	0    1    1    0   
$EndComp
$Comp
L Diode:BAV99 D?
U 1 1 61C86767
P 3000 1300
AR Path="/61C818BB/61C86767" Ref="D?"  Part="1" 
AR Path="/61C92EF9/61C86767" Ref="D?"  Part="1" 
AR Path="/61C93C03/61C86767" Ref="D?"  Part="1" 
AR Path="/61C96555/61C86767" Ref="D?"  Part="1" 
F 0 "D?" V 3046 1379 50  0000 L CNN
F 1 "BAV99" V 2955 1379 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3000 800 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/BAV99_SER.pdf" H 3000 1300 50  0001 C CNN
	1    3000 1300
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 61C8787F
P 3000 950
AR Path="/61C818BB/61C8787F" Ref="#PWR?"  Part="1" 
AR Path="/61C92EF9/61C8787F" Ref="#PWR?"  Part="1" 
AR Path="/61C93C03/61C8787F" Ref="#PWR?"  Part="1" 
AR Path="/61C96555/61C8787F" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3000 800 50  0001 C CNN
F 1 "+5V" H 3015 1123 50  0000 C CNN
F 2 "" H 3000 950 50  0001 C CNN
F 3 "" H 3000 950 50  0001 C CNN
	1    3000 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 950  3000 1000
$Comp
L Device:R R?
U 1 1 61C8825D
P 2300 1300
AR Path="/61C818BB/61C8825D" Ref="R?"  Part="1" 
AR Path="/61C92EF9/61C8825D" Ref="R?"  Part="1" 
AR Path="/61C93C03/61C8825D" Ref="R?"  Part="1" 
AR Path="/61C96555/61C8825D" Ref="R?"  Part="1" 
F 0 "R?" V 2093 1300 50  0000 C CNN
F 1 "R" V 2184 1300 50  0000 C CNN
F 2 "" V 2230 1300 50  0001 C CNN
F 3 "~" H 2300 1300 50  0001 C CNN
	1    2300 1300
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61C8A134
P 3000 1650
AR Path="/61C818BB/61C8A134" Ref="#PWR?"  Part="1" 
AR Path="/61C92EF9/61C8A134" Ref="#PWR?"  Part="1" 
AR Path="/61C93C03/61C8A134" Ref="#PWR?"  Part="1" 
AR Path="/61C96555/61C8A134" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3000 1400 50  0001 C CNN
F 1 "GND" H 3005 1477 50  0000 C CNN
F 2 "" H 3000 1650 50  0001 C CNN
F 3 "" H 3000 1650 50  0001 C CNN
	1    3000 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 1650 3000 1600
Text HLabel 3600 1300 2    50   Input ~ 0
IN+
Wire Wire Line
	1500 1300 1700 1300
Wire Wire Line
	2000 1300 2150 1300
Wire Wire Line
	1500 1400 1600 1400
Wire Wire Line
	2450 1300 3200 1300
Wire Wire Line
	3200 1300 3600 1300
Connection ~ 3200 1300
$Comp
L power:GND #PWR?
U 1 1 61C8E055
P 1600 2200
AR Path="/61C818BB/61C8E055" Ref="#PWR?"  Part="1" 
AR Path="/61C92EF9/61C8E055" Ref="#PWR?"  Part="1" 
AR Path="/61C93C03/61C8E055" Ref="#PWR?"  Part="1" 
AR Path="/61C96555/61C8E055" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1600 1950 50  0001 C CNN
F 1 "GND" H 1605 2027 50  0000 C CNN
F 2 "" H 1600 2200 50  0001 C CNN
F 3 "" H 1600 2200 50  0001 C CNN
	1    1600 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 2200 1600 2150
Wire Wire Line
	1600 1400 1600 1850
$Comp
L Device:R R?
U 1 1 61C8D68F
P 1600 2000
AR Path="/61C818BB/61C8D68F" Ref="R?"  Part="1" 
AR Path="/61C92EF9/61C8D68F" Ref="R?"  Part="1" 
AR Path="/61C93C03/61C8D68F" Ref="R?"  Part="1" 
AR Path="/61C96555/61C8D68F" Ref="R?"  Part="1" 
F 0 "R?" H 1670 2046 50  0000 L CNN
F 1 "R" H 1670 1955 50  0000 L CNN
F 2 "" V 1530 2000 50  0001 C CNN
F 3 "~" H 1600 2000 50  0001 C CNN
	1    1600 2000
	1    0    0    -1  
$EndComp
$EndSCHEMATC
