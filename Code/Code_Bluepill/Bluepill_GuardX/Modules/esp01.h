/*
 * esp01.h
 *
 *  Created on: Feb 22, 2026
 *      Author: Hariharan
 */

#ifndef ESP01_H_
#define ESP01_H_

#include "main.h"

void ESP01_Init(UART_HandleTypeDef *huart);
void ESP01_Decode(uint8_t c);

#endif /* ESP01_H_ */
