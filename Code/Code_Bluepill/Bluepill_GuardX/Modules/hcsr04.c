/*
 * hcsr04.c
 *
 *  Created on: Feb 24, 2026
 *      Author: Hariharan
 */
#include "hcsr04.h"

static TIM_HandleTypeDef *HCSR04_TIM;

#define TRIG_PORT GPIOB
#define TRIG_PIN  GPIO_PIN_0
#define ECHO_PORT GPIOB
#define ECHO_PIN  GPIO_PIN_1

static void delay_us(uint16_t us)
{
    __HAL_TIM_SET_COUNTER(HCSR04_TIM,0);
    while(__HAL_TIM_GET_COUNTER(HCSR04_TIM) < us);
}

void HCSR04_Init(TIM_HandleTypeDef *htim)
{
	HCSR04_TIM = htim;
    HAL_TIM_Base_Start(HCSR04_TIM);
}

float HCSR04_Read(void)
{
    uint32_t start, stop;

    HAL_GPIO_WritePin(TRIG_PORT,TRIG_PIN,GPIO_PIN_RESET);
    delay_us(2);

    HAL_GPIO_WritePin(TRIG_PORT,TRIG_PIN,GPIO_PIN_SET);
    delay_us(10);
    HAL_GPIO_WritePin(TRIG_PORT,TRIG_PIN,GPIO_PIN_RESET);

    while(HAL_GPIO_ReadPin(ECHO_PORT,ECHO_PIN)==GPIO_PIN_RESET);
    start = __HAL_TIM_GET_COUNTER(HCSR04_TIM);

    while(HAL_GPIO_ReadPin(ECHO_PORT,ECHO_PIN)==GPIO_PIN_SET);
    stop = __HAL_TIM_GET_COUNTER(HCSR04_TIM);

    uint32_t diff = stop - start;

    float distance = (diff * 0.0343f)/2.0f;

    return distance;
}
