/*
 * SysTickDrv.h
 *
 */
#ifndef DL_SYSTICKDRV_H_
#define DL_SYSTICKDRV_H_

#include "stm32f4xx_hal.h"

void SysTickDrv_Init();

uint32_t SysTickDrv_GetTime();

BOOL SysTickDrv_IsTimePassed(uint32_t savedTime, uint32_t period);

void SysTick_CallBack(void);

#endif /* DL_SYSTICKDRV_H_ */
