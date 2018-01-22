/*
 * LedDrv.h
 *
 *  Created on: 2017.
 *      Author: oleh.plotnikov
 */

#ifndef DL_LEDDRV_H_
#define DL_LEDDRV_H_

#include "stm32f4xx_hal.h"

typedef struct{
	uint32_t gpio_pin;
	GPIO_TypeDef* gpio_port;
} LedDrv_Param_T;

void LedDrv_Pin_Init(LedDrv_Param_T ledDrvStruct);
void LedDrv_Set(LedDrv_Param_T ledDrvStruct);
void LedDrv_Reset(LedDrv_Param_T ledDrvStruct);
void LedDrv_Toggle(LedDrv_Param_T ledDrvStruct);

#endif /* DL_LEDDRV_H_ */
