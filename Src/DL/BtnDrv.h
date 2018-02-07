/*
 * BtnDrv.h
 *
 */
#ifndef DL_BTNDRV_H_
#define DL_BTNDRV_H_

#include "stm32f4xx_hal.h"

typedef struct{
	uint32_t gpio_pin;
	GPIO_TypeDef* gpio_port;
} BtnDrv_Param_T;

void BtnDrv_Init(BtnDrv_Param_T btnDrvStruct);
BOOL BtnDrv_Is_Pressed(BtnDrv_Param_T btnDrvStruct);

#endif /* DL_BTNDRV_H_ */
