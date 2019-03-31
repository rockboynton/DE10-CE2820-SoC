/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include "system.h"
#include "alt_types.h"
#include "SevenSegs.h"
#include "delay.h"
#include "ServoAPI.h"
#include "adc.h"
#include "CommonRegisters.h"


int main(){
  printf("Welcome to the test display!\n");
  //clear on boot up
  clearSevenSegs();
  //initalize ADC
  adc_init();

  //main loop
  while(1){

	  //printf("X: %d\n", read_channel1());
	  //printf("Y: %d\n", read_channel2());

	  //determine if switch 0 is on or off. if on display channel 1
	  //else if off, display channel 2 on the hex display
	  if(((*slideSwitches)&1) == 1){
		  *HEX4HEX5 = (*HEX4HEX5&0x0000)|(ASCII_to_7Seg('1')<< 8);
		  num_to_7Seg(read_channel1());
	  } else {
		  *HEX4HEX5 = (*HEX4HEX5&0x0000)|(ASCII_to_7Seg('0')<< 8);
		  num_to_7Seg(read_channel2());
	  }
	  delay_1s(1);

  }
  return 0;
}


