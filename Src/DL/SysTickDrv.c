/*
 * SysTickDrv.c
 *
 */
#include "SysTickDrv.h"

static uint8_t	isInit = 0;


void SysTickDrv_Init()
{
	 isInit = 1;
}

uint32_t SysTickDrv_GetTime()
{
	assert_param(isInit == 1);
	return  HAL_GetTick();
}

BOOL SysTickDrv_IsTimePassed(uint32_t savedTime, uint32_t period)
{
	assert_param(isInit == 1);

	if ((HAL_GetTick() - savedTime) >= period)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
