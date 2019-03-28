/**
 * adc.c
 *
 *  Created on: Mar 28, 2019
 *      Authors: schillingdl, boyntonrl
 *
 * Implements functions specified in adc.h to use the DE10-CE2820 SoC
 * Analog-to-Digital Converters
 */

 #include "adc.h"

// static volatile alt_u32* sequencerCmd = (alt_u32*) ADC_SEQUENCER_BASE;
// static volatile *ADC_SAMPLE_STORE samples = ADC_SAMPLE_STORE_BASE;
//
//void adc_init(){
//
//}
//
// alt_u16 read_channel1(){
//     alt_u16 data = samples.slot1;
//     data &= 0xFFF;
//     return data;
// }
//
// alt_u16 read_channel2(){
//     alt_u16 data = samples.slot2;
//     data &= 0xFFF;
//     return data;
// }
