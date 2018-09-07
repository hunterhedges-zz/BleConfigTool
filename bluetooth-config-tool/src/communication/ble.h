/*
 * ble.h
 *
 *  Created on: Sep 7, 2018
 *      Author: hhedg
 */

#ifndef BLE_H_
#define BLE_H_

void ble_init(void (*bleCallbackFxn)(uint8_t charReceived));
void ble_intHandler(void);
void ble_sendBuffer(uint8_t* buffer, uint8_t bufferSize);

#endif /* BLE_H_ */
