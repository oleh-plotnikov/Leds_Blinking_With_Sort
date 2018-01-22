/*
 * ulBtnRead.c
 *
 *  Created on: 20 ????. 2017 ?.
 *      Author: oleh.plotnikov
 */
#include "DL/BtnDrv.h"
#include "DL/SysTickDrv.h"
#include "Utils/utils.h"
#include "UL/ulButton.h"

#define MIN_PRESSED_PERIOD 1000
#define MAX_PRESSED_PERIOD 10000

typedef enum{
	RELEASED = 0,
	PRESSED  = 1
}ulButton_btnstate_t;

typedef struct{
	BtnDrv_Param_T 		Btn_DrvPin;
	uint32_t 			Curr_Press_Time;
	uint32_t 			Curr_Release_Time;
	uint32_t			Period;
	BOOL				New_Period;
	ulButton_btnstate_t State_Btn;
}ulButton_params_t;


ulButton_params_t button_params;


void ulButton_Init(void)
{
	button_params.Btn_DrvPin.gpio_port = BTN_GPIO_Port;
	button_params.Btn_DrvPin.gpio_pin = BTN_Pin;
	BtnDrv_Init(button_params.Btn_DrvPin);
	button_params.State_Btn = RELEASED;
	button_params.Curr_Press_Time = 0;
	button_params.Curr_Release_Time = 0;
	button_params.Period = MIN_PRESSED_PERIOD;
}


BOOL ulButton_NewPeriodDetected(void)
{
	BOOL status = FALSE;
	uint32_t period = ulButton_ReadPeriod();

	if(TRUE == button_params.New_Period)
		if(MIN_PRESSED_PERIOD <= period && MAX_PRESSED_PERIOD >= period)
			{
				status = TRUE;
				button_params.New_Period = FALSE;
			}

	return status;
}


uint32_t ulButton_ReadPeriod(void)
{
	return button_params.Period;
}


ERROR_T ulButton_Run(void)
{

	ERROR_T	error_status = ERROR_SUCCESS;

	switch(button_params.State_Btn)
	{
		case RELEASED:
						if(BtnDrv_Is_Pressed(button_params.Btn_DrvPin))
						{
							button_params.Curr_Press_Time = SysTickDrv_GetTime();
							button_params.State_Btn = PRESSED;
						}
						break;
		case PRESSED:
						if(!BtnDrv_Is_Pressed(button_params.Btn_DrvPin))
						{
							button_params.Curr_Release_Time = SysTickDrv_GetTime();
							button_params.State_Btn = RELEASED;
							button_params.Period = GetSysTickInterval(button_params.Curr_Press_Time, button_params.Curr_Release_Time);
							button_params.New_Period = TRUE;
						}
						break;
		default:
						button_params.State_Btn = RELEASED;
						error_status = ERROR_BADSTATE;
						break;
	}

	return error_status;
}
