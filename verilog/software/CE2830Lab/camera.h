/*
 * camera.h
 *
 *  Created on: Apr 29, 2019
 *      Author: boyntonrl
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "alt_types.h"

#define CAM_BASE 0xFF2000C0

/**
 * Configure and enable peripheral
 */ 
void cam_init();

/**
 * Sets a camera register to the provided value
 */ 
void cam_setReg(alt_u32* cmd);

/**
 * Gets the current register value from the camera
 */ 
alt_u32 cam_getReg();



#endif /* CAMERA_H_ */
