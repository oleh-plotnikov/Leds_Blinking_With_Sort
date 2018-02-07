/*
 * ulLedCtrl.h
 *
 */
#ifndef UL_ULLEDCTRL_H_
#define UL_ULLEDCTRL_H_

#include "Utils/utils.h"

#define DEFAULT_PERIOD 5000

typedef enum{
	R_LED = 0,
	G_LED,
	B_LED,
	O_LED,
	NUMBERS_LED
} leds_t;

void ulLedCtrl_Init(void);
void ulLedCtrl_SetPeriod(uint16_t period);
ERROR_T ulLedCtrl_Run();

#endif /* UL_ULLEDCTRL_H_ */
