/*
 * ulUart.h
 *
 */
#ifndef UL_ULUART_H_
#define UL_ULUART_H_

#include "Utils/utils.h"
#include "main.h"

#define MAXLENRX 	19
#define MAXLENTX 	19
#define MIN_PERIOD 	100
#define MAX_PERIOD 	5000
#define CMDLENTH	32


ERROR_T ulUart_Init();
ERROR_T ulUart_Run();
ERROR_T ulUart_SendMessage(char* msg);
ERROR_T ulUart_ReadMessage(char* msg, uint16_t len);
BOOL ulUart_NewPeriodDetected(void);
uint16_t ulUart_ReadPeriod(void);

#endif /* UL_ULUART_H_ */
