/*
 * mpu6050.h
 *
 *  Created on: Mar 9, 2026
 *      Author: Hariharan
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#include "main.h"
#include <math.h>

void MPU6050_Init(I2C_HandleTypeDef *hi2c);
void MPU6050_Read(void);
void MPU6050_Calibrate(void);
float compute_Velocity(void);

extern int16_t AccX,AccY,AccZ;
extern int16_t GyroX,GyroY,GyroZ;

extern float ax_offset,ay_offset,az_offset;
extern float velocity;
extern float dt;

#endif /* MPU6050_H_ */
