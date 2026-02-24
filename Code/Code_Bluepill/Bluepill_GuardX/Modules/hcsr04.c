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

/* Microsecond delay using timer */
static void Delay_us(uint16_t us)
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
    uint32_t start=0, stop=0;
    uint32_t timeout;

    /* Trigger pulse */
    HAL_GPIO_WritePin(TRIG_PORT,TRIG_PIN,GPIO_PIN_RESET);
    Delay_us(2);

    HAL_GPIO_WritePin(TRIG_PORT,TRIG_PIN,GPIO_PIN_SET);
    Delay_us(10);
    HAL_GPIO_WritePin(TRIG_PORT,TRIG_PIN,GPIO_PIN_RESET);

    __HAL_TIM_SET_COUNTER(HCSR04_TIM,0);
    timeout = __HAL_TIM_GET_COUNTER(HCSR04_TIM);

    /* Wait rising edge */
    while(HAL_GPIO_ReadPin(ECHO_PORT,ECHO_PIN)==GPIO_PIN_RESET)
    {
        if((__HAL_TIM_GET_COUNTER(HCSR04_TIM)-timeout) > 60000)
            return -1.0f;
    }

    start = __HAL_TIM_GET_COUNTER(HCSR04_TIM);

    /* Wait falling edge */
    while(HAL_GPIO_ReadPin(ECHO_PORT,ECHO_PIN)==GPIO_PIN_SET)
    {
        if((__HAL_TIM_GET_COUNTER(HCSR04_TIM)-start) > 60000)
            return -1.0f;
    }

    stop = __HAL_TIM_GET_COUNTER(HCSR04_TIM);

    uint32_t diff;

    if(stop >= start)
        diff = stop - start;
    else
        diff = (0xFFFF - start + 1) + stop;

    float distance = (diff * 0.0343f) * 0.5f;

    return distance;
}
