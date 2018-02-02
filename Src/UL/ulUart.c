/*
 * ulUart.c
 *
 *  Created on: 22 ???. 2018 ?.
 *      Author: oleh.plotnikov
 */

#include "ulUart.h"
#include "DL/UartDrv.h"

#define MAXLENRX 16
#define MAXLENTX 16

#define MAXLEN 9


static char rxBuffer[MAXLENRX];
static char txBuffer[MAXLENTX];

UART_HandleTypeDef huart2;

ERROR_T ulUart_Init()
{

	ERROR_T error_status = ERROR_SUCCESS;
	UartDrv_Init();

	return error_status;
}

ERROR_T ulUart_SendMessage(char* msg)
{
	ERROR_T error_status = ERROR_SUCCESS;

	if(NULL == msg)
		error_status = ERROR_NULL;

	UartDrv_Write(&huart2, msg);

	return error_status;
}

ERROR_T ulUart_ParseMsg()
{
	ERROR_T error_status = ERROR_SUCCESS;


	return error_status;
}

ERROR_T ulUart_ReadMessage(char* msg, uint16_t len)
{
	ERROR_T error_status = ERROR_SUCCESS;

	if(NULL == msg)
		error_status = ERROR_NULL;

	if(UartDrv_Read(&huart2, (uint8_t*)msg, len) == 0)
		error_status = ERROR_EMPTYMSG;

	return error_status;
}

char message[100];

ERROR_T ulUart_Run()
{
	ulUart_ReadMessage(rxBuffer, (uint16_t)MAXLENRX);

	if(0 == huart2.RxXferCount)
		ulUart_SendMessage(rxBuffer);

	return ERROR_SUCCESS;
}
