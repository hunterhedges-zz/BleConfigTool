/*
 * config.c
 *  Author: Hunter Hedges
 *  Date: 6-20-2018
 */

#include <driverlib.h>
#include "config.h"

const eUSCI_UART_Config debugUARTConfig =
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

void initUART(void)
{
    GPIO_setAsPeripheralModuleFunctionInputPin(DEBUG_UART_PINS, PRIMARY_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(BLE_UART_PINS, PRIMARY_FUNCTION);

    UART_initModule(DEBUG_UART_BASE, &debugUARTConfig);
    UART_initModule(BLE_UART_BASE, &bleUARTConfig);

    UART_enableModule(DEBUG_UART_BASE);
    UART_enableModule(BLE_UART_BASE);

    UART_enableInterrupt(DEBUG_UART_BASE, RX_INTERRUPT);
    UART_enableInterrupt(BLE_UART_BASE, RX_INTERRUPT);

    Interrupt_enableInterrupt(DEBUG_UART_INT);
    Interrupt_enableInterrupt(BLE_UART_INT);

}

void initTimer32(void)
{
    Timer32_initModule(TIMER32_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);

    Timer32_enableInterrupt(TIMER32_BASE);

    Interrupt_enableInterrupt(INT_T32_INT1);

    // TIMER32_TIME / 12,000,000 [Clock Freq]
    Timer32_setCount(TIMER32_BASE, TIMER32_TIME);

    Timer32_startTimer(TIMER32_BASE, true);

}
