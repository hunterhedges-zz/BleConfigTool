# Bluetooth Config Tool
This tool is specifically for configuring the SH-HC-08 Bluetooth 4.0 BLE Module from DSD Tech.

Found on Amazon: 
https://www.amazon.com/DSD-TECH-SH-HC-08-Transceiver-Compatible/dp/B01N4P7T0H

The BLE Module is configured through UART in which this tool uses a TI MSP432P401R development board.

Found on TI:
http://www.ti.com/tool/MSP-EXP432P401R

## How To Use
Connect to MSP432 through USB com port using 9600 Baud. 

Write commands found on BLE datasheet through USB com port. 

## Helpful Links

How to add msp432 driver library
https://e2e.ti.com/support/development_tools/code_composer_studio/f/81/p/578332/2122538#2122538

How to link the driver library 
http://processors.wiki.ti.com/index.php/Include_paths_and_options

SH-HC-08 (Bluetooth 4.0 BLE Module) Datasheet
https://drive.google.com/file/d/0B4urklB65vaCcEVyMm5haVVpMUk/view

TI Tool to configure UART baud rates
http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html