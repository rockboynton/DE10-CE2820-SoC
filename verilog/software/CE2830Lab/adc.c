/**
 * adc.c
 *
 *  Created on: Mar 28, 2019
 *      Authors: schillingdl, boyntonrl
 *
 * Implements functions specified in adc.h to use the DE10-CE2820 SoC
 * Analog-to-Digital Converters to control a joystick
 */

#include "adc.h"

static volatile ADC_SAMPLE_STORE* samples = (alt_u32*) ADC_SAMPLE_STORE_BASE;

void adc_init() {
	alt_u32 data = *sequencerCmd;
	data = (data&0xF) | 0b0001;
	*sequencerCmd = data;
}

alt_u16 read_channel1() {
    alt_u32 data = samples->slot0;
    data &= 0xFFF;
    return data;
}

alt_u16 read_channel2() {
    alt_u32 data = samples->slot1;
    data &= 0xFFF;
    return data;
}

void read_joystick() {
	servo_setAngle(SERVO_Y, (alt_8) (read_channel1() / 3800.0 * 90 - 45));
	servo_setAngle(SERVO_X, (alt_8) (read_channel2() / 3800.0 * 90 - 45));
}
