/*
 * ulUart.c
 *
 *  Created on: 22 ???. 2018 ?.
 *      Author: oleh.plotnikov
 */

#include "ulUart.h"
#include "DL/UartDrv.h"
#include "stdlib.h"
#include "ctype.h"

#define MAXLENRX 19
#define MAXLENTX 19
#define MIN_PERIOD 100
#define MAX_PERIOD 5000

static BOOL ulUart_ParseMsg(void);

static char rxBuffer[MAXLENRX];
//static char txBuffer[MAXLENTX];

UART_HandleTypeDef huart2;
BOOL UartReady;
BOOL NewDataReady;
BOOL NewPeriodReady;

typedef struct{
	char 		cmd[32];
	uint16_t 	num;
}msg_t;

msg_t message;


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	UartReady = SET;
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	NewDataReady = SET;
}


ERROR_T ulUart_Init()
{

	ERROR_T error_status = ERROR_SUCCESS;
	UartDrv_Init();

	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_TC);

	NewDataReady = RESET;
	UartReady = SET;
	NewPeriodReady = RESET;

	return error_status;
}


ERROR_T ulUart_SendMessage(char* msg, uint16_t len)
{
	ERROR_T error_status = ERROR_SUCCESS;

	if(NULL == msg)
		error_status = ERROR_NULL;

	if(UartReady)
	{
		UartDrv_Write(&huart2, msg, len);
		UartReady = RESET;
		NewDataReady = RESET;
	}



	return error_status;
}


ERROR_T ulUart_ReadMessage(char* msg, uint16_t len)
{
	ERROR_T error_status = ERROR_SUCCESS;

	if(NULL == msg)
		error_status = ERROR_NULL;

	if(RESET == UartDrv_Read(&huart2, (uint8_t*)msg, len))
		error_status = ERROR_EMPTYMSG;

	return error_status;
}


static BOOL ulUart_ParseMsg(void)
{
	BOOL status = RESET;

	volatile uint16_t i = 0;

	char cmd[] = "change period";

	uint16_t cmdlen = strlen(cmd);

	int rescmp = strncmp(rxBuffer, cmd, cmdlen);

	if(rescmp == RESET)
	{
		i = cmdlen;
		if(RESET !=(message.num = atoi((char*)&rxBuffer[i])))
			status = SET;
	}

	return status;
}


BOOL ulUart_NewPeriodDetected(void)
{
	BOOL status = RESET;
	if(NewPeriodReady)
		if(message.num >= MIN_PERIOD && message.num <= MAX_PERIOD)
		{
			status = SET;
			NewPeriodReady = RESET;
		}

	return status;
}

uint16_t ulUart_ReadPeriod(void)
{
	return message.num;
}


ERROR_T ulUart_Run()
{
	if(SET == UartReady)
	{
		if(SET == NewDataReady)
		{
			if(ulUart_ParseMsg())
			{
				NewDataReady = RESET;
				NewPeriodReady = SET;
			}
		}
		ulUart_ReadMessage(rxBuffer, (uint16_t)MAXLENRX);
	}

	return ERROR_SUCCESS;
}


ERROR_T ulUart_Stop(void)
{

	UartDrv_DeInit(&huart2);

	return ERROR_SUCCESS;
}

