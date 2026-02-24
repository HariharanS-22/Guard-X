/*
 * hcsr04.h
 *
 *  Created on: Feb 24, 2026
 *      Author: Hariharan
 */

#ifndef HCSR04_H_
#define HCSR04_H_

#include "main.h"

void HCSR04_Init(TIM_HandleTypeDef *htim);
float HCSR04_Read(void);

#endif /* HCSR04_H_ */
