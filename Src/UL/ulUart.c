/*
 * ulUart.c
 *
 */

#include "ulUart.h"
#include "DL/UartDrv.h"
#include "stdlib.h"
#include "ctype.h"

static BOOL ulUart_ParseMsg(void);

char rxBuffer[MAXLENRX];
char txBuffer[MAXLENTX];

typedef struct{
	char 		cmd[CMDLENTH];
	uint16_t 	num;
}msg_t;

typedef struct{
	msg_t message;
	UART_HandleTypeDef huart;
	BOOL UartReady;
	BOOL NewDataReady;
	BOOL NewPeriodReady;
	char* rxBuffer;
	char* txBuffer;
}UART_ConfigTypedef;

UART_ConfigTypedef UartInst;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	UartInst.UartReady = SET;
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	UartInst.NewDataReady = SET;
}


ERROR_T ulUart_Init()
{

	ERROR_T error_status = ERROR_SUCCESS;
	UartDrv_Init(&UartInst.huart);

	__HAL_UART_ENABLE_IT(&UartInst.huart, UART_IT_RXNE);
	__HAL_UART_ENABLE_IT(&UartInst.huart, UART_IT_TC);

	UartInst.NewDataReady = RESET;
	UartInst.UartReady = SET;
	UartInst.NewPeriodReady = RESET;

	return error_status;
}


ERROR_T ulUart_SendMessage(char* msg)
{
	ERROR_T error_status = ERROR_SUCCESS;
	uint8_t len = strlen(msg);

	if(NULL == msg)
		error_status = ERROR_NULL;

	if(UartInst.UartReady)
	{
		UartDrv_Write(&UartInst.huart, msg, len);
		UartInst.UartReady = RESET;
		UartInst.NewDataReady = RESET;
	}



	return error_status;
}


ERROR_T ulUart_ReadMessage(char* msg, uint16_t len)
{
	ERROR_T error_status = ERROR_SUCCESS;

	if(NULL == msg)
		error_status = ERROR_NULL;

	if(ERROR_UART == UartDrv_Read(&UartInst.huart, (uint8_t*)msg, len))
		error_status = ERROR_UART;

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
		if(RESET !=(UartInst.message.num = atoi((char*)&rxBuffer[i])))
			status = SET;
	}

	return status;
}


BOOL ulUart_NewPeriodDetected(void)
{
	BOOL status = RESET;
	if(UartInst.NewPeriodReady)
	{
		if(UartInst.message.num < MIN_PERIOD)
		{
			ulUart_SendMessage("LED PERIOD IS TOO SMALL!!!\n");
		}
		else if(UartInst.message.num >= MAX_PERIOD)
		{
			ulUart_SendMessage("LED PERIOD IS TOO BIG!!!\n");
		}
		else
		{
			status = SET;
		}

		UartInst.NewPeriodReady = RESET;
	}

	return status;
}

uint16_t ulUart_ReadPeriod(void)
{
	return UartInst.message.num;
}


ERROR_T ulUart_Run()
{
	if(SET == UartInst.UartReady)
	{
		if(SET == UartInst.NewDataReady)
		{
			if(ulUart_ParseMsg())
			{
				UartInst.NewDataReady = RESET;
				UartInst.NewPeriodReady = SET;
			}
			else
			{
				ulUart_SendMessage("WRONG COMMAND!!!\n");
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

ERROR_T ulUart_IRQHandler(void)
{
	ERROR_T status = ERROR_SUCCESS;

	if(ERROR_SUCCESS != UartDrv_IRQHandler(&UartInst.huart))
		status = ERROR_UART;

	return status;
}
