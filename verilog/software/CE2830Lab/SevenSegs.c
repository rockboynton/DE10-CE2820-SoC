/*
 * SevenSegs.c
 *
 *  Created on: Mar 9, 2019
 *      Author: schillingdl
 */
#include "alt_types.h"
#include "SevenSegs.h"
#include <stdio.h>

void clearSevenSegs(){
	*HEX0HEX3 = 0;
    *HEX4HEX5 = 0;
}

char ASCII_to_7Seg(char c){
	if(c != 0){
		c -= 0x30;
	}
	char HEXMap[10] = {0b0111111,
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

void num_to_7Seg(alt_u16 num){
	char BCDOut[6] = {0};
	sprintf(BCDOut, "%d", (num>9999 ? 9999 : num));
	alt_u32 HexOut = 0;
	for(int i = 0; i <= 3; i++){
		if(BCDOut[i] != 0){
			HexOut = HexOut << 8;
			HexOut |= ASCII_to_7Seg(BCDOut[i]);
		}
	}
	*HEX0HEX3 = HexOut;
}
