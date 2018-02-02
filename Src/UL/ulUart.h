/*
 * ulUart.h
 *
 *  Created on: 22 ???. 2018 ?.
 *      Author: oleh.plotnikov
 */

#ifndef UL_ULUART_H_
#define UL_ULUART_H_

#include "Utils/utils.h"

ERROR_T ulUart_Init();
ERROR_T ulUart_SendMessage();
ERROR_T ulUart_ReadMessage(char* msg, uint16_t len);
ERROR_T ulUart_Run();

#endif /* UL_ULUART_H_ */
