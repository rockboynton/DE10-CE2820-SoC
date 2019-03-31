/*
 * CommonRegisters.h
 *
 *  Created on: Mar 30, 2019
 *      Author: schillingdl
 */

#ifndef COMMONREGISTERS_H_
#define COMMONREGISTERS_H_
#include "system.h"
#include "alt_types.h"

volatile alt_u16* leds = (alt_u16*) LEDS_BASE;
volatile alt_u8* pushbuttons = (alt_u8*) PUSHBUTTONS_BASE;
volatile alt_u16* slideSwitches = (alt_u16*) 0xFF200040;


#endif /* COMMONREGISTERS_H_ */
