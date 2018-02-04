#ifndef DL_UARTDRV_H_
#define DL_UARTDRV_H_
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

extern void _Error_Handler(char *, int);

void UartDrv_Run(void);
void UartDrv_Init(void);
void UartDrv_DeInit(UART_HandleTypeDef* uartHandle);
int16_t UartDrv_Write(UART_HandleTypeDef* uartHandle, char* str, uint16_t len);
uint16_t UartDrv_Read(UART_HandleTypeDef* uartHandle, uint8_t* msg, uint16_t len);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /* DL_UARTDRV_H_ */
