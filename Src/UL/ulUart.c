/*
 * ulUart.c
 *
 *  Created on: 22 ???. 2018 ?.
 *      Author: oleh.plotnikov
 */

#include "ulUart.h"
#include "DL/UartDrv.h"

#define MAXLENRX 19
#define MAXLENTX 19

static BOOL ulUart_ParseMsg(void);

static char rxBuffer[MAXLENRX];
//static char txBuffer[MAXLENTX];

UART_HandleTypeDef huart2;
BOOL UartReady;
BOOL NewDataReady;

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

	char cmd[] = "change period 1000\n";
	while (i < MAXLENTX)
	{
		if(rxBuffer[i] == 'c')
		{
			int rescmp = strcmp(rxBuffer, cmd);
			if(rescmp == RESET)
			{
				status = SET;
				break;
			}else
			{
				i++;
			}
		}
	}

	return status;
}


ERROR_T ulUart_Run()
{

	if(SET == UartReady)
	{
		if(SET == NewDataReady)
		{
			if(ulUart_ParseMsg())
				ulUart_SendMessage(rxBuffer, (uint16_t)MAXLENRX);
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

