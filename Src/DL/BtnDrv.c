/*
 * BtnDrv.c
 *
 *  Created on: 27 ????. 2017 ?.
 *      Author: oleh.plotnikov
 */

#include "BtnDrv.h"

static BOOL BtnDrv_CheckDebouceBtn(BtnDrv_Param_T btnDrvStruct);

void BtnDrv_Init(BtnDrv_Param_T btnDrvStruct)
{
	 GPIO_InitTypeDef GPIO_InitStruct;

	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  GPIO_InitStruct.Pin = btnDrvStruct.gpio_pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(btnDrvStruct.gpio_port, &GPIO_InitStruct);
}

BOOL BtnDrv_Is_Pressed(BtnDrv_Param_T btnDrvStruct)
{
	return BtnDrv_CheckDebouceBtn(btnDrvStruct);
}

static BOOL BtnDrv_CheckDebouceBtn(BtnDrv_Param_T btnDrvStruct)
{
	uint8_t 	result 	 = 0;
	uint16_t	btncount = 0;

	while(GPIO_PIN_SET == HAL_GPIO_ReadPin(btnDrvStruct.gpio_port, btnDrvStruct.gpio_pin)){
		if(btncount < 10){
			btncount++;
		}
		else{
			result = 1;
			break;
		}
	}

	return result;
}
