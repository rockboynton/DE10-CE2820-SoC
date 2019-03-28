/*
 * SevenSegs.c
 *
 *  Created on: Mar 9, 2019
 *      Author: schillingdl
 */
#include "alt_types.h"
#include "SevenSegs.h"

alt_u32* HEX3dt0 = (alt_32*) 0xFF200020;
alt_u32* HEX4ut5 = (alt_32*) 0xFF200030;

alt_u8 ASCII_to_7Seg(char c){
	if(c != 0){
		c -= 0x30;
	}
	alt_u8 HEXMap[10] = {0b0111111,
			0b0000110,
			0b1011011,
			0b1001111,
			0b1100110,
			0b1101101,
			0b1111100,
			0b0000111,
			0b1111111,
			0b1100111};
	return HEXMap[c];
};

void clearSevenSegs(){
	*HEX3dt0 = 0;
    *HEX4ut5 = 0;
}

