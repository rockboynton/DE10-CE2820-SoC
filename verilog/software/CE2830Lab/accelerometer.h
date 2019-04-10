/*
 * accelerometer.h
 *
 *  Created on: Apr 10, 2019
 *      Author: boyntonrl
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include "altera_up_avalon_accelerometer_spi.h"

#define ACCELEROMETER_BASE 0xFF2000B0

#define DATAX0 0x32
#define DATAX1 0x33
#define DATAY0 0x34
#define DATAY1 0x35
#define DATAZ0 0x36
#define DATAZ1 0x37

/**
 * Reads x-axis from accelerometer
 * @return signed integer 
 */ 
int acc_read_x();

/**
 * Reads y-axis from accelerometer
 * @return signed integer
 */ 
int acc_read_y();

/**
 * Reads z-axis from accelerometer
 * @return signed integer
 */ 
int acc_read_z();

#endif /* ACCELEROMETER_H_ */
