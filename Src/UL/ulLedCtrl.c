#include "DL/LedDrv.h"
#include "DL/SysTickDrv.h"
#include "UL/ulLedCtrl.h"
#include <stdlib.h>

#define DEFAULT_PERIOD 5000

typedef struct{
	leds_t	 		Led_Pins;
	LedDrv_Param_T 	Led_DrvPin;
	uint32_t 		Led_Period;
	uint32_t 		Led_State;
	uint32_t 		Led_Time;
}ulLedCtrl_params_t;

static int comp (const void * elem1, const void * elem2);
static void ulLedCtrl_Sort_Periods();

static ulLedCtrl_params_t 	leds_params  [NUMBERS_LED];

void ulLedCtrl_Init(void)
{
	leds_t led;

	led = R_LED;
	leds_params[led].Led_DrvPin.gpio_pin = R_LED_Pin;
	leds_params[led].Led_DrvPin.gpio_port = R_LED_GPIO_Port;

	led = G_LED;
	leds_params[led].Led_DrvPin.gpio_pin = G_LED_Pin;
	leds_params[led].Led_DrvPin.gpio_port = G_LED_GPIO_Port;

	led = B_LED;
	leds_params[led].Led_DrvPin.gpio_pin = B_LED_Pin;
	leds_params[led].Led_DrvPin.gpio_port = B_LED_GPIO_Port;

	led = O_LED;
	leds_params[led].Led_DrvPin.gpio_pin = O_LED_Pin;
	leds_params[led].Led_DrvPin.gpio_port = O_LED_GPIO_Port;

	for(int i=0; i < NUMBERS_LED; i++)
	{
		leds_params[i].Led_Period = DEFAULT_PERIOD;
		leds_params[i].Led_State = LED_OFF;
		leds_params[i].Led_Time = 0;
		LedDrv_Pin_Init (leds_params[i].Led_DrvPin);
		LedDrv_Set(leds_params[i].Led_DrvPin);
	}
}


ERROR_T ulLedCtrl_Run()
{
	ERROR_T error_status = ERROR_SUCCESS;

	static int i=0;

	if(SysTickDrv_IsTimePassed(leds_params[i].Led_Time, leds_params[i].Led_Period))
	{
		if(leds_params[i].Led_State == LED_ON)
		{
			LedDrv_Reset(leds_params[i].Led_DrvPin);
			leds_params[i].Led_State = LED_OFF;
		}
		else
		{
			LedDrv_Set(leds_params[i].Led_DrvPin);
			leds_params[i].Led_State = LED_ON;
		}

		leds_params[i].Led_Time = SysTickDrv_GetTime();
	}
	i++;
	if (i>=NUMBERS_LED)
	{
		i=0;
	}

	return error_status;
}

void ulLedCtrl_SetPeriod(uint16_t period)
{
	leds_params[NUMBERS_LED - 1].Led_Period = period;
	ulLedCtrl_Sort_Periods();
}

static void ulLedCtrl_Sort_Periods(){
	qsort(&leds_params, NUMBERS_LED, sizeof(ulLedCtrl_params_t), comp);
}

static int comp (const void * elem1, const void * elem2)
{
    return ((ulLedCtrl_params_t*)elem1)->Led_Period - ((ulLedCtrl_params_t*)elem2)->Led_Period;
}
