/*
 * ulBtnRead.h
 *
 *  Created on: 20 ????. 2017 ?.
 *      Author: oleh.plotnikov
 */

#ifndef UL_ULBUTTON_H_
#define UL_ULBUTTON_H_

void ulButton_Init(void);
uint32_t ulButton_ReadPeriod(void);
BOOL ulButton_NewPeriodDetected(void);
ERROR_T ulButton_Run(void);

#endif /* UL_ULBUTTON_H_ */
