/*
 * config.h
 *  Author: Hunter Hedges
 *  Date: 6-20-2018
 */

#define PRIMARY_FUNCTION    GPIO_PRIMARY_MODULE_FUNCTION
#define DEBUG_UART_PINS     GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3
#define BLE_UART_PINS       GPIO_PORT_P3, GPIO_PIN2 | GPIO_PIN3

#define DEBUG_UART_BASE     EUSCI_A0_BASE
#define BLE_UART_BASE       EUSCI_A2_BASE

#define RX_INTERRUPT        EUSCI_A_UART_RECEIVE_INTERRUPT
#define TX_INTERRUPT        EUSCI_A_UART_TRANSMIT_INTERRUPT

#define DEBUG_UART_INT      INT_EUSCIA0
#define BLE_UART_INT        INT_EUSCIA2

#define TIMER32_TIME        6000000     // 6,000,000[Timer32 Count] / 12,000,000[Clock Freq] = 500ms

void initUART(void);
void initTimer32(void);
