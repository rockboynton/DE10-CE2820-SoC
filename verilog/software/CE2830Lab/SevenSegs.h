/**
 * SevenSegs.h
 *
 *  Created on: Mar 9, 2019
 *      Author: schillingdl
 */

#ifndef SEVENSEGS_H_
#define SEVENSEGS_H_

#include "alt_types.h"

  static volatile alt_u32* HEX0HEX3 = (alt_u32*) 0xFF200020;
  static volatile alt_u32* HEX4HEX5 = (alt_u32*) 0xFF200030;

/**
 * Converts the ASCII numbers to 7 segment readable numbers.
 * DOES NOT mask of the range that is inclusive of numbers only.
 * Takes ASCII char as argument
 * Returns 7 bit value to be set to the seven segment display.
 */
char ASCII_to_7Seg(char c);

/**
 * Clears all seven segment displays to off
 */
void clearSevenSegs();

/**
 * Displays a decimal number less than 9999 to the DE10 Hex display.
 * args: num - number less than 9999 that is to be displayed.
 * If number is greater than 9999, 9999 will be displayed.
 */
void num_to_7Seg(alt_u16 num);

#endif /* SEVENSEGS_H_ */
