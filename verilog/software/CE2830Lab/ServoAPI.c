/**
 * ServoAPI.c
 *
 *  Created on: Mar 25, 2019
 *      Authors: schillingdl, boyntonrl
 *
 * Implements functions specified in ServoAPI.h to use the DE10-CE2820 SoC 
 * servo controllers (SERVO_X and SERVO_Y)
 */

#include "ServoAPI.h"


bool servo_setAngle(SERVO servo, alt_8 angle){
	volatile alt_u32* addr = (alt_u32*) servo;
	if((angle > 45) || (angle < -45)){
		return false;
	} else {
		*addr = ((alt_u8) (((100/45)*angle)+100));
		return true;
	}
}

bool servo_center(SERVO servo){
	volatile alt_u32* addr = (alt_u32*) servo;
	*addr = 100;
	return true;
}

bool servo_pan(SERVO servo, alt_u32 speed, float cycles){
	volatile alt_u32* addr = (alt_u32*) servo;
	//TODO
	return false;
}

bool servo_randomMovement(SERVO servo){
	volatile alt_u32* addr = (alt_u32*) servo;
	srand(time(0));
	*addr = ((alt_u8)(rand()%200));
	return true;
}
