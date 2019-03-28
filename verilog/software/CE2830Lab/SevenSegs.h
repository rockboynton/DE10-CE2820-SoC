/*
 * SevenSegs.h
 *
 *  Created on: Mar 9, 2019
 *      Author: schillingdl
 */

#ifndef SEVENSEGS_H_
#define SEVENSEGS_H_

#include "alt_types.h"

/*
 * Converts the ASCII numbers to 7 segment readable numbers.
 * DOES NOT mask of the range that is inclusive of numbers only.
 * Takes ASCII char as argument
 * Returns 7 bit value to be set to the seven segment display.
 */
alt_u8 ASCII_to_7Seg(char c);

/*
 * Clears all seven segment displays to off
 */
void clearSevenSegs();



#endif /* SEVENSEGS_H_ */
