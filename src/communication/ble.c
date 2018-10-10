/*
 * ble.c
 *
 *  Created on: Sep 7, 2018
 *      Author: hhedg
 */

#include <driverlib.h>
#include "ble.h"

/***************************
 * File Specific Defines
 ***************************/
#define PRIMARY_FUNCTION        GPIO_PRIMARY_MODULE_FUNCTION
#define BLE_UART_PINS           GPIO_PORT_P3, GPIO_PIN2 | GPIO_PIN3
#define BLE_UART_BASE           EUSCI_A2_BASE
#define RX_INTERRUPT            EUSCI_A_UART_RECEIVE_INTERRUPT
#define TX_INTERRUPT            EUSCI_A_UART_TRANSMIT_INTERRUPT
#define BLE_UART_INT            INT_EUSCIA2

/***************************
 * UART Configuration based on TI Tool:
 * http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
 ***************************/
const eUSCI_UART_Config bleUARTConfig =
{
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,                 // SMCLK Clock Source
    78,                                             // BRDIV = 78
    2,                                              // UCxBRF = 2 Baud 9600
    0,                                              // UCxBRS = 0
    EUSCI_A_UART_NO_PARITY,                         // No Parity
    EUSCI_A_UART_LSB_FIRST,                         // MSB First
    EUSCI_A_UART_ONE_STOP_BIT,                      // One stop bit
    EUSCI_A_UART_MODE,                              // UART mode
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION   // Oversampling
};

/***************************
 * Function to be called on receiving character from BLE
 ***************************/
void (*_bleCallbackFxn)(uint8_t charReceived);

/***************************
 * Setup BLE UART
 ***************************/
void ble_init(void (*bleCallbackFxn)(uint8_t charReceived))
{
    GPIO_setAsPeripheralModuleFunctionInputPin(BLE_UART_PINS, PRIMARY_FUNCTION);

    UART_initModule(BLE_UART_BASE, &bleUARTConfig);

    UART_enableModule(BLE_UART_BASE);

    UART_enableInterrupt(BLE_UART_BASE, RX_INTERRUPT);

    Interrupt_enableInterrupt(BLE_UART_INT);

    _bleCallbackFxn = bleCallbackFxn;
}

/***************************
 * Triggered on all EUSCI_A2 UART interrupts
 * Call callbackFxn when character is received
 ***************************/
void ble_intHandler(void)
{
    uint32_t intStatus = UART_getEnabledInterruptStatus(BLE_UART_BASE);

    if(intStatus == RX_INTERRUPT)
    {
        UART_clearInterruptFlag(BLE_UART_BASE, RX_INTERRUPT);

        uint8_t charReceived = UART_receiveData(BLE_UART_BASE);

        _bleCallbackFxn(charReceived);
    }
}

/***************************/
void ble_sendBuffer(uint8_t* buffer, uint8_t bufferSize)
{
    int i;
    for(i = 0; i < bufferSize; i++)
    {
        UART_transmitData(BLE_UART_BASE, buffer[i]);
    }
}

