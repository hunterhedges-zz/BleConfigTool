/*
 * main.c
 *  Author: Hunter Hedges
 *  Date: 9-7-2018
 */

/***************************
 * Includes
 ***************************/
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <driverlib.h>
#include "communication/ble.h"
#include "communication/usb.h"

/***************************
 * File Specific Defines
 ***************************/
#define ENTER_KEY           13
#define BACKSPACE_KEY       8
#define MAX_BUFFER_SIZE     128

/***************************
 * File Specific Functions
 ***************************/
void usbCallbackFxn(uint8_t charReceived);
void processUsbCommand(uint8_t* buffer, uint8_t bufferSize);
void newLineAndReturn(void);
void bleCallbackFxn(uint8_t charReceived);

/***************************
 * Start of program
 ***************************/
void main(void)
{
    WDT_A_holdTimer();

    /* Setting DCO (clock) to 12MHz */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    usb_init(&usbCallbackFxn);
    ble_init(&bleCallbackFxn);

    newLineAndReturn();

    Interrupt_enableMaster();

    while(true)
    { }
}

/***************************
 * Called every character received by USB
 ***************************/
void usbCallbackFxn(uint8_t charReceived)
{
    static uint8_t buffer[MAX_BUFFER_SIZE];
    static uint8_t ptr = 0;

    // Command too large...
    if(ptr == MAX_BUFFER_SIZE)
    {
        ptr = 0;
    }

    usb_sendBuffer(&charReceived, 1);

    if(charReceived == ENTER_KEY)
    {
        processUsbCommand(buffer, ptr);
        ptr = 0;
    }
    else if(charReceived == BACKSPACE_KEY)
    {
        ptr--;
    }
    else
    {
        buffer[ptr++] = charReceived;
    }
}

/***************************/
void processUsbCommand(uint8_t* buffer, uint8_t bufferSize)
{
    newLineAndReturn();
    ble_sendBuffer(buffer, bufferSize);
}

/***************************/
void newLineAndReturn(void)
{
    uint8_t* buffer = "\n\r";
    usb_sendBuffer(buffer, 2);
}

/***************************
 * Called every character received from BLE
 ***************************/
void bleCallbackFxn(uint8_t charReceived)
{
    usb_sendBuffer(&charReceived, 1);
}


