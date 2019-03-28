/**
 * adc.h
 *
 *  Created on: Mar 28, 2019
 *      Authors: schillingdl, boyntonrl
 *
 * API for interfacing with the DE10-CE2820 SoC Analog-to-Digital Converters
 */
#ifndef ADC_H_
#define ADC_H_
 
#include "alt_types.h"
#include "system.h"

/**
 * Initialize the ADC.
 * 
 */
void adc_init();

/**
 * Read channel 1
 * @return the value read from channel 1 (TODO-TODO)
 */ 
alt_u16 read_channel1();

/**
 * Read channel 2
 * @return the value read from channel 2 (TODO-TODO)
 */
alt_u16 read_channel2();

#endif /* ADC_H_ */
