/*
 * main.h
 *  Author: Hunter Hedges
 *  Date: 6-20-2018
 */

void usbIntHandler(void);
void sendBufferToUART(uint32_t UART_BASE, uint8_t buffer[], uint8_t sizeOfBuffer);
void bluetoothIntHandler(void);
void timer32IntHandler(void);
void toggleLED(void);
