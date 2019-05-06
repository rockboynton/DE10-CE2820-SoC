/*
 * camera.c
 *
 *  Created on: Apr 29, 2019
 *      Author: boyntonrl
 */

#include "camera.h"
/*
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
	//camera->TFR_CMD |= 1<<9;
	//wait for transmit ready
	while(!(camera->ISR&0b1 == 1)){};
	//assert write ID and start bit
	camera->TFR_CMD = (0x42) | (1<<9);
	//wait for transmit ready
	while(!(camera->ISR&0b1 == 1)){};
	//specify address (shift for write bit)
	camera->TFR_CMD = addr<<1;
	//wait for transmit ready
	while(!(camera->ISR&0b1 == 1)){};
	//actually write data (shift for write bit) and asset stop bit
	camera->TFR_CMD = (data<<1) | (1<<8);
	//stop transmit
	//camera->TFR_CMD |= 1<<8;


}

alt_u8 cam_read_data(int addr){
	//assert start bit
	//camera->TFR_CMD |= 1<<9;
	//wait for transmit ready
	while(!(camera->ISR&0b1 == 1)){};
	//assert write ID and start bit
	camera->TFR_CMD = (0x42) | (1<<9);
	//wait for transmit ready
	while(!(camera->ISR&0b1 == 1)){};
	//specify address (shift for write bit) and assert repeated start
	camera->TFR_CMD = (addr<<1) | (1<<9);
	//stop transmit
	//camera->TFR_CMD |= 1<<8;
	//do i need to restart transmit here? doc's just stay stop
	//camera->TFR_CMD |= 1<<9;
	//wait for transmit ready
	while(!(camera->ISR&0b1 == 1)){};
	//assert read ID
	camera->TFR_CMD = 0x43;
	//wait for receive ready
	while(!(camera->ISR&2 == 2)){};
	//read and return
	alt_u8 ret = (camera->RX_DATA&0xFF);
	//stop transmit
	camera->TFR_CMD |= 1<<8;
	return ret;

}
*/

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "system.h"
#include <altera_avalon_pio_regs.h>
#include <altera_avalon_i2c.h>
#include <priv/alt_busy_sleep.h>


ALT_AVALON_I2C_DEV_t *i2c_dev;  //pointer to instance structure



int cam_write(uint8_t reg, uint8_t data)
{
	int status;
	uint8_t txbuf[2];
	txbuf[0]=reg;
	txbuf[1]=data;

	status=alt_avalon_i2c_master_tx(i2c_dev,txbuf, 2, ALT_AVALON_I2C_NO_INTERRUPTS);
	if (status!=ALT_AVALON_I2C_SUCCESS) return 1; //FAIL
	return 0;
}


int cam_read(uint8_t reg, uint8_t* data)
{
	int status;
	status = alt_avalon_i2c_master_tx(i2c_dev, &reg, 1, ALT_AVALON_I2C_NO_INTERRUPTS);
	if (status!=ALT_AVALON_I2C_SUCCESS) return 1; //FAIL
	status = alt_avalon_i2c_master_rx(i2c_dev, data, 1, ALT_AVALON_I2C_NO_INTERRUPTS);
	//status=alt_avalon_i2c_master_tx_rx(i2c_dev, &reg, 1, data, 1, ALT_AVALON_I2C_NO_INTERRUPTS);
	if (status!=ALT_AVALON_I2C_SUCCESS) return 2; //FAIL
	return 0;
}


int cam_init()
{

  //get a pointer to the avalon i2c instance
  i2c_dev = alt_avalon_i2c_open("/dev/camera_i2c");
  if (NULL==i2c_dev)
  {
      printf("Error: Cannot find /dev/camera_i2c\n");
      return 1;
  }

  //set the address of the device using

  alt_avalon_i2c_master_target_set(i2c_dev,0x21);

  // should be a delay here to wait for reset to complete

  return 0;
}

int cam_dump()
{
	uint8_t data;

	for(int i=1;i<50;i++)
	{
		if (!cam_read(i,&data))
		{
			printf("Reg: %d, Value: %d\n",i,data);
		}
		else
		{
			printf("read failed: %d\n",i);
		}

		alt_busy_sleep(100);
	}
	return 0;
}


//volatile uint16_t * camcam = 0xFF200100;
volatile short * pixel_buffer = (short *) 0x01000000; // Pixel buffer

#define PCLK 0x100
#define HREF 0x200
#define VSYNCH 0x400

void interactCamera()
{
  printf("Hello from Nios II!\n");

  // reset Camera
  printf("Reset Camera\n");
  IOWR_ALTERA_AVALON_PIO_DATA(ARDUINO_RESET_N_BASE, 0X00);
  usleep(1000000);
  IOWR_ALTERA_AVALON_PIO_DATA(ARDUINO_RESET_N_BASE, 0X01);
  usleep(100000);
  printf("Init I2C\n");
  cam_init();
  printf("Dump\n");
  cam_dump();
//  cam_write_2();
  printf("Write 1\n");

//  cam_write_1();

  char burn;
  char cmd = 'n';
  int reg = 0;
  int val = 0;

  int retval;

  while(1)
  {
    printf(">");
	scanf("%c", &cmd);

	if(cmd == 'w' || cmd == 'r')
	{
		scanf("%x", &reg);
	}
	if (cmd == 'w')
	{
		scanf("%x", &val);
	}
	scanf("%c", &burn);

	printf("Command: %c\n",cmd);

	if(cmd == 'w')
	{
		retval = cam_write(reg, val);
		if (retval)
		{
			printf("Cam Write failed: %d\n", retval);
		}
		retval = cam_read(reg,&val);
		if (retval)
		{
			printf("Cam Readback failed: %d\n", retval);
		}
		printf("Register %#X is now: %#X\n",reg,val);
	}
	else if(cmd == 'r')
	{
		retval = cam_read(reg,&val);
		if (retval)
		{
			printf("Cam Read failed: %d\n", retval);
		}
		printf("Register %#X is: %#X\n",reg,val);
	}

  }
}
