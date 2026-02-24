/*
 * esp01.c
 *
 *  Created on: Feb 22, 2026
 *      Author: Hariharan
 */

#include "esp01.h"
#include "motor.h"
#include <stdio.h>
#include <string.h>

static UART_HandleTypeDef *espUart;

static char cmdBuf[32];
static uint8_t idx = 0;

static int joyX = 512;
static int joyY = 512;


void ESP01_Init(UART_HandleTypeDef *huart)
{
    espUart = huart;
}

void ESP01_Decode(uint8_t c)
{
    if(c=='\n' || c=='\r')
    {
        cmdBuf[idx]=0;
        // Joystick
        if(strncmp(cmdBuf,"J:",2)==0)
        {
            sscanf(cmdBuf,"J:%d,%d",&joyX,&joyY);
            Motor_UpdateJoystick(joyX,joyY);
        }
        // Speed Slider
        if(strncmp(cmdBuf,"S:",2)==0)
		{
		   int spd;
		   sscanf(cmdBuf,"S:%d",&spd);
		   Motor_SetSpeed(spd);
		}

        idx=0;
    }
    else
    {
        if(idx<sizeof(cmdBuf)-1)
            cmdBuf[idx++]=c;
    }
}
