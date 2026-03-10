/*
 * mpu6050.c
 *
 *  Created on: Mar 9, 2026
 *      Author: Hariharan
 */
#include "mpu6050.h"

#define MPU_ADDR (0x68<<1)

static I2C_HandleTypeDef *MPU_I2C;

int16_t AccX,AccY,AccZ;
int16_t GyroX,GyroY,GyroZ;

float ax_offset=0,ay_offset=0,az_offset=0;

float velocity = 0;
float dt = 0.01;

void MPU6050_Init(I2C_HandleTypeDef *hi2c)
{
    MPU_I2C = hi2c;

    uint8_t data;

    data = 0;
    HAL_I2C_Mem_Write(MPU_I2C,MPU_ADDR,0x6B,1,&data,1,100);

    data = 0x00;
    HAL_I2C_Mem_Write(MPU_I2C,MPU_ADDR,0x1C,1,&data,1,100);

    data = 0x00;
    HAL_I2C_Mem_Write(MPU_I2C,MPU_ADDR,0x1B,1,&data,1,100);
}

void MPU6050_Read(void)
{
    uint8_t buffer[14];

    HAL_I2C_Mem_Read(MPU_I2C,MPU_ADDR,0x3B,1,buffer,14,100);

    AccX = buffer[0]<<8 | buffer[1];
    AccY = buffer[2]<<8 | buffer[3];
    AccZ = buffer[4]<<8 | buffer[5];

    GyroX = buffer[8]<<8 | buffer[9];
    GyroY = buffer[10]<<8 | buffer[11];
    GyroZ = buffer[12]<<8 | buffer[13];
}

void MPU6050_Calibrate()
{
    for(int i=0;i<500;i++)
    {
        MPU6050_Read();

        ax_offset += AccX;
        ay_offset += AccY;
        az_offset += AccZ;

        HAL_Delay(5);
    }

    ax_offset /= 500;
    ay_offset /= 500;
    az_offset /= 500;
}

float compute_Velocity(void)
{
    static uint32_t lastTime = 0;

    uint32_t now = HAL_GetTick();
    float dt = (now - lastTime)/1000.0f;

    lastTime = now;

    MPU6050_Read();

    float Ax = (AccX - ax_offset)/16384.0f;

    float ax_ms2 = Ax * 9.81f;

    if(fabs(ax_ms2) < 0.2f)
        ax_ms2 = 0;

    velocity += ax_ms2 * dt;

    velocity *= 0.98f;

    if(fabs(velocity) < 0.01f)
        velocity = 0;

    return velocity;
}
