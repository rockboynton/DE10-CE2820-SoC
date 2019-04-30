/*
 * camera.c
 *
 *  Created on: Apr 29, 2019
 *      Author: boyntonrl
 */

#include "camera.h"

static volatile CAMERA* camera = (alt_u32*) CAM_BASE;

void cam_init() {
    // TODO
	//turn disable peripheral core
	camera->CTRL &= 0xFFFFFFFE;
	//set to standard transfer mode
	camera->CTRL &= 0xFFFFFFFD;
	//enable rx and tx interrupts
	camera->ISER |= 0x3;
	//enable peripheral core
	camera->CTRL |= 0b1;
}

void cam_setReg(alt_u32* cmd) {
    // TODO
}

alt_u32 cam_getReg() {
    // TODO
    return 0;
}

void cam_write_data(int addr, int data){
	//assert start bit
	camera->TFR_CMD |= 1<<9;
	//wait for transmit ready
	while(!(camera->ISR&0b1 == 1)){};
	//assert write ID
	camera->TFR_CMD = 42;
	//wait for transmit ready
	while(!(camera->ISR&0b1 == 1)){};
	//specify address (shift for write bit)
	camera->TFR_CMD = addr<<1;
	//wait for transmit ready
	while(!(camera->ISR&0b1 == 1)){};
	//actually write data (shift for write bit)
	camera->TFR_CMD = data<<1;
	//stop transmit
	camera->TFR_CMD |= 1<<8;


}

alt_u8 cam_read_data(int addr){
	//assert start bit
	camera->TFR_CMD |= 1<<9;
	//wait for transmit ready
	while(!(camera->ISR&0b1 == 1)){};
	//assert write ID
	camera->TFR_CMD = 42;
	//wait for transmit ready
	while(!(camera->ISR&0b1 == 1)){};
	//specify address (shift for write bit)
	camera->TFR_CMD = addr<<1;
	//stop transmit
	//camera->TFR_CMD |= 1<<8;
	//do i need to restart transmit here? doc's just stay stop
	camera->TFR_CMD |= 1<<9;
	//wait for transmit ready
	while(!(camera->ISR&0b1 == 1)){};
	//assert read ID
	camera->TFR_CMD = 43;
	//wait for receive ready
	while(!(camera->ISR&2 == 2)){};
	//read and return
	alt_u8 ret = camera->RX_DATA&0xFF;
	//stop transmit
	camera->TFR_CMD |= 1<<8;
	return ret;

}
