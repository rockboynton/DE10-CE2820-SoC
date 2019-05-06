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
#include <stdint.h>
#include <unistd.h>
#include "system.h"
#include <altera_avalon_pio_regs.h>
#include <altera_avalon_i2c.h>
#include <priv/alt_busy_sleep.h>
//#include <altera_up_avalon_video_pixel_buffer_dma.h>

#define REG_GAIN	0x00	/* Gain lower 8 bits (rest in vref) */
#define REG_BLUE	0x01	/* blue gain */
#define REG_RED		0x02	/* red gain */
#define REG_VREF	0x03	/* Pieces of GAIN, VSTART, VSTOP */
#define REG_COM1	0x04	/* Control 1 */
#define  COM1_CCIR656	  0x40  /* CCIR656 enable */
#define REG_BAVE	0x05	/* U/B Average level */
#define REG_GbAVE	0x06	/* Y/Gb Average level */
#define REG_AECHH	0x07	/* AEC MS 5 bits */
#define REG_RAVE	0x08	/* V/R Average level */
#define REG_COM2	0x09	/* Control 2 */
#define  COM2_SSLEEP	  0x10	/* Soft sleep mode */
#define REG_PID		0x0a	/* Product ID MSB */
#define REG_VER		0x0b	/* Product ID LSB */
#define REG_COM3	0x0c	/* Control 3 */
#define  COM3_SWAP	  0x40	  /* Byte swap */
#define  COM3_SCALEEN	  0x08	  /* Enable scaling */
#define  COM3_DCWEN	  0x04	  /* Enable downsamp/crop/window */
#define REG_COM4	0x0d	/* Control 4 */
#define REG_COM5	0x0e	/* All "reserved" */
#define REG_COM6	0x0f	/* Control 6 */
#define REG_AECH	0x10	/* More bits of AEC value */
#define REG_CLKRC	0x11	/* Clocl control */
#define   CLK_EXT	  0x40	  /* Use external clock directly */
#define   CLK_SCALE	  0x3f	  /* Mask for internal clock scale */
#define REG_COM7	0x12	/* Control 7 */
#define   COM7_RESET	  0x80	  /* Register reset */
#define   COM7_FMT_MASK	  0x38
#define   COM7_FMT_VGA	  0x00
#define	  COM7_FMT_CIF	  0x20	  /* CIF format */
#define   COM7_FMT_QVGA	  0x10	  /* QVGA format */
#define   COM7_FMT_QCIF	  0x08	  /* QCIF format */
#define	  COM7_RGB	  0x04	  /* bits 0 and 2 - RGB format */
#define	  COM7_YUV	  0x00	  /* YUV */
#define	  COM7_BAYER	  0x01	  /* Bayer format */
#define	  COM7_PBAYER	  0x05	  /* "Processed bayer" */
#define REG_COM8	0x13	/* Control 8 */
#define   COM8_FASTAEC	  0x80	  /* Enable fast AGC/AEC */
#define   COM8_AECSTEP	  0x40	  /* Unlimited AEC step size */
#define   COM8_BFILT	  0x20	  /* Band filter enable */
#define   COM8_AGC	  0x04	  /* Auto gain enable */
#define   COM8_AWB	  0x02	  /* White balance enable */
#define   COM8_AEC	  0x01	  /* Auto exposure enable */
#define REG_COM9	0x14	/* Control 9  - gain ceiling */
#define REG_COM10	0x15	/* Control 10 */
#define   COM10_HSYNC	  0x40	  /* HSYNC instead of HREF */
#define   COM10_PCLK_HB	  0x20	  /* Suppress PCLK on horiz blank */
#define   COM10_HREF_REV  0x08	  /* Reverse HREF */
#define   COM10_VS_LEAD	  0x04	  /* VSYNC on clock leading edge */
#define   COM10_VS_NEG	  0x02	  /* VSYNC negative */
#define   COM10_HS_NEG	  0x01	  /* HSYNC negative */
#define REG_HSTART	0x17	/* Horiz start high bits */
#define REG_HSTOP	0x18	/* Horiz stop high bits */
#define REG_VSTART	0x19	/* Vert start high bits */
#define REG_VSTOP	0x1a	/* Vert stop high bits */
#define REG_PSHFT	0x1b	/* Pixel delay after HREF */
#define REG_MIDH	0x1c	/* Manuf. ID high */
#define REG_MIDL	0x1d	/* Manuf. ID low */
#define REG_MVFP	0x1e	/* Mirror / vflip */
#define   MVFP_MIRROR	  0x20	  /* Mirror image */
#define   MVFP_FLIP	  0x10	  /* Vertical flip */
#define REG_AEW		0x24	/* AGC upper limit */
#define REG_AEB		0x25	/* AGC lower limit */
#define REG_VPT		0x26	/* AGC/AEC fast mode op region */
#define REG_HSYST	0x30	/* HSYNC rising edge delay */
#define REG_HSYEN	0x31	/* HSYNC falling edge delay */
#define REG_HREF	0x32	/* HREF pieces */
#define REG_TSLB	0x3a	/* lots of stuff */
#define   TSLB_YLAST	  0x04	  /* UYVY or VYUY - see com13 */
#define REG_COM11	0x3b	/* Control 11 */
#define   COM11_NIGHT	  0x80	  /* NIght mode enable */
#define   COM11_NMFR	  0x60	  /* Two bit NM frame rate */
#define   COM11_HZAUTO	  0x10	  /* Auto detect 50/60 Hz */
#define	  COM11_50HZ	  0x08	  /* Manual 50Hz select */
#define   COM11_EXP	  0x02
#define REG_COM12	0x3c	/* Control 12 */
#define   COM12_HREF	  0x80	  /* HREF always */
#define REG_COM13	0x3d	/* Control 13 */
#define   COM13_GAMMA	  0x80	  /* Gamma enable */
#define	  COM13_UVSAT	  0x40	  /* UV saturation auto adjustment */
#define   COM13_UVSWAP	  0x01	  /* V before U - w/TSLB */
#define REG_COM14	0x3e	/* Control 14 */
#define   COM14_DCWEN	  0x10	  /* DCW/PCLK-scale enable */
#define REG_EDGE	0x3f	/* Edge enhancement factor */
#define REG_COM15	0x40	/* Control 15 */
#define   COM15_R10F0	  0x00	  /* Data range 10 to F0 */
#define	  COM15_R01FE	  0x80	  /*            01 to FE */
#define   COM15_R00FF	  0xc0	  /*            00 to FF */
#define   COM15_RGB565	  0x10	  /* RGB565 output */
#define   COM15_RGB555	  0x30	  /* RGB555 output */
#define REG_COM16	0x41	/* Control 16 */
#define   COM16_AWBGAIN   0x08	  /* AWB gain enable */
#define REG_COM17	0x42	/* Control 17 */
#define   COM17_AECWIN	  0xc0	  /* AEC window - must match COM4 */
#define   COM17_CBAR	  0x08	  /* DSP Color bar */
#define	REG_CMATRIX_BASE 0x4f
#define   CMATRIX_LEN 6
#define REG_CMATRIX_SIGN 0x58
#define REG_BRIGHT	0x55	/* Brightness */
#define REG_CONTRAS	0x56	/* Contrast control */
#define REG_GFIX	0x69	/* Fix gain control */
#define REG_REG76	0x76	/* OV's name */
#define   R76_BLKPCOR	  0x80	  /* Black pixel correction enable */
#define   R76_WHTPCOR	  0x40	  /* White pixel correction enable */
#define REG_RGB444	0x8c	/* RGB 444 control */
#define   R444_ENABLE	  0x02	  /* Turn on RGB444, overrides 5x5 */
#define   R444_RGBX	  0x01	  /* Empty nibble at end */
#define REG_HAECC1	0x9f	/* Hist AEC/AGC control 1 */
#define REG_HAECC2	0xa0	/* Hist AEC/AGC control 2 */
#define REG_BD50MAX	0xa5	/* 50hz banding step limit */
#define REG_HAECC3	0xa6	/* Hist AEC/AGC control 3 */
#define REG_HAECC4	0xa7	/* Hist AEC/AGC control 4 */
#define REG_HAECC5	0xa8	/* Hist AEC/AGC control 5 */
#define REG_HAECC6	0xa9	/* Hist AEC/AGC control 6 */
#define REG_HAECC7	0xaa	/* Hist AEC/AGC control 7 */
#define REG_BD60MAX	0xab	/* 60hz banding step limit */


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


void cam_write_1()
{
	cam_write( REG_COM7, COM7_RGB ); /* Selects RGB mode */
	cam_write( REG_RGB444, 0 );	/* No RGB444 please */
	cam_write( REG_COM1, 0x0 );	/* CCIR601 */
	cam_write( REG_COM15, COM15_RGB565 );
	cam_write( REG_COM9, 0x38 ); 	/* 16x gain ceiling; 0x8 is reserved bit */
	cam_write( 0x4f, 0xb3 ); 	/* "matrix coefficient 1" */
	cam_write( 0x50, 0xb3 ); 	/* "matrix coefficient 2" */
	cam_write( 0x51, 0    );		/* vb */
	cam_write( 0x52, 0x3d ); 	/* "matrix coefficient 4" */
	cam_write( 0x53, 0xa7 ); 	/* "matrix coefficient 5" */
	cam_write( 0x54, 0xe4 ); 	/* "matrix coefficient 6" */
	cam_write( REG_COM13, COM13_GAMMA|COM13_UVSAT );

}


void cam_write_2()
{
	cam_write( REG_CLKRC, 0x1 );	/* OV: clock scale (30 fps) */
	cam_write( REG_TSLB,  0x04 );	/* OV */
cam_write( REG_COM7, 0 );	/* VGA */
/*
 * Set the hardware window.  These values from OV don't entirely
 * make sense - hstop is less than hstart.  But they work...
 */
cam_write( REG_HSTART, 0x13 );
cam_write( REG_HSTOP, 0x01 );
cam_write( REG_HREF, 0xb6 );
cam_write( REG_VSTART, 0x02 );
cam_write( REG_VSTOP, 0x7a );
cam_write( REG_VREF, 0x0a );
cam_write( REG_COM3, 0 );
cam_write( REG_COM14, 0 );
/* Mystery scaling numbers */
cam_write( 0x70, 0x3a );
cam_write( 0x71, 0x35 );
cam_write( 0x72, 0x11 );
cam_write( 0x73, 0xf0 );
cam_write( 0xa2, 0x02 );
cam_write( REG_COM10, 0x0 );
/* Gamma curve values */
cam_write( 0x7a, 0x20 );
cam_write( 0x7b, 0x10 );
cam_write( 0x7c, 0x1e );
cam_write( 0x7d, 0x35 );
cam_write( 0x7e, 0x5a );
cam_write( 0x7f, 0x69 );
cam_write( 0x80, 0x76 );
cam_write( 0x81, 0x80 );
cam_write( 0x82, 0x88 );
cam_write( 0x83, 0x8f );
cam_write( 0x84, 0x96 );
cam_write( 0x85, 0xa3 );
cam_write( 0x86, 0xaf );
cam_write( 0x87, 0xc4 );
cam_write( 0x88, 0xd7 );
cam_write( 0x89, 0xe8 );
/* AGC and AEC parameters.  Note we start by disabling those features,
   then turn them only after tweaking the values. */
cam_write( REG_COM8, COM8_FASTAEC | COM8_AECSTEP | COM8_BFILT );
cam_write( REG_GAIN, 0 );
cam_write( REG_AECH, 0 );
cam_write( REG_COM4, 0x40 ); /* magic reserved bit */
cam_write( REG_COM9, 0x18 ); /* 4x gain + magic rsvd bit */
cam_write( REG_BD50MAX, 0x05 );
cam_write( REG_BD60MAX, 0x07 );
cam_write( REG_AEW, 0x95 );
cam_write( REG_AEB, 0x33 );
cam_write( REG_VPT, 0xe3 );
cam_write( REG_HAECC1, 0x78 );
cam_write( REG_HAECC2, 0x68 );
cam_write( 0xa1, 0x03 ); /* magic */
cam_write( REG_HAECC3, 0xd8 );
cam_write( REG_HAECC4, 0xd8 );
cam_write( REG_HAECC5, 0xf0 );
cam_write( REG_HAECC6, 0x90 );
cam_write( REG_HAECC7, 0x94 );
cam_write( REG_COM8, COM8_FASTAEC|COM8_AECSTEP|COM8_BFILT|COM8_AGC|COM8_AEC );
/* Almost all of these are magic "reserved" values.  */
cam_write( REG_COM5, 0x61 );
cam_write( REG_COM6, 0x4b );
cam_write( 0x16, 0x02 );
cam_write(  REG_MVFP, 0x07 );
cam_write( 0x21, 0x02 );
cam_write(  0x22, 0x91 );
cam_write( 0x29, 0x07 );
cam_write(  0x33, 0x0b );
cam_write( 0x35, 0x0b );
cam_write(  0x37, 0x1d );
cam_write( 0x38, 0x71 );
cam_write(  0x39, 0x2a );
cam_write( REG_COM12, 0x78 );
cam_write( 0x4d, 0x40 );
cam_write( 0x4e, 0x20 );
cam_write( REG_GFIX, 0 );
cam_write( 0x6b, 0x4a );
cam_write( 0x74, 0x10 );
cam_write( 0x8d, 0x4f );
cam_write(  0x8e, 0 );
cam_write( 0x8f, 0 );
cam_write( 0x90, 0 );
cam_write( 0x91, 0 );
cam_write( 0x96, 0 );
cam_write( 0x9a, 0 );
cam_write(  0xb0, 0x84 );
cam_write( 0xb1, 0x0c );
cam_write( 0xb2, 0x0e );
cam_write( 0xb3, 0x82 );
cam_write( 0xb8, 0x0a );
/* More reserved magic, some of which tweaks white balance */
cam_write( 0x43, 0x0a );
cam_write(  0x44, 0xf0 );
cam_write( 0x45, 0x34 );
cam_write(  0x46, 0x58 );
cam_write( 0x47, 0x28 );
cam_write( 0x48, 0x3a );
cam_write( 0x59, 0x88 );
cam_write( 0x5a, 0x88 );
cam_write( 0x5b, 0x44 );
cam_write( 0x5c, 0x67 );
cam_write( 0x5d, 0x49 );
cam_write( 0x5e, 0x0e );
cam_write( 0x6c, 0x0a );
cam_write(  0x6d, 0x55 );
cam_write( 0x6e, 0x11 );
cam_write( 0x6f, 0x9f ); /* "9e for advance AWB" */
cam_write( 0x6a, 0x40 );
cam_write( REG_BLUE, 0x40 );
cam_write( REG_RED, 0x60 );
cam_write( REG_COM8, COM8_FASTAEC|COM8_AECSTEP|COM8_BFILT|COM8_AGC|COM8_AEC|COM8_AWB );
/* Matrix coefficients */
cam_write( 0x4f, 0x80 );
cam_write( 0x50, 0x80 );
cam_write( 0x51, 0 );
cam_write( 0x52, 0x22 );
cam_write( 0x53, 0x5e );
cam_write(  0x54, 0x80 );
cam_write( 0x58, 0x9e );
cam_write( REG_COM16, COM16_AWBGAIN );
cam_write(  REG_EDGE, 0 );
cam_write( 0x75, 0x05 );
cam_write(  0x76, 0xe1 );
cam_write( 0x4c, 0 );
cam_write( 0x77, 0x01 );
cam_write( REG_COM13, 0xc3 );
cam_write(  0x4b, 0x09 );
cam_write( 0xc9, 0x60 );
cam_write( REG_COM16, 0x38 );
cam_write( 0x56, 0x40 );
cam_write( 0x34, 0x11 );
cam_write(  REG_COM11, COM11_EXP|COM11_HZAUTO );
cam_write( 0xa4, 0x88 );
cam_write(  0x96, 0 );
cam_write( 0x97, 0x30 );
cam_write(  0x98, 0x20 );
cam_write( 0x99, 0x30 );
cam_write(  0x9a, 0x84 );
cam_write( 0x9b, 0x29 );
cam_write( 0x9c, 0x03 );
cam_write( 0x9d, 0x4c );
cam_write( 0x9e, 0x3f );
cam_write( 0x78, 0x04 );
/* Extra-weird stuff.  Some sort of multiplexor register */
cam_write( 0x79, 0x01 );
cam_write( 0xc8, 0xf0 );
cam_write( 0x79, 0x0f );
cam_write( 0xc8, 0x00 );
cam_write( 0x79, 0x10 );
cam_write(  0xc8, 0x7e );
cam_write( 0x79, 0x0a );
cam_write(  0xc8, 0x80 );
cam_write( 0x79, 0x0b );
cam_write( 0xc8, 0x01 );
cam_write( 0x79, 0x0c );
cam_write(  0xc8, 0x0f );
cam_write( 0x79, 0x0d );
cam_write(  0xc8, 0x20 );
cam_write( 0x79, 0x09 );
cam_write( 0xc8, 0x80 );
cam_write( 0x79, 0x02 );
cam_write(  0xc8, 0xc0 );
cam_write( 0x79, 0x03 );
cam_write(  0xc8, 0x40 );
cam_write( 0x79, 0x05 );
cam_write( 0xc8, 0x30 );
cam_write( 0x79, 0x26 );

}


int cam_init()
{
  //int i;
  //ALT_AVALON_I2C_STATUS_CODE status;

  //get a pointer to the avalon i2c instance
  i2c_dev = alt_avalon_i2c_open("/dev/camera_i2c");
  if (NULL==i2c_dev)
  {
      printf("Error: Cannot find /dev/camera_i2c\n");
      return 1;
  }

  //set the address of the device using

  alt_avalon_i2c_master_target_set(i2c_dev,0x21);

  //cam_write(REG_COM7,0x80);	// reset

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

// delay routine using timer
void delay_usec(int delay)
{
	//volatile uint16_t* timer0 = INTERVAL_TIMER_BASE;

	//

}

void copy_that()
{
	uint16_t * vga_ram = 0x08000000;
	uint16_t * cam_ram = 0x02000000;

	for (int i = 0; i<160; i++)
	{
		for (int j=0;j<120;j++)
		{
			*(vga_ram+i+j*160) = *(cam_ram+(i*4)+(j*4*160));
		}
	}


}

//volatile uint16_t * camcam = 0xFF200100;
volatile short * pixel_buffer = (short *) 0x01000000; // Pixel buffer

#define PCLK 0x100
#define HREF 0x200
#define VSYNCH 0x400

int main()
{
  printf("Hello from Nios II!\n");


//  c2();
//  c2();

//  0xFF203020
//  0xFF203024

//  clear_screen(0xF00F);
// clear_screen(0x00FF);

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
	else if (cmd == 'c')
	{
		copy_that();
	}

  }


  return 0;
}


