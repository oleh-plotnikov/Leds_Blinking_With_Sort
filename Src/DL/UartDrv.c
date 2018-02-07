/*
 * UartDrv.c
 *
 */
#include "DL/UartDrv.h"

ERROR_T UartDrv_Read(UART_HandleTypeDef* uartHandle, uint8_t* msg, uint16_t len)
{
	ERROR_T status = ERROR_SUCCESS;
	if(HAL_OK != HAL_UART_Receive_IT(uartHandle, (uint8_t*)msg, len))
		status = ERROR_UART;

	return status;
}

ERROR_T UartDrv_Write(UART_HandleTypeDef* uartHandle, char* str, uint16_t len)
{
	ERROR_T status = ERROR_SUCCESS;

	if(HAL_OK != HAL_UART_Transmit_IT(uartHandle, (uint8_t*)str, len))
		status = ERROR_UART;

	return status;
}

ERROR_T UartDrv_Init(UART_HandleTypeDef* huart)
{
	ERROR_T status = ERROR_SUCCESS;

	huart->Instance = USART2;
	huart->Init.BaudRate = 115200;
	huart->Init.WordLength = UART_WORDLENGTH_8B;
	huart->Init.StopBits = UART_STOPBITS_1;
	huart->Init.Parity = UART_PARITY_NONE;
	huart->Init.Mode = UART_MODE_TX_RX;
	huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart->Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_OK != HAL_UART_Init(huart))
		status = ERROR_UART;

	return status;
}


void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(uartHandle->Instance==USART2)
  {
    __HAL_RCC_USART2_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  }
}

ERROR_T UartDrv_DeInit(UART_HandleTypeDef* uartHandle)
{
	ERROR_T status = ERROR_SUCCESS;

	if (NULL == uartHandle)
		status = ERROR_NULL;

	if(uartHandle->Instance==USART2)
	{
		__HAL_RCC_USART2_CLK_DISABLE();
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);
		HAL_NVIC_DisableIRQ(USART2_IRQn);
	}

	return status;
}

ERROR_T UartDrv_IRQHandler(UART_HandleTypeDef* uartHandle)
{
	ERROR_T status = ERROR_SUCCESS;

	if (NULL == uartHandle)
		status = ERROR_NULL;

	HAL_UART_IRQHandler(uartHandle);
	return status;
}
