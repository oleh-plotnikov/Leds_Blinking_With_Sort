/*
 * LedDrv.c
 *
 *  Created on: 20.
 *      Author: oleh.plotnikov
 */
#include "LedDrv.h"


void LedDrv_Pin_Init(LedDrv_Param_T ledDrvStruct)
{
	 GPIO_InitTypeDef GPIO_InitStruct;

	 __HAL_RCC_GPIOD_CLK_ENABLE();
	 HAL_GPIO_WritePin(ledDrvStruct.gpio_port, ledDrvStruct.gpio_pin, GPIO_PIN_RESET);

	 GPIO_InitStruct.Pin = ledDrvStruct.gpio_pin;
	 GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	 GPIO_InitStruct.Pull = GPIO_NOPULL;
	 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	 HAL_GPIO_Init(ledDrvStruct.gpio_port, &GPIO_InitStruct);
}

void LedDrv_Set(LedDrv_Param_T ledDrvStruct)
{
	HAL_GPIO_WritePin(ledDrvStruct.gpio_port, ledDrvStruct.gpio_pin, LED_ON);
}

void LedDrv_Reset(LedDrv_Param_T ledDrvStruct)
{
	HAL_GPIO_WritePin(ledDrvStruct.gpio_port, ledDrvStruct.gpio_pin, LED_OFF);
}

void LedDrv_Toggle(LedDrv_Param_T ledDrvStruct)
{
	HAL_GPIO_TogglePin(ledDrvStruct.gpio_port, ledDrvStruct.gpio_pin);
}
