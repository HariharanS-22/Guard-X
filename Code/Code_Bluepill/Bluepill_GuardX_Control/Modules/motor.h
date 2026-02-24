/*
 * motor.h
 *
 *  Created on: Feb 22, 2026
 *      Author: Hariharan
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "main.h"

void Motor_Init(TIM_HandleTypeDef *htim);
void Motor_UpdateJoystick(int joyX, int joyY);
void Motor_SetSpeed(int spd);

#endif /* MOTOR_H_ */
