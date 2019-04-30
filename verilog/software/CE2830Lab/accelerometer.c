/*
 * accelerometer.c
 *
 *  Created on: Apr 10, 2019
 *      Author: boyntonrl
 */
#include "accelerometer.h"
#include "ServoAPI.h"

 static volatile ACCELEROMETER* acceleromter = (alt_u32*) ACCELEROMETER_BASE;

 int acc_read_x(){
     acceleromter->address = DATAX0;
     alt_16 data = 0x0000|acceleromter->data;
     acceleromter->address = DATAX1;
     data |= ((acceleromter->data&0x01)<<8);
     if(acceleromter->data&0x02 == 2){
         data |= (0b1111111<<9);
     }
     return (int)data;
 }

int acc_read_y(){
     acceleromter->address = DATAY0;
     alt_16 data = 0x0000|acceleromter->data;
     acceleromter->address = DATAY1;
     data |= ((acceleromter->data&0x01)<<8);
     if(acceleromter->data&0x02 == 2){
         data |= (0b1111111<<9);
     }
     return (int)data;
 }

 int acc_read_z(){
     acceleromter->address = DATAZ0;
     alt_16 data = 0x0000|acceleromter->data;
     acceleromter->address = DATAZ1;
     data |= ((acceleromter->data&0x01)<<8);
     if(acceleromter->data&0x02 == 2){
         data |= (0b1111111<<9);
     }
     return (int)data;
 }

 void acc_steady_servo(){
	 servo_setAngle(SERVO_X, (alt_8)(-acc_read_y()*0.1765));
	 servo_setAngle(SERVO_Y, (alt_8)(-acc_read_x()*0.1765));
 }


