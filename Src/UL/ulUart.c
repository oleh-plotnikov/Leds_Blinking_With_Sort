/*
 * ulUart.c
 *
 *  Created on: 22 ???. 2018 ?.
 *      Author: oleh.plotnikov
 */

#include "ulUart.h"
#include "DL/UartDrv.h"

ERROR_T ulUart_Init(){
	ERROR_T error_status = ERROR_SUCCESS;
	UartDrv_Init();
	return error_status;
}
