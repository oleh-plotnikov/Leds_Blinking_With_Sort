/*
 * utils.c
 *
 *  Created on: 18 ???. 2018 ?.
 *      Author: oleh.plotnikov
 */

#include <stdlib.h>
#include <stdint.h>

uint32_t GetSysTickInterval(uint32_t first_time, uint32_t second_time){
	return abs(first_time - second_time);;
}
