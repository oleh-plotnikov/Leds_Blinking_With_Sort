/*
 * ulBtnRead.h
 *
 */
#ifndef UL_ULBUTTON_H_
#define UL_ULBUTTON_H_

#define MIN_PRESSED_PERIOD 100
#define MAX_PRESSED_PERIOD 5000

typedef enum{
	RELEASED = 0,
	PRESSED  = 1
}ulButton_btnstate_t;

void ulButton_Init(void);
uint32_t ulButton_ReadPeriod(void);
BOOL ulButton_NewPeriodDetected(void);
ERROR_T ulButton_Run(void);

#endif /* UL_ULBUTTON_H_ */
