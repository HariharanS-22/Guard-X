/*
 * motor.c
 *
 *  Created on: Feb 22, 2026
 *      Author: Hariharan
 */
#include "motor.h"

/* Private variables */
static TIM_HandleTypeDef *motorTim;

static int x = 512;
static int y = 512;

static int Speed = 800;   // PWM value (0-1000)

/* Motor pins */
#define IN1 GPIO_PIN_0
#define IN2 GPIO_PIN_1
#define IN3 GPIO_PIN_4
#define IN4 GPIO_PIN_5
#define MOTOR_PORT GPIOA

/* ------------ Internal Motor Actions ------------ */

static void Forward(void)
{
    __HAL_TIM_SET_COMPARE(motorTim,TIM_CHANNEL_1,Speed);
    __HAL_TIM_SET_COMPARE(motorTim,TIM_CHANNEL_2,Speed);

    HAL_GPIO_WritePin(MOTOR_PORT,IN1,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT,IN2,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT,IN3,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT,IN4,GPIO_PIN_RESET);
}

static void Backward(void)
{
    __HAL_TIM_SET_COMPARE(motorTim,TIM_CHANNEL_1,Speed);
    __HAL_TIM_SET_COMPARE(motorTim,TIM_CHANNEL_2,Speed);

    HAL_GPIO_WritePin(MOTOR_PORT,IN1,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT,IN2,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT,IN3,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT,IN4,GPIO_PIN_SET);
}

static void Right(void)
{
    __HAL_TIM_SET_COMPARE(motorTim,TIM_CHANNEL_1,Speed);
    __HAL_TIM_SET_COMPARE(motorTim,TIM_CHANNEL_2,Speed);

    HAL_GPIO_WritePin(MOTOR_PORT,IN1,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT,IN2,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT,IN3,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT,IN4,GPIO_PIN_RESET);
}

static void Left(void)
{
    __HAL_TIM_SET_COMPARE(motorTim,TIM_CHANNEL_1,Speed);
    __HAL_TIM_SET_COMPARE(motorTim,TIM_CHANNEL_2,Speed);

    HAL_GPIO_WritePin(MOTOR_PORT,IN1,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT,IN2,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT,IN3,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT,IN4,GPIO_PIN_SET);
}

static void carStop(void)
{
    __HAL_TIM_SET_COMPARE(motorTim,TIM_CHANNEL_1,0);
    __HAL_TIM_SET_COMPARE(motorTim,TIM_CHANNEL_2,0);

    HAL_GPIO_WritePin(MOTOR_PORT,IN1,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT,IN2,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT,IN3,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT,IN4,GPIO_PIN_RESET);
}

/* ------------ Public API ------------ */

void Motor_Init(TIM_HandleTypeDef *htim)
{
    motorTim = htim;

    HAL_TIM_PWM_Start(motorTim,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(motorTim,TIM_CHANNEL_2);

    carStop();
}

void Motor_UpdateJoystick(int joyX,int joyY)
{
    x = joyX ;
    y = joyY ;

    if (y > 600)
        Forward();
    else if (y < 400)
        Backward();
    else if (x < 400)
        Left();
    else if (x > 600)
        Right();
    else
        carStop();
}

void Motor_SetSpeed(int spd)
{
    if(spd > 1000) spd = 1000;
    Speed = spd;
}
