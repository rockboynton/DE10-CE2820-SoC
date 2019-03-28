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

int main()
{
  printf("Welcome to the 7-Seg Switch Display!\n");

  alt_u16* leds = (alt_u16*) LEDS_BASE;
  volatile alt_u8* pushbuttons = (alt_u8*) PUSHBUTTONS_BASE;
  alt_u32* HEX0HEX3 = (alt_u32*) 0xFF200020;
  alt_u32* HEX4HEX5 = (alt_u32*) 0xFF200030;
  volatile alt_u16* slideSwitches = (alt_u16*) 0xFF200040;

  char BCDOut[7] = {0};
  alt_u32 HexOut = 0;
  //clear on boot up
  clearSevenSegs();

  //main loop
  while(1){
	  servo_randomMovement(SERVO_Y);
	  servo_randomMovement(SERVO_X);
	  delay_1ms(50);

  }
  return 0;
}


