/**
 * adc.c
 *
 *  Created on: Mar 28, 2019
 *      Authors: schillingdl, boyntonrl
 *
 * Implements functions specified in adc.h to use the DE10-CE2820 SoC
 * Analog-to-Digital Converters
 */

 #include "alt_types.h"
 #include "adc.h"

static volatile ADC_SAMPLE_STORE* samples = (alt_u32*) ADC_SAMPLE_STORE_BASE;

void adc_init(){

	alt_u32 data = *sequencerCmd;
	data = (data&0xF)|0b0001;
	*sequencerCmd = data;
}

 alt_u16 read_channel1(){
     alt_u32 data = samples->slot0;
     data &= 0xFFF;
     return data;
}

 alt_u16 read_channel2(){
     alt_u32 data = samples->slot1;
     data &= 0xFFF;
     return data;
}
