/*
 * utils.h
 *
 *  Created on: 18 ???. 2018 ?.
 *      Author: oleh.plotnikov
 */

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include "stdint.h"

typedef enum {
	ERROR_SUCCESS 	= 0,
	ERROR_NULL 		= 1,
	ERROR_BADSTATE 	= 2,
	ERROR_EMPTYMSG  = 3,
	ERROR_UART		= 4
}ERROR_T;

uint32_t GetSysTickInterval(uint32_t first_time, uint32_t second_time);

#endif /* UTILS_UTILS_H_ */
