/**
 * Main program
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
#include "accelerometer.h"
#include "camera.h"

/**
 * 0: main program
 * 1: display hex values
 * 2: move servos
 */
#define DEBUG 2


int main(){
  printf("Welcome to the test display!\n");
  //clear on boot up
  clearSevenSegs();
  //initalize ADC
  adc_init();
  cam_init();
  cam_write_data(0x01,0x40);

  //main loop
  while(1){

	//determine if switch 0 is on or off. if on display channel 1
	//else if off, display channel 2 on the hex display
	while (DEBUG == 2) {
		if(((*slideSwitches)&1) == 1){
			*HEX4HEX5 = (*HEX4HEX5&0x0000)|(ASCII_to_7Seg('1')<< 8);
			num_to_7Seg(read_channel1());
		} else {
			*HEX4HEX5 = (*HEX4HEX5&0x0000)|(ASCII_to_7Seg('0')<< 8);
			num_to_7Seg(read_channel2());
		}
		//read_joystick();
		acc_steady_servo();
		//printf("X: %d\n", acc_read_x());
		//printf("Y: %d\n", acc_read_y());
		//printf("Z: %d\n", acc_read_z());
		printf("camera blue gain: %d\n", cam_read_data(0x01));
		printf("\n");
		delay_1ms(200);
	}
  }
  return 0;
}


