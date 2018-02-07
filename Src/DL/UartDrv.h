/*
 * UartDrv.h
 *
 */
#ifndef DL_UARTDRV_H_
#define DL_UARTDRV_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "main.h"
#include "Utils/utils.h"

extern UART_HandleTypeDef huart2;

ERROR_T UartDrv_Init(UART_HandleTypeDef* huart2);
ERROR_T UartDrv_DeInit(UART_HandleTypeDef* uartHandle);
ERROR_T UartDrv_IRQHandler(UART_HandleTypeDef* uartHandle);
ERROR_T UartDrv_Write(UART_HandleTypeDef* uartHandle, char* str, uint16_t len);
ERROR_T UartDrv_Read(UART_HandleTypeDef* uartHandle, uint8_t* msg, uint16_t len);

#endif /* DL_UARTDRV_H_ */
