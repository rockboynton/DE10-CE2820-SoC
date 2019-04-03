/**
 * adc.h
 *
 *  Created on: Mar 28, 2019
 *      Authors: schillingdl, boyntonrl
 *
 * API for interfacing with the DE10-CE2820 SoC Analog-to-Digital Converters to control
 * a joystick
 */
#ifndef ADC_H_
#define ADC_H_

#include "alt_types.h"
#include "system.h"
#include "ServoAPI.h"

#define ADC_SEQUENCER_BASE 0xff200210
#define ADC_SAMPLE_STORE_BASE 0xff200400


typedef struct{
	alt_u32 slot0;
	alt_u32 slot1;
	alt_u32 slot2;
} ADC_SAMPLE_STORE;

/**
 * Initialize the ADC to continuous mode
 * and turns the sequencer on.
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

/**
 * Reads the current joystick position and sets the servo position via dirrect mapping
 */
void read_joystick();

#endif /* ADC_H_ */
