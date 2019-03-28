/*
 * delay.c
 *
 *  Created on: Mar 21, 2019
 *      Author: schillingdl
 */
/*
 * delay.c
 *
 * Starter Code
 */

#include "alt_types.h"
#include "delay.h"  //include declaration header file

void delay_1s(alt_u32 n){
	int i = 500000*n;
	while(i>0){
		i--;
	}
}
void delay_1ms(alt_u32 n){
	int i = 500*n;
	while(i>0){
		i--;
	}
}


