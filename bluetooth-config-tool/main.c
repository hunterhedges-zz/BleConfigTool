/*
 * main.c
 *  Author: Hunter Hedges
 *  Date: 6-20-2018
 */

#include <driverlib.h>
#include "config.h"
#include "main.h"

void main(void)
{
    WDT_A_holdTimer();

    /* Setting DCO (clock) to 12MHz */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    // Board LED GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    initUART();
    initTimer32();

    Interrupt_enableMaster();

    while(1)
    { }

}

// Called every byte received
// Baud will ALWAYS remain at 9600 for this**
void usbIntHandler(void)
{
    uint16_t intStatus = UART_getEnabledInterruptStatus(DEBUG_UART_BASE);
    uint8_t newLineAndReturn[] = { '\n', '\r' };
    static uint8_t usbRxBuffer[128];
    static uint8_t usbRxBufferPtr = 0;

    if(intStatus == RX_INTERRUPT)
    {
        UART_clearInterruptFlag(DEBUG_UART_BASE, RX_INTERRUPT);

        // Prevent going out of bounds
        if(usbRxBufferPtr < 128)
        {
            usbRxBuffer[usbRxBufferPtr] = UART_receiveData(DEBUG_UART_BASE);
        }
        else
        {
            usbRxBufferPtr = 0;
        }

        // 13 == ENTER KEY signaling EOT
        if(usbRxBuffer[usbRxBufferPtr] == 13)
        {
            sendBufferToUART(BLE_UART_BASE, usbRxBuffer, usbRxBufferPtr);
            sendBufferToUART(DEBUG_UART_BASE, newLineAndReturn, 2);
            usbRxBufferPtr = 0;
        }
        else
        {
            usbRxBufferPtr++;
        }

    }

}

//
void sendBufferToUART(uint32_t UART_BASE, uint8_t buffer[], uint8_t sizeOfBuffer)
{
    int i;

    for(i = 0; i < sizeOfBuffer; i++)
    {
        UART_transmitData(UART_BASE, buffer[i]);
    }

}

// Triggered every byte received by BLE
void bluetoothIntHandler(void)
{
    uint16_t intStatus = UART_getEnabledInterruptStatus(BLE_UART_BASE);

    if(intStatus == RX_INTERRUPT)
    {
        UART_clearInterruptFlag(BLE_UART_BASE, RX_INTERRUPT);

        uint8_t charReceived = UART_receiveData(BLE_UART_BASE);

        // Echo back to USB
        UART_transmitData(DEBUG_UART_BASE, charReceived);
    }

}

// Called every 500ms to toggle LED
// Show that we are running
void timer32IntHandler(void)
{
    Timer32_clearInterruptFlag(TIMER32_BASE);

    // Reset timer
    Timer32_setCount(TIMER32_BASE, TIMER32_TIME);

    toggleLED();
}

//
void toggleLED(void)
{
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}
