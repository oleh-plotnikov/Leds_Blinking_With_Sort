/*
 * ulBtnRead.c
 *
 */
#include "DL/BtnDrv.h"
#include "DL/SysTickDrv.h"
#include "Utils/utils.h"
#include "UL/ulButton.h"

typedef struct{
	BtnDrv_Param_T 		Btn_DrvPin;
	uint32_t 			Curr_Press_Time;
	uint32_t 			Curr_Release_Time;
	uint32_t			Period;
	BOOL				IsNewPeriod;
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
	BOOL period_status = FALSE;
	uint32_t period = ulButton_ReadPeriod();

	if(button_params.IsNewPeriod)
		if(MIN_PRESSED_PERIOD <= period && MAX_PRESSED_PERIOD >= period)
		{
			period_status = TRUE;
			button_params.IsNewPeriod = FALSE;
		}

	return period_status;
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
							button_params.IsNewPeriod = TRUE;
						}
						break;
		default:
						button_params.State_Btn = RELEASED;
						error_status = ERROR_BADSTATE;
						break;
	}

	return error_status;
}
